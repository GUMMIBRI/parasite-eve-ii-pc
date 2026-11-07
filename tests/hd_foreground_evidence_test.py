import hashlib
import json
from pathlib import Path
import sys
import struct
import tempfile
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/hd'))
from foreground_evidence import check_material_evidence,verify_empty_sources

class ForegroundEvidenceTest(unittest.TestCase):
    def test_visible_and_empty_material_have_distinct_evidence(self):
        check_material_evidence(True,1)
        check_material_evidence(False,1,empty=True)
        check_material_evidence(False,0,empty=True)
        for changed,count,empty in [(False,1,False),(True,0,False),(False,0,False),(True,1,True)]:
            with self.assertRaises(AssertionError):check_material_evidence(changed,count,empty)

    def test_empty_proof_rejects_stp_black_changes_and_wrong_capture(self):
        with tempfile.TemporaryDirectory() as folder:
            root=Path(folder);native=b'\0'*32;key='0000000000001234';location=[1,16,27,1,1,1]
            source=root/'sprite-0000.rgb555';source.write_bytes(native)
            report=dict(format='pe2-foreground-source-audit-v1',capture=dict(key=key,location=location),
                sprites=[dict(index=0,source=dict(w=4,h=4,tpage=143,clut=16320,u0=112,v0=0),native_sha256=hashlib.sha256(native).hexdigest())])
            (root/'report.json').write_text(json.dumps(report))
            metadata=struct.pack('<8sQQ6I',b'PE2FG2\0\0',0x1234,0x5678,*location[:4],1,1)+struct.pack('<IHHHHBBH',0,143,16320,4,4,112,0,0)
            self.assertEqual(verify_empty_sources(root,key,location,metadata),1)
            with self.assertRaises(ValueError):verify_empty_sources(root,key,location,metadata[:-1])
            changed=bytearray(metadata);changed[48]=1
            with self.assertRaises(ValueError):verify_empty_sources(root,key,location,changed)
            with self.assertRaises(ValueError):verify_empty_sources(root,'0000000000005678',location,metadata)
            with self.assertRaises(ValueError):verify_empty_sources(root,key,[1,16,15,1,1,1],metadata)
            source.write_bytes(b'\0\x80'+native[2:])
            with self.assertRaises(ValueError):verify_empty_sources(root,key,location,metadata)
            report['sprites'][0]['native_sha256']=hashlib.sha256(source.read_bytes()).hexdigest()
            (root/'report.json').write_text(json.dumps(report))
            with self.assertRaises(ValueError):verify_empty_sources(root,key,location,metadata)
            source.write_bytes(b'')
            with self.assertRaises(ValueError):verify_empty_sources(root,key,location,metadata)

if __name__=='__main__':unittest.main()
