"""Synthetic pack format/registration gates; no game assets."""
import importlib.util
from pathlib import Path
import struct
import unittest
from PIL import Image
spec=importlib.util.spec_from_file_location('hd_pack',Path(__file__).resolve().parents[1]/'tools/hd/pack.py')
pack=importlib.util.module_from_spec(spec);spec.loader.exec_module(pack)

class PackTest(unittest.TestCase):
    def test_identity_is_little_endian_and_references_remain_native(self):
        self.assertEqual(pack.identity(b'hello'),0xa430d84680aabd0b)
        native=struct.pack('<H',0x801f)*(320*240)
        art=Image.new('RGBA',(1792,960),(12,34,56,255))
        key,metadata,atlas=pack.build(native,art,-64,384)
        fields=struct.unpack('<8sQIIiiIIII',metadata)
        self.assertEqual(fields,(b'PE2BG1\0\0',key,320,240,-64,384,1,4,420,0))
        self.assertEqual(atlas.size,(1088,3672))
        # First central tile is cell 4; its art differs from the native red basis.
        self.assertEqual(atlas.getpixel((4*68+2,2)),(12,34,56,255))
        self.assertEqual(atlas.getpixel((4*68+2,1836+2)),(255,0,0,255))
        self.assertEqual(atlas.getpixel((4*68,0)),(12,34,56,255))

    def test_explicit_size_fit_retains_framing_native_references_and_input(self):
        native=struct.pack('<H',31)*(320*240)
        art=Image.new('RGBA',(896,480),(12,34,56,255));before=art.tobytes()
        with self.assertRaises(ValueError):pack.build(native,art,-64,384)
        _,_,atlas=pack.build(native,art,-64,384,fit=True)
        self.assertEqual(art.tobytes(),before)
        self.assertEqual(atlas.getpixel((4*68+2,2)),(12,34,56,255))
        self.assertEqual(atlas.getpixel((4*68+2,1836+2)),(255,0,0,255))
        for invalid in [Image.new('RGB',(800,480)),Image.new('RGBA',(896,480),(1,2,3,0))]:
            with self.assertRaises(ValueError):pack.build(native,invalid,-64,384,fit=True)

    def test_geometry_alpha_and_native_length_are_strict(self):
        native=bytes(320*240*2)
        for art,left,right in [(Image.new('RGB',(1659,948)),-64,384),
                              (Image.new('RGB',(1792,960)),-63,385),
                              (Image.new('RGBA',(1792,960),(0,0,0,0)),-64,384)]:
            with self.assertRaises(ValueError):pack.build(native,art,left,right)
        with self.assertRaises(ValueError):pack.build(native[:-1],Image.new('RGB',(1792,960)),-64,384)

if __name__=='__main__':unittest.main()
