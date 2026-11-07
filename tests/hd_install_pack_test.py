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

if __name__=='__main__':unittest.main()
