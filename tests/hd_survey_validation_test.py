"""Reject stale, loading, mismatched and truncated survey captures."""
import importlib.util
import json
from pathlib import Path
import tempfile
import unittest
from PIL import Image
spec=importlib.util.spec_from_file_location('hd_survey',Path(__file__).resolve().parents[1]/'tools/hd/survey.py')
module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)

class SurveyTest(unittest.TestCase):
    def test_capture_evidence_is_specific_and_complete(self):
        with tempfile.TemporaryDirectory() as name:
            root=Path(name);target=dict(keys=['0123456789abcdef'],location=[1,2,3,1,1,1])
            report=dict(format='pe2-static-view-survey-v2',matched_frames=30,key=target['keys'][0],location=target['location'],width=320,height=240)
            (root/'report.json').write_text(json.dumps(report));(root/'vram.bin').write_bytes(bytes(1024*512*2))
            Image.new('RGB',(320,240),(1,2,3)).save(root/'frame.ppm')
            module.validate_capture(root,target)
            for field,value in [('format','pe2-static-view-survey-v1'),('matched_frames',3),('key','wrong'),('location',[1,2,4,1,1,1]),('width',1)]:
                changed={**report,field:value};(root/'report.json').write_text(json.dumps(changed))
                with self.assertRaises(ValueError):module.validate_capture(root,target)
            (root/'report.json').write_text(json.dumps(report))
            Image.new('RGB',(320,240)).save(root/'frame.ppm')
            with self.assertRaises(ValueError):module.validate_capture(root,target)
            Image.new('RGB',(320,240),(1,2,3)).save(root/'frame.ppm');(root/'vram.bin').write_bytes(b'partial')
            with self.assertRaises(ValueError):module.validate_capture(root,target)

if __name__=='__main__':unittest.main()
