import json
from pathlib import Path
import struct
import sys
import tempfile
import unittest
from unittest.mock import patch

from PIL import Image

sys.path.insert(0, str(Path(__file__).resolve().parents[1]/'tools/hd'))
from install_pack import create, read_manifest, install
from material_bundle import MANIFEST, split, hydrate, read_bundle, reference_digest


class MaterialBundleTest(unittest.TestCase):
    def fixture(self, root, name='source', color=(17, 31, 53, 255)):
        source = root/name
        source.mkdir()
        (source/'0000000000000001.pe2bg').write_bytes(struct.pack(
            '<8sQIIiiIIII', b'PE2BG1\0\0', 1, 320, 240, 0, 320, 1, 4, 300, 0))
        raw = struct.pack('<8sQQ6I', b'PE2FG2\0\0', 1, 2, 1, 20, 11, 1, 1, 1)
        raw += struct.pack('<IHHHHBBH', 4096, 0, 0, 16, 16, 0, 0, 0)
        (source/'0000000000000001-1-20-11-1.pe2fg').write_bytes(raw)
        for filename, height in [('0000000000000001.png', 1292), ('0000000000000002.fg.png', 68)]:
            atlas = Image.new('RGBA', (1088, height*2), color)
            atlas.paste(Image.new('RGBA', (1088, height), (89, 101, 113, 255)), (0, height))
            atlas.save(source/filename)
        (source/'private-notes.json').write_text('must not be exported')
        create(source, 'fixture', name)
        return source

    def prepare(self, root):
        source = self.fixture(root)
        materials, cache = root/'materials', root/'private-cache'
        split(source, materials, cache)
        return source, materials, cache

    def test_material_planes_only_and_exact_runtime_round_trip(self):
        with tempfile.TemporaryDirectory() as name:
            root = Path(name)
            source, materials, cache = self.prepare(root)
            bundle = read_bundle(materials)
            self.assertEqual(set(p.name for p in materials.iterdir()), {MANIFEST, *bundle['files']})
            self.assertFalse((materials/'pe2-pack.json').exists())
            self.assertEqual(len(list(cache.glob('*.png'))), 2)
            for filename, record in bundle['atlases'].items():
                with Image.open(source/filename) as original, Image.open(materials/filename) as material:
                    self.assertEqual(material.size, (original.width, original.height//2))
                    self.assertEqual(material.tobytes(), original.crop((0, 0, *material.size)).tobytes())
                    self.assertNotEqual(reference_digest(material), record['reference'])
            restored = root/'restored'
            result = hydrate(materials, cache, restored)
            self.assertEqual(result, read_manifest(source))
            for filename in result['files']:
                self.assertEqual((restored/filename).read_bytes(), (source/filename).read_bytes())
            installed = install(restored, root/'installed')
            self.assertEqual(read_manifest(installed), result)

    def test_reference_cache_is_independent_of_material_pixels(self):
        with tempfile.TemporaryDirectory() as name:
            root = Path(name)
            _, first, cache = self.prepare(root)
            second_source = self.fixture(root, 'other', (201, 41, 59, 255))
            second = root/'other-materials'
            split(second_source, second, cache)
            a, b = read_bundle(first), read_bundle(second)
            self.assertEqual(a['atlases'], b['atlases'])
            self.assertEqual(len(list(cache.iterdir())), 2)
            self.assertNotEqual(a['files']['0000000000000001.png'], b['files']['0000000000000001.png'])
            hydrate(second, cache, root/'other-restored')

    def test_missing_changed_and_symlinked_references_never_publish(self):
        for mode in ['missing', 'changed', 'dimensions', 'symlink']:
            with self.subTest(mode=mode), tempfile.TemporaryDirectory() as name:
                root = Path(name)
                _, materials, cache = self.prepare(root)
                file = next(cache.glob('*.png'))
                if mode == 'missing':
                    file.unlink()
                elif mode == 'changed':
                    with Image.open(file) as image:
                        image = image.convert('RGBA')
                    image.putpixel((0, 0), (1, 2, 3, 255))
                    image.save(file)
                elif mode == 'dimensions':
                    Image.new('RGBA', (1088, 68), (1, 2, 3, 255)).save(file)
                else:
                    saved = root/'saved.png'
                    file.rename(saved)
                    file.symlink_to(saved)
                with self.assertRaises(ValueError):
                    hydrate(materials, cache, root/'restored')
                self.assertFalse((root/'restored').exists())
                self.assertFalse(list(root.glob('.pe2-material-*')))

    def test_changed_or_unlisted_material_and_path_escape_rejected(self):
        for mode in ['changed', 'unlisted', 'escape', 'symlink', 'manifest-shape']:
            with self.subTest(mode=mode), tempfile.TemporaryDirectory() as name:
                root = Path(name)
                _, materials, _ = self.prepare(root)
                file = materials/'0000000000000001.pe2bg'
                if mode == 'changed':
                    file.write_bytes(file.read_bytes() + b'x')
                elif mode == 'unlisted':
                    (materials/'private-native.png').write_bytes(b'must not be archived')
                elif mode == 'symlink':
                    saved = root/'saved-header'
                    file.rename(saved)
                    file.symlink_to(saved)
                elif mode == 'manifest-shape':
                    (materials/MANIFEST).write_text('[]')
                else:
                    data = json.loads((materials/MANIFEST).read_text())
                    data['files']['../escape'] = data['files'].pop(file.name)
                    (materials/MANIFEST).write_text(json.dumps(data))
                with self.assertRaises(ValueError):
                    read_bundle(materials)

    def test_outputs_are_immutable_and_cache_must_be_separate(self):
        with tempfile.TemporaryDirectory() as name:
            root = Path(name)
            source, materials, cache = self.prepare(root)
            saved = (materials/MANIFEST).read_bytes()
            with self.assertRaises(ValueError):
                split(source, materials, cache)
            self.assertEqual((materials/MANIFEST).read_bytes(), saved)
            restored = root/'restored'
            hydrate(materials, cache, restored)
            with self.assertRaises(ValueError):
                hydrate(materials, cache, restored)
            with self.assertRaises(ValueError):
                split(source, root/'nested', root/'nested/cache')
            self.assertFalse((root/'nested').exists())

    def test_copy_failure_leaves_no_material_bundle(self):
        with tempfile.TemporaryDirectory() as name:
            root = Path(name)
            source = self.fixture(root)
            with patch('material_bundle.shutil.copyfile', side_effect=OSError('interrupted')):
                with self.assertRaises(OSError):
                    split(source, root/'materials', root/'private-cache')
            self.assertFalse((root/'materials').exists())
            self.assertFalse(list(root.glob('.pe2-material-*')))

    def test_reference_publication_failure_leaves_no_partial_cache_entry(self):
        with tempfile.TemporaryDirectory() as name:
            root = Path(name)
            source = self.fixture(root)
            with patch('material_bundle.os.link', side_effect=OSError('interrupted publication')):
                with self.assertRaises(OSError):
                    split(source, root/'materials', root/'private-cache')
            self.assertFalse((root/'materials').exists())
            self.assertEqual(list((root/'private-cache').iterdir()), [])

    def test_invalid_full_atlas_inventory_cannot_export_unknown_pixels(self):
        with tempfile.TemporaryDirectory() as name:
            root = Path(name)
            source = self.fixture(root)
            (source/'pe2-pack.json').unlink()
            Image.new('RGBA', (1088, 136)).save(source/'0000000000000003.png')
            create(source, 'fixture', 'extra')
            with self.assertRaises(ValueError):
                split(source, root/'materials', root/'private-cache')
            self.assertFalse((root/'materials').exists())

    def test_source_manifest_changes_during_split_cannot_publish(self):
        import shutil
        copy = shutil.copyfile
        with tempfile.TemporaryDirectory() as name:
            root = Path(name)
            source = self.fixture(root)
            def changed(*args, **kwargs):
                result = copy(*args, **kwargs)
                data = json.loads((source/'pe2-pack.json').read_text())
                data['version'] = 'changed'
                (source/'pe2-pack.json').write_text(json.dumps(data))
                return result
            with patch('material_bundle.shutil.copyfile', side_effect=changed):
                with self.assertRaises(ValueError):
                    split(source, root/'materials', root/'private-cache')
            self.assertFalse((root/'materials').exists())

    def test_material_manifest_changes_during_hydration_cannot_publish(self):
        import shutil
        copy = shutil.copyfile
        with tempfile.TemporaryDirectory() as name:
            root = Path(name)
            _, materials, cache = self.prepare(root)
            def changed(*args, **kwargs):
                result = copy(*args, **kwargs)
                data = json.loads((materials/MANIFEST).read_text())
                data['version'] = 'changed'
                (materials/MANIFEST).write_text(json.dumps(data))
                return result
            with patch('material_bundle.shutil.copyfile', side_effect=changed):
                with self.assertRaises(ValueError):
                    hydrate(materials, cache, root/'restored')
            self.assertFalse((root/'restored').exists())


if __name__ == '__main__':
    unittest.main()
