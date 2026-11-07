import hashlib
import json
from pathlib import Path
import shutil
import struct
import sys
import tempfile
import unittest

from PIL import Image

sys.path.insert(0, str(Path(__file__).resolve().parents[1]/'tools/hd'))
from install_pack import create, digest, read_manifest
from material_bundle import MANIFEST, acquire, hydrate, read_bundle, split
from pack import build, identity
from foreground_pack import build as build_foreground


class ReferenceAcquisitionTest(unittest.TestCase):
    def fixture(self, root, legacy=False):
        source, native, foreground = root/'private-pack', root/'native', root/'foreground'
        for path in [source, native, foreground]:
            path.mkdir()
        words = [0, 0x8000, 1, 0x1f, 0x3e0, 0x7c00, 0x7fff, 0xffff]
        raw = struct.pack('<8H', *words)*(320*240//8)
        key = identity(raw)
        (native/f'{key:016x}.rgb555').write_bytes(raw)
        art = Image.new('RGB', (1792, 960), (17, 31, 53))
        _, metadata, atlas = build(raw, art, -64, 384)
        (source/f'{key:016x}.pe2bg').write_bytes(metadata)
        atlas.save(source/f'{key:016x}.png')
        report = dict(format='pe2-foreground-source-audit-v1',
                      capture=dict(key=f'{key:016x}', location=[1,20,11,1,6,1]), sprites=[])
        for index, (w, h, flags) in enumerate([(8,18,0), (18,17,0), (17,19,2), (16,16,0)]):
            s = dict(tpage=0, clut=0, w=w, h=h, u0=index*16, v0=0,
                     x0=-160+index*32, y0=-120, codeFlags=2 if legacy else flags)
            pixels = struct.pack('<'+'H'*(w*h), *[(n*211+index*17) & 65535 for n in range(w*h)])
            (foreground/f'sprite-{index:04d}.rgb555').write_bytes(pixels)
            report['sprites'].append(dict(index=index, source=s, native_sha256=hashlib.sha256(pixels).hexdigest()))
        (foreground/'report.json').write_text(json.dumps(report))
        atlas_key, metadata, atlas = build_foreground(report, foreground, art, -64)
        if legacy:
            # Legacy layout uses the producer's non-inset cells for every source.
            metadata = b'PE2FG1\0\0' + metadata[8:]
        (source/f'{key:016x}-1-20-11-1.pe2fg').write_bytes(metadata)
        atlas.save(source/f'{atlas_key:016x}.fg.png')
        original = create(source, 'fixture', 'v1')
        materials = root/'materials'
        split(source, materials, root/'author-cache')
        # Acquisition must work without the author's runtime pack or cache.
        shutil.rmtree(source)
        shutil.rmtree(root/'author-cache')
        return materials, native, foreground, original

    def test_raw_exports_rebuild_exact_references_for_legacy_and_inset_cells(self):
        for legacy in [False, True]:
            with self.subTest(legacy=legacy), tempfile.TemporaryDirectory() as name:
                root = Path(name)
                materials, native, foreground, original = self.fixture(root, legacy)
                result = acquire(materials, root/'cache', native, [foreground])
                self.assertTrue(result['complete'])
                self.assertEqual(len(result['references']), 2)
                restored = hydrate(materials, root/'cache', root/'runtime')
                self.assertEqual(restored['files'], original['files'])
                self.assertEqual(read_manifest(root/'runtime'), restored)

    def test_changed_background_identity_is_rejected(self):
        with tempfile.TemporaryDirectory() as name:
            root = Path(name)
            materials, native, foreground, _ = self.fixture(root)
            file = next(native.glob('*.rgb555'))
            raw = bytearray(file.read_bytes())
            raw[0] ^= 1
            file.write_bytes(raw)
            with self.assertRaisesRegex(ValueError, 'background identity'):
                acquire(materials, root/'cache', native, [foreground])

    def test_missing_changed_misbound_or_ambiguous_foregrounds_rejected(self):
        for mode in ['missing', 'changed', 'context', 'parameters', 'ambiguous']:
            with self.subTest(mode=mode), tempfile.TemporaryDirectory() as name:
                root = Path(name)
                materials, native, foreground, _ = self.fixture(root)
                roots = [foreground]
                report_path = foreground/'report.json'
                if mode == 'missing':
                    roots = []
                elif mode == 'changed':
                    file = foreground/'sprite-0001.rgb555'
                    raw = bytearray(file.read_bytes()); raw[0] ^= 1; file.write_bytes(raw)
                elif mode == 'ambiguous':
                    other = root/'other-foreground'
                    shutil.copytree(foreground, other)
                    roots.append(other)
                else:
                    report = json.loads(report_path.read_text())
                    if mode == 'context':
                        report['capture']['location'][2] += 1
                    else:
                        report['sprites'][1]['source']['u0'] += 1
                    report_path.write_text(json.dumps(report))
                with self.assertRaises(ValueError):
                    acquire(materials, root/'cache', native, roots)

    def test_bundle_layout_is_checked_even_after_payload_hashes_are_refreshed(self):
        with tempfile.TemporaryDirectory() as name:
            root = Path(name)
            materials, native, foreground, _ = self.fixture(root)
            file = next(materials.glob('*.pe2bg'))
            raw = bytearray(file.read_bytes()); struct.pack_into('<I', raw, 16, 319); file.write_bytes(raw)
            data = json.loads((materials/MANIFEST).read_text())
            data['files'][file.name] = dict(size=file.stat().st_size, sha256=digest(file))
            (materials/MANIFEST).write_text(json.dumps(data))
            with self.assertRaises(ValueError):
                read_bundle(materials)
            with self.assertRaises(ValueError):
                acquire(materials, root/'cache', native, [foreground])
            self.assertFalse((root/'cache').exists())

    def test_verified_cache_can_be_reused_without_reopening_exports(self):
        with tempfile.TemporaryDirectory() as name:
            root = Path(name)
            materials, native, foreground, _ = self.fixture(root)
            acquire(materials, root/'cache', native, [foreground])
            saved = {p.name: digest(p) for p in (root/'cache').iterdir()}
            shutil.rmtree(native); shutil.rmtree(foreground)
            result = acquire(materials, root/'cache', native, [foreground])
            self.assertTrue(all(r['cached'] for r in result['references']))
            self.assertEqual(saved, {p.name: digest(p) for p in (root/'cache').iterdir()})

    def test_reference_content_must_match_the_requested_plane(self):
        with tempfile.TemporaryDirectory() as name:
            root = Path(name)
            materials, native, foreground, _ = self.fixture(root)
            data = json.loads((materials/MANIFEST).read_text())
            atlas = next(n for n in data['atlases'] if n.endswith('.fg.png'))
            data['atlases'][atlas]['reference'] = 'f'*64
            (materials/MANIFEST).write_text(json.dumps(data))
            with self.assertRaisesRegex(ValueError, 'No matching native export'):
                acquire(materials, root/'cache', native, [foreground])
            self.assertFalse((root/'cache'/('f'*64+'.png')).exists())


if __name__ == '__main__':
    unittest.main()
