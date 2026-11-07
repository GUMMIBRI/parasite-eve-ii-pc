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
            report=dict(format='pe2-static-view-survey-v3',matched_frames=30,key=target['keys'][0],location=target['location'],width=320,height=240,buffer_y=272)
            (root/'report.json').write_text(json.dumps(report));(root/'vram.bin').write_bytes(bytes(1024*512*2))
            Image.new('RGB',(320,240),(1,2,3)).save(root/'frame.ppm')
            module.validate_capture(root,target)
            audit=dict(format='pe2-gpu-state-audit-v1',complete=True,buffer_y=272,key=report['key'],location=report['location'],sprites=[])
            (root/'gpu-state.json').write_text(json.dumps(audit));module.validate_capture(root,target,True)
            for field,value in [('complete',False),('buffer_y',256),('key','wrong'),('location',[1,2,4,1,1,1]),('format','unknown')]:
                (root/'gpu-state.json').write_text(json.dumps({**audit,field:value}))
                with self.assertRaises(ValueError):module.validate_capture(root,target,True)
            for field,value in [('format','pe2-static-view-survey-v1'),('format','pe2-static-view-survey-v2'),('format','pe2-frame-checkpoint-v1'),('buffer_y',256),('matched_frames',3),('key','wrong'),('location',[1,2,4,1,1,1]),('width',1)]:
                changed={**report,field:value};(root/'report.json').write_text(json.dumps(changed))
                with self.assertRaises(ValueError):module.validate_capture(root,target)
            (root/'report.json').write_text(json.dumps(report))
            Image.new('RGB',(320,240)).save(root/'frame.ppm')
            with self.assertRaises(ValueError):module.validate_capture(root,target)
            Image.new('RGB',(320,240),(1,2,3)).save(root/'frame.ppm');(root/'vram.bin').write_bytes(b'partial')
            with self.assertRaises(ValueError):module.validate_capture(root,target)

if __name__=='__main__':unittest.main()
