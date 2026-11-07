import hashlib
import importlib.util
from pathlib import Path
import struct
import sys
import tempfile
import unittest
import numpy as np
from PIL import Image
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/hd'))
import foreground_pack

class ForegroundPackTest(unittest.TestCase):
    def fixture(self,root):
        raw=np.arange(8*23,dtype='<u2').tobytes();(root/'sprite-0000.rgb555').write_bytes(raw)
        return dict(format='pe2-foreground-source-audit-v1',capture=dict(key='0000000000001234',location=[1,20,10,1,1,1]),
                    sprites=[dict(index=0,native_sha256=hashlib.sha256(raw).hexdigest(),
                                  source=dict(w=8,h=23,x0=-7,y0=-11,tpage=143,clut=16320,u0=104,v0=8))])
    def test_registered_material_and_exact_native_reference_planes(self):
        with tempfile.TemporaryDirectory() as directory:
            root=Path(directory);report=self.fixture(root)
            key,metadata,atlas=foreground_pack.build(report,root,Image.new('RGB',(1792,960),(192,64,128)))
            self.assertEqual(len(metadata),64);self.assertEqual(atlas.size,(1088,136))
            header=struct.unpack('<8sQQ6I',metadata[:48]);self.assertEqual(header,(b'PE2FG2\0\0',0x1234,key,1,20,10,1,1,2))
            self.assertEqual(atlas.getpixel((2,2)),(192,64,128,255))
            self.assertEqual(atlas.getpixel((6,70)),(8,0,0,255))
    def test_explicit_fit_uses_same_registered_canvas_and_native_plane(self):
        with tempfile.TemporaryDirectory() as directory:
            root=Path(directory);report=self.fixture(root);art=Image.new('RGB',(896,480),(192,64,128))
            with self.assertRaises(ValueError):foreground_pack.build(report,root,art)
            _,_,atlas=foreground_pack.build(report,root,art,fit=True)
            self.assertEqual(atlas.getpixel((2,2)),(192,64,128,255))
            self.assertEqual(atlas.getpixel((6,70)),(8,0,0,255))

    def test_inset_tail_cells_preserve_source_coordinates(self):
        with tempfile.TemporaryDirectory() as directory:
            root=Path(directory);raw=np.arange(32*40,dtype='<u2').reshape(40,32)
            report=self.fixture(root);report['sprites'][0]['source'].update(w=32,h=40)
            (root/'sprite-0000.rgb555').write_bytes(raw.tobytes())
            report['sprites'][0]['native_sha256']=hashlib.sha256(raw.tobytes()).hexdigest()
            _,metadata,atlas=foreground_pack.build(report,root,Image.new('RGB',(1792,960),(192,64,128)))
            self.assertEqual(struct.unpack_from('<I',metadata,48)[0],4096)
            word=int(raw[24,0]);expected=tuple(((word>>b)&31)*255//31 for b in [0,5,10])+(255,)
            self.assertEqual(atlas.getpixel((4*68+2,70)),expected)
            report['sprites'][0]['source']['codeFlags']=2
            _,metadata,_=foreground_pack.build(report,root,Image.new('RGB',(1792,960),(192,64,128)))
            self.assertEqual(struct.unpack_from('<I',metadata,48)[0],0)

    def test_changed_native_input_or_transparent_art_is_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            root=Path(directory);report=self.fixture(root);art=Image.new('RGBA',(1792,960),(1,2,3,0))
            with self.assertRaises(ValueError):foreground_pack.build(report,root,art)
            (root/'sprite-0000.rgb555').write_bytes(b'changed')
            with self.assertRaises(ValueError):foreground_pack.build(report,root,art.convert('RGB'))

    def test_individual_material_retains_native_coverage(self):
        with tempfile.TemporaryDirectory() as directory:
            root=Path(directory);report=self.fixture(root);image=Image.new('RGBA',(32,92),(90,110,130,255))
            image.putpixel((0,0),(0,0,0,0)) # Native word zero remains a hole.
            image.save(root/'sprite-0000.png')
            _,_,atlas=foreground_pack.build(report,root,materials=root)
            self.assertEqual(atlas.getpixel((6,2)),(90,110,130,255))
            image.putpixel((4,0),(0,0,0,0));image.save(root/'sprite-0000.png')
            with self.assertRaises(ValueError):foreground_pack.build(report,root,materials=root)

if __name__=='__main__':unittest.main()
