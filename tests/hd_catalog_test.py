"""Logical/native catalog joins using only synthetic source metadata."""
import importlib.util
from pathlib import Path
import unittest
spec=importlib.util.spec_from_file_location('hd_view_catalog',Path(__file__).resolve().parents[1]/'tools/hd/view_catalog.py')
module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)

class CatalogTest(unittest.TestCase):
    def scene(self):
        return dict(room='room',stage=1,area=2,warps={'entries':[{'slot':3,'initialView':1}]},placements={'defaultVariant':2},
                    unresolved=[],views=[dict(roomIndex=1,mapWriters=[],views=[dict(view=1,file=4,withinViewCount=True,fileExists=True,camera={'x':0})])])
    def test_mapped_file_is_not_the_logical_view(self):
        native={'records':[dict(stage='stage1',folder='room',mapped_view_file=4,key='1234567812345678',review='unverified static candidate')]}
        result=module.catalog([self.scene()],native);row=result['records'][0]
        self.assertEqual(row['location'],[1,2,1,1,3,2])
        self.assertEqual(row['keys'],['1234567812345678'])
        self.assertTrue(row['eligible_for_start_test']);self.assertFalse(row['runtime_verified'])
    def test_missing_and_ambiguous_sources_never_become_verified(self):
        scene=self.scene();scene['views'][0]['views'][0]['camera']=None
        rows=[dict(stage='stage1',folder='room',mapped_view_file=4,key=key,review='scrolling panorama') for key in ['a','b']]
        result=module.catalog([scene],{'records':rows});row=result['records'][0]
        self.assertFalse(row['eligible_for_start_test']);self.assertIn('multiple native backgrounds',row['review'])
        self.assertIn('no camera',row['review']);self.assertEqual(row['special_renderers'],['scrolling panorama'])
        scene['views']=[];scene['unresolved']=[dict(block='views',reason='no table')]
        result=module.catalog([scene],{'records':[]})
        self.assertEqual(result['summary']['rooms_without_view_rows'],['room'])
        self.assertEqual(result['summary']['unresolved_diagnostics'],1)

if __name__=='__main__':unittest.main()
