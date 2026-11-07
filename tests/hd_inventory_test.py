"""Synthetic background inventory checks; no disc images or game assets."""
import importlib.util
import json
from pathlib import Path
import tempfile
import unittest

from PIL import Image

spec = importlib.util.spec_from_file_location('hd_inventory', Path(__file__).resolve().parents[1]/'tools/hd/inventory.py')
inventory_module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(inventory_module)


class InventoryTest(unittest.TestCase):
    def test_shared_pixels_missing_sources_and_screen_classification(self):
        with tempfile.TemporaryDirectory() as name:
            assets=Path(name)
            Image.new('RGB',(320,240),(32,48,64)).save(assets/'one.png')
            Image.new('RGB',(320,240),(32,48,64)).save(assets/'two.png')
            manifest={'stage0':{'files':{'title':{'background.bs':{'type':'room_background','path':'one.png'}}}},
                'stage1':{'folders':{'akropolis_square':{'file1':{'view.bs':{'type':'room_background','path':'two.png'}},
                    'file2':{'view.bs':{'type':'room_background','path':'missing.png'}},
                    'file3':{'ignore':{'type':'image','path':'two.png'}}}}}}
            report=inventory_module.inventory(manifest,assets)
            self.assertEqual(report['summary']['records'],3)
            self.assertEqual(report['summary']['missing'],1)
            self.assertEqual(report['summary']['unique_rgb'],1)
            self.assertEqual(report['summary']['dimensions'],{'320x240':2})
            self.assertIn('non-field',report['records'][0]['review'])
            self.assertEqual(report['records'][1]['review'],'scrolling panorama')
            self.assertEqual(report['records'][1]['mapped_view_file'],1)
            self.assertTrue(all(not r['runtime_verified'] for r in report['records']))

    def test_raw_store_paths_are_not_double_prefixed(self):
        with tempfile.TemporaryDirectory() as name:
            assets=Path(name);(assets/'raw/bs').mkdir(parents=True)
            (assets/'raw/bs/bs_123.bs').write_bytes(b'synthetic raw input')
            manifest={'stage2':{'folders':{'room':{'file1':{'0.bs':{'type':'room_background','path':'bs/bs_123.png'}}}}}}
            report=inventory_module.inventory(manifest,assets)
            self.assertEqual(report['summary']['missing'],0)
            self.assertEqual(report['summary']['unique_raw'],1)
            self.assertEqual(report['records'][0]['raw_source'],'raw/bs/bs_123.bs')
            self.assertNotIn('size',report['records'][0])


if __name__=='__main__':unittest.main()
