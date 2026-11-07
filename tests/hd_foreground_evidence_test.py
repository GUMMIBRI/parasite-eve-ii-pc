import hashlib
import json
from pathlib import Path
import sys
import struct
import tempfile
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/hd'))
from foreground_evidence import check_material_evidence,verify_empty_sources,compare_gpu_commands,normalized_gpu_commands,simulation_state

class ForegroundEvidenceTest(unittest.TestCase):
    def test_visible_and_empty_material_have_distinct_evidence(self):
        check_material_evidence(True,1)
        check_material_evidence(False,1,empty=True)
        check_material_evidence(False,0,empty=True)
        for changed,count,empty in [(False,1,False),(True,0,False),(False,0,False),(True,1,True)]:
            with self.assertRaises(AssertionError):check_material_evidence(changed,count,empty)

    def test_gpu_input_comparison_preserves_meaningful_fields(self):
        def trace(words):return struct.pack('<'+'I'*(len(words)+1),len(words),*words)
        original=[0x25010203,0x00100020,0x12340000,0x00300040,0x01800010,0x00500060,0xabcd0020]
        ignored=original.copy();ignored[0]=0x25abcdef;ignored[6]=0x98760020
        self.assertTrue(compare_gpu_commands(trace(original),trace(ignored))['equal'])
        for index in [1,2,3,4,5,6]:
            changed=original.copy();changed[index]^=1
            self.assertFalse(compare_gpu_commands(trace(original),trace(changed))['equal'])
        modulated=original.copy();modulated[0]=0x24010203
        changed=modulated.copy();changed[0]^=1
        self.assertFalse(compare_gpu_commands(trace(modulated),trace(changed))['equal'])
        self.assertEqual(compare_gpu_commands(trace(original),trace(original)*2)['first_difference'],1)
        gouraud=[0x3a000000,0x00100020,0x00112233,0x00300040,0x07123456,0x00500060,0x00223344,0x00700080]
        padding=gouraud.copy();padding[4]=0x03123456
        self.assertTrue(compare_gpu_commands(trace(gouraud),trace(padding))['equal'])
        padding[4]^=1
        self.assertFalse(compare_gpu_commands(trace(gouraud),trace(padding))['equal'])
        for malformed in [b'',b'x',struct.pack('<I',0),struct.pack('<II',2,0)]:
            with self.assertRaises(ValueError):normalized_gpu_commands(malformed)

    def test_simulation_state_requires_complete_integer_evidence(self):
        state=dict(anim_frame=600,frame_count=800,loop_count=900,loop_ticks=1200,random_lcg=0xffffffff,random_bios=1)
        self.assertEqual(simulation_state(dict(simulation_state=state)),state)
        for invalid in [None,{},dict(state,random_lcg=-1),dict(state,loop_count=True),dict(state,anim_frame=2**32)]:
            with self.assertRaises(ValueError):simulation_state(dict(simulation_state=invalid))

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
