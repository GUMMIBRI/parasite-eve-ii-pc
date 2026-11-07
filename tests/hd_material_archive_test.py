import hashlib
import json
from pathlib import Path
import stat
import struct
import sys
import tempfile
import unittest
from unittest.mock import patch
import warnings
import zipfile

from PIL import Image

sys.path.insert(0, str(Path(__file__).resolve().parents[1]/'tools/hd'))
import material_archive as archive
from install_pack import create as runtime_manifest, digest, read_manifest
from material_bundle import MANIFEST, hydrate, read_bundle, split


class MaterialArchiveTest(unittest.TestCase):
    def fixture(self, root):
        runtime = root/'runtime';runtime.mkdir()
        (runtime/'0000000000000001.pe2bg').write_bytes(struct.pack(
            '<8sQIIiiIIII', b'PE2BG1\0\0', 1, 320, 240, 0, 320, 1, 4, 300, 0))
        image = Image.new('RGBA', (1088, 2584), (17, 31, 53, 255))
        image.paste((89, 101, 113, 255), (0, 1292, 1088, 2584))
        image.save(runtime/'0000000000000001.png')
        runtime_manifest(runtime, 'fixture', '1')
        materials = root/'materials';cache = root/'cache'
        split(runtime, materials, cache)
        output = root/'materials.zip'
        result = archive.create(materials, output)
        return runtime, materials, cache, output, result['sha256']

    def rewrite(self, source, target, alter):
        with zipfile.ZipFile(source) as original:
            records = [(i, original.read(i)) for i in original.infolist()]
        with warnings.catch_warnings(), zipfile.ZipFile(target, 'w') as output:
            warnings.simplefilter('ignore', UserWarning)
            for info, raw in alter(records):output.writestr(info, raw)
        return digest(target)

    def test_deterministic_transfer_and_exact_hydration_without_cache_in_archive(self):
        with tempfile.TemporaryDirectory() as name:
            root = Path(name);runtime, materials, cache, source, checksum = self.fixture(root)
            second = root/'second.zip';archive.create(materials, second)
            self.assertEqual(source.read_bytes(), second.read_bytes())
            with zipfile.ZipFile(source) as zipped:
                self.assertEqual(set(zipped.namelist()), {MANIFEST, *read_bundle(materials)['files']})
                self.assertTrue(all(i.compress_type == zipfile.ZIP_STORED for i in zipped.infolist()))
            restored = root/'restored';archive.unpack(source, restored, checksum)
            for file in materials.iterdir():self.assertEqual(file.read_bytes(), (restored/file.name).read_bytes())
            self.assertEqual(hydrate(restored, cache, root/'hydrated'), read_manifest(runtime))

    def test_expected_checksum_and_immutable_outputs(self):
        with tempfile.TemporaryDirectory() as name:
            root = Path(name);_, materials, _, source, checksum = self.fixture(root)
            for wrong in [None, '', checksum.upper(), '0'*64]:
                with self.subTest(wrong=wrong), self.assertRaises(ValueError):
                    archive.unpack(source, root/'restored', wrong)
                self.assertFalse((root/'restored').exists())
            saved = source.read_bytes()
            with self.assertRaises(ValueError):archive.create(materials, source)
            self.assertEqual(source.read_bytes(), saved)
            (root/'restored').mkdir();(root/'restored/keep').write_text('keep')
            with self.assertRaises(ValueError):archive.unpack(source, root/'restored', checksum)
            self.assertEqual((root/'restored/keep').read_text(), 'keep')
            with self.assertRaises(ValueError):archive.create(materials, materials/'nested.zip')

    def test_duplicate_traversal_native_cache_and_non_regular_entries_rejected(self):
        for mode in ['duplicate', 'traversal', 'cache', 'directory', 'symlink', 'compression', 'missing-manifest']:
            with self.subTest(mode=mode), tempfile.TemporaryDirectory() as name:
                root = Path(name);_, _, _, source, _ = self.fixture(root)
                def alter(records):
                    if mode == 'missing-manifest':return [(i,r) for i,r in records if i.filename != MANIFEST]
                    if mode == 'duplicate':return records + [records[0]]
                    if mode in ['traversal', 'cache', 'directory']:
                        filename = dict(traversal='../escape', cache='cache/reference.png', directory='folder/')[mode]
                        return records + [(zipfile.ZipInfo(filename), b'forbidden')]
                    info, raw = records[0]
                    if mode == 'symlink':info.external_attr = (stat.S_IFLNK | 0o777) << 16
                    else:info.compress_type = zipfile.ZIP_BZIP2
                    return [(info, raw), *records[1:]]
                checksum = self.rewrite(source, root/'bad.zip', alter)
                with self.assertRaises(ValueError):archive.unpack(root/'bad.zip', root/'output', checksum)
                self.assertFalse((root/'output').exists());self.assertFalse((root/'escape').exists())

    def test_changed_payload_and_rehashed_invalid_layout_never_publish(self):
        for refresh in [False, True]:
            with self.subTest(refresh=refresh), tempfile.TemporaryDirectory() as name:
                root = Path(name);_, _, _, source, _ = self.fixture(root)
                def alter(records):
                    files = {i.filename: raw for i,raw in records}
                    key = '0000000000000001.pe2bg'
                    raw = bytearray(files[key]);struct.pack_into('<I',raw,16,319);files[key] = bytes(raw)
                    if refresh:
                        manifest = json.loads(files[MANIFEST]);manifest['files'][key]['sha256'] = hashlib.sha256(raw).hexdigest()
                        files[MANIFEST] = json.dumps(manifest).encode()
                    return [(i,files[i.filename]) for i,_ in records]
                checksum = self.rewrite(source, root/'bad.zip', alter)
                with self.assertRaises(ValueError):archive.unpack(root/'bad.zip', root/'output', checksum)
                self.assertFalse((root/'output').exists())

    def test_limits_and_interrupted_archive_writes(self):
        with tempfile.TemporaryDirectory() as name:
            root = Path(name);_, materials, _, source, checksum = self.fixture(root)
            for setting, limit in [('MAX_FILES', 1), ('MAX_FILE_BYTES', 8), ('MAX_TOTAL_BYTES', 8)]:
                with self.subTest(setting=setting), patch.object(archive, setting, limit), self.assertRaises(ValueError):
                    archive.unpack(source, root/'output', checksum)
                self.assertFalse((root/'output').exists())
                with patch.object(archive, setting, limit), self.assertRaises(ValueError):
                    archive.create(materials, root/'oversized.zip')
                self.assertFalse((root/'oversized.zip').exists())
            with patch.object(zipfile.ZipFile, 'writestr', side_effect=OSError('interrupted')):
                with self.assertRaises(OSError):archive.create(materials, root/'interrupted.zip')
            self.assertFalse((root/'interrupted.zip').exists())
            self.assertFalse(list(root.glob('.pe2-archive-*')))

    def test_archive_changed_during_unpack_is_not_published(self):
        with tempfile.TemporaryDirectory() as name:
            root = Path(name);_, _, _, source, checksum = self.fixture(root)
            real = archive.read_bundle
            def changed(path):
                result = real(path)
                with source.open('ab') as file:file.write(b'changed')
                return result
            with patch.object(archive, 'read_bundle', side_effect=changed), self.assertRaises(ValueError):
                archive.unpack(source, root/'output', checksum)
            self.assertFalse((root/'output').exists())

    def test_changed_source_during_archive_creation_is_not_published(self):
        with tempfile.TemporaryDirectory() as name:
            root = Path(name);_, materials, _, _, _ = self.fixture(root)
            real = zipfile.ZipFile.writestr
            def changed(zipped, entry, raw, **kwargs):
                result = real(zipped, entry, raw, **kwargs)
                (materials/'0000000000000001.pe2bg').write_bytes(b'changed')
                return result
            with patch.object(zipfile.ZipFile, 'writestr', changed), self.assertRaises(ValueError):
                archive.create(materials, root/'changed.zip')
            self.assertFalse((root/'changed.zip').exists())

    def test_corrupt_zip_crc_never_publishes(self):
        with tempfile.TemporaryDirectory() as name:
            root = Path(name);_, _, _, source, _ = self.fixture(root)
            with zipfile.ZipFile(source) as zipped:info = zipped.infolist()[0]
            raw = bytearray(source.read_bytes())
            name_length, extra_length = struct.unpack_from('<HH', raw, info.header_offset+26)
            raw[info.header_offset+30+name_length+extra_length] ^= 1
            source.write_bytes(raw)
            with self.assertRaises(zipfile.BadZipFile):archive.unpack(source, root/'output', digest(source))
            self.assertFalse((root/'output').exists())

    @unittest.skipUnless(hasattr(Path, 'symlink_to'), 'Symlinks unavailable')
    def test_symlink_archive_and_destination_rejected(self):
        with tempfile.TemporaryDirectory() as name:
            root = Path(name);_, _, _, source, checksum = self.fixture(root)
            link = root/'link.zip';link.symlink_to(source)
            with self.assertRaises(ValueError):archive.unpack(link, root/'output', checksum)
            output = root/'output';output.symlink_to(root/'missing-directory')
            with self.assertRaises(ValueError):archive.unpack(source, output, checksum)
            self.assertTrue(output.is_symlink())


if __name__ == '__main__':
    unittest.main()
