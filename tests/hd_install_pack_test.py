import json
from pathlib import Path
import struct
import sys
import tempfile
import unittest
from unittest.mock import patch
from PIL import Image
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/hd'))
from install_pack import create,read_manifest,install,MANIFEST

class InstallTest(unittest.TestCase):
    def foreground(self,source,version=2,source_id=4096,width=16):
        raw=struct.pack('<8sQQ6I',b'PE2FG2\0\0' if version==2 else b'PE2FG1\0\0',1,2,1,20,11,1,1,1)
        raw+=struct.pack('<IHHHHBBH',source_id,0,0,width,16,0,0,0)
        (source/'0000000000000001-1-20-11-1.pe2fg').write_bytes(raw)
        Image.new('RGBA',(1088,136)).save(source/'0000000000000002.fg.png')

    def fixture(self,root):
        source=root/'source';source.mkdir();key='0000000000000001'
        (source/(key+'.pe2bg')).write_bytes(struct.pack('<8sQIIiiIIII',b'PE2BG1\0\0',1,320,240,0,320,1,4,300,0))
        Image.new('RGBA',(1088,2584)).save(source/(key+'.png'))
        return source

    def test_verified_copy_retains_previous_versions_and_ignores_private_notes(self):
        with tempfile.TemporaryDirectory() as temporary:
            root=Path(temporary);source=self.fixture(root);(source/'private.json').write_text('private')
            data=create(source,'gallery','v1');target=install(source,root/'installed')
            self.assertEqual(read_manifest(target),data)
            self.assertFalse((target/'private.json').exists())
            extra=target/'0000000000000003.pe2bg';extra.write_bytes(b'unlisted')
            with self.assertRaises(ValueError):read_manifest(target)
            extra.unlink()
            with self.assertRaises(ValueError):install(source,root/'installed')
            (source/MANIFEST).unlink();create(source,'gallery','v2');install(source,root/'installed')
            self.assertEqual(read_manifest(target),data)

    def test_changed_payload_and_path_escape_never_publish(self):
        with tempfile.TemporaryDirectory() as temporary:
            root=Path(temporary);source=self.fixture(root);create(source,'gallery','v1')
            file=source/'0000000000000001.pe2bg';file.write_bytes(file.read_bytes()+b'x')
            with self.assertRaises(ValueError):install(source,root/'installed')
            self.assertFalse((root/'installed').exists())
            data=json.loads((source/MANIFEST).read_text());data['files']['../escape']=next(iter(data['files'].values()))
            (source/MANIFEST).write_text(json.dumps(data))
            with self.assertRaises(ValueError):read_manifest(source)

    def test_symlink_and_bad_metadata_rejected(self):
        with tempfile.TemporaryDirectory() as temporary:
            root=Path(temporary);source=self.fixture(root)
            file=source/'0000000000000001.pe2bg';data=file.read_bytes();file.unlink();(root/'header').write_bytes(data);file.symlink_to(root/'header')
            with self.assertRaises(ValueError):create(source,'gallery','v1')
            file.unlink();file.write_bytes(bytes(48))
            with self.assertRaises(ValueError):create(source,'gallery','v1')
            self.assertFalse((source/MANIFEST).exists())

    def test_existing_manifest_symlink_is_never_removed(self):
        with tempfile.TemporaryDirectory() as temporary:
            root=Path(temporary);source=self.fixture(root)
            manifest=source/MANIFEST;manifest.symlink_to(root/'missing')
            with self.assertRaises(ValueError):create(source,'gallery','v1')
            self.assertTrue(manifest.is_symlink())

    def test_copy_failure_does_not_publish_partial_version(self):
        with tempfile.TemporaryDirectory() as temporary:
            root=Path(temporary);source=self.fixture(root);create(source,'gallery','v1')
            with patch('install_pack.shutil.copyfile',side_effect=OSError('interrupted copy')):
                with self.assertRaises(OSError):install(source,root/'installed')
            self.assertEqual(list((root/'installed').iterdir()),[])
            read_manifest(source)

    def test_foreground_structure_rejected_even_with_fresh_hashes(self):
        # Fresh manifests cannot legitimize corrupt descriptors or misbound art.
        for offset,value in [(8,3),(24,2),(40,2),(44,2),(48,8192),(52,384),(54,32768),(62,1)]:
            with self.subTest(offset=offset),tempfile.TemporaryDirectory() as temporary:
                source=self.fixture(Path(temporary));self.foreground(source)
                file=source/'0000000000000001-1-20-11-1.pe2fg';raw=bytearray(file.read_bytes())
                size=2 if offset in [52,54,62] else 4
                raw[offset:offset+size]=value.to_bytes(size,'little');file.write_bytes(raw)
                with self.assertRaises(ValueError):create(source,'gallery','v1')
                self.assertFalse((source/MANIFEST).exists())

    def test_foreground_legacy_and_inset_versions_and_atlas_dimensions(self):
        for version,source_id in [(1,0),(2,4096)]:
            with tempfile.TemporaryDirectory() as temporary:
                root=Path(temporary);source=self.fixture(root);self.foreground(source,version,source_id)
                create(source,'gallery','v1');install(source,root/'installed')
                (source/MANIFEST).unlink();Image.new('RGBA',(1088,272)).save(source/'0000000000000002.fg.png')
                with self.assertRaises(ValueError):create(source,'gallery','v2')
        with tempfile.TemporaryDirectory() as temporary:
            source=self.fixture(Path(temporary));self.foreground(source,width=8)
            with self.assertRaises(ValueError):create(source,'gallery','v1')

if __name__=='__main__':unittest.main()
