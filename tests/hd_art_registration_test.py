import sys
from pathlib import Path
import unittest
import numpy as np
from PIL import Image
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/hd'))
from check_art_registration import assess
from pack import identity

class RegistrationTest(unittest.TestCase):
    def fixture(self,dx=0,dy=0):
        words=np.zeros((240,320),dtype='<u2')
        words[65:98,76:126]=31;words[100:139,91:146]=31<<5;words[112:146,150:174]=31<<10
        native=words.tobytes();rgb=np.stack([((words>>s)&31)*255//31 for s in [0,5,10]],axis=-1).astype(np.uint8)
        rgb=np.roll(rgb,(dy,dx),axis=(0,1))
        art=Image.new('RGB',(1792,960));art.paste(Image.fromarray(rgb).resize((1280,960),Image.Resampling.NEAREST),(256,0))
        audit=dict(format='pe2-foreground-source-audit-v1',capture=dict(key=f'{identity(native):016x}'),sprites=[dict(index=0,screen_rect=[65,55,120,105])])
        return native,art,audit
    def test_known_source_alignment_and_integer_displacement(self):
        for dx,dy in [(0,0),(3,-2),(-2,4)]:
            native,art,audit=self.fixture(dx,dy);before=art.tobytes();report=assess(native,art,audit,radius=5)
            self.assertEqual(report['regions'][0]['best_shift_native_px'],[dx,dy])
            self.assertEqual(art.tobytes(),before)
            self.assertFalse(report['approved'])
    def test_side_regions_use_outpaint_search_without_losing_authored_pixels(self):
        words=np.zeros((240,320),dtype='<u2');words[90:110,306:316]=31;words[110:140,314:319]=31<<5
        native=words.tobytes();rgb=np.stack([((words>>s)&31)*255//31 for s in [0,5,10]],axis=-1).astype(np.uint8)
        canvas=np.zeros((240,448,3),np.uint8);canvas[:,64:384]=rgb
        canvas=np.roll(canvas,(-2,3),axis=(0,1))
        art=Image.fromarray(canvas).resize((1792,960),Image.Resampling.NEAREST)
        audit=dict(format='pe2-foreground-source-audit-v1',capture=dict(key=f'{identity(native):016x}'),sprites=[dict(index=0,screen_rect=[308,80,12,80])])
        row=assess(native,art,audit,radius=5)['regions'][0]
        self.assertEqual(row['best_shift_native_px'],[3,-2])
        self.assertLessEqual(row['template_rect'][0],308)
        self.assertEqual(row['template_rect'][2],319)
        self.assertFalse(row['search_truncated'])

    def test_flat_or_wrong_identity_does_not_claim_alignment(self):
        native,art,audit=self.fixture();audit['capture']['key']='wrong'
        with self.assertRaises(ValueError):assess(native,art,audit)
        report=assess(bytes(320*240*2),Image.new('RGB',(1792,960)))
        self.assertFalse(report['regions'][0]['informative'])
        with self.assertRaises(ValueError):assess(native,art,radius=0)

if __name__=='__main__':unittest.main()
