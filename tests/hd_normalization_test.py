"""Source geometry remains exact in a generated-material candidate."""
import importlib.util
from pathlib import Path
import sys
import unittest
import numpy as np
from PIL import Image
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/hd'))
spec=importlib.util.spec_from_file_location('hd_normalize',Path(__file__).resolve().parents[1]/'tools/hd/normalize_art.py')
module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)

class NormalizationTest(unittest.TestCase):
    def native(self):
        pixels=np.full((240,320),0x4210,dtype='<u2');pixels[:,160:]=0x7fff;return pixels.tobytes()
    def test_edges_marks_and_boundary_colours_are_exact(self):
        generated=np.zeros((960,1792,3),np.uint8);generated[:]=(64,80,96)
        generated[::2,::2]=(96,64,80)
        image,report=module.normalize(self.native(),Image.fromarray(generated))
        self.assertEqual(image.size,(1792,960));self.assertEqual(report['protected_channel_mismatches'],0)
        self.assertGreater(report['enhanced_pixels'],0);self.assertLessEqual(report['centre_max_channel_delta'],16)
        data=np.array(image);self.assertTrue(np.array_equal(data[:,255],data[:,256]))
        self.assertTrue(np.array_equal(data[:,1535],data[:,1536]))
    def test_wrong_canvas_and_transparency_require_rejection(self):
        with self.assertRaises(ValueError):module.normalize(self.native(),Image.new('RGB',(100,100)))
        with self.assertRaises(ValueError):module.normalize(self.native(),Image.new('RGBA',(1792,960),(0,0,0,0)))
        image,report=module.normalize(self.native(),Image.new('RGB',(100,100)),fit=True)
        self.assertEqual(image.size,(1792,960))

if __name__=='__main__':unittest.main()
