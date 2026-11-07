"""Synthetic PS1 palette/coverage fixtures, without game data."""
import importlib.util
import hashlib
import json
from pathlib import Path
import tempfile
import unittest
import numpy as np
spec=importlib.util.spec_from_file_location('hd_foreground',Path(__file__).resolve().parents[1]/'tools/hd/foreground.py')
module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)


class ForegroundTest(unittest.TestCase):
    def source(self,**kwargs):
        return dict(tpage=0,clut=128,w=4,h=1,u0=0,v0=0,x0=-162,y0=-120,depth=10,r0=128,g0=128,b0=128,codeFlags=2,**kwargs)

    def test_four_bit_palette_owns_zero_and_stp_coverage(self):
        vram=np.zeros((512,1024),np.uint16)
        vram[0,0]=0x3210;vram[2,:4]=[31,0,0x8000,31<<5]
        source=self.source();words,rgba=module.decode_sprite(vram,source)
        self.assertEqual(words.tolist(),[[31,0,0x8000,31<<5]])
        self.assertEqual(rgba[0,:,3].tolist(),[255,0,255,255])
        fields=list(source)
        view=dict(sourceCount=1,rows=[list(source.values())],batchList=[dict(firstSprite=0,spriteCount=1,hidden=1,skipCachedPackets=0)])
        sprites,coverage=module.layers(view,fields,vram)
        self.assertEqual(sprites[0][0]['semitransparent_texels'],1)
        self.assertEqual(int(np.count_nonzero(coverage)),2)
        self.assertTrue(sprites[0][0]['batches'][0]['hidden'])

    def test_eight_bit_subword_address_and_clut_offset(self):
        vram=np.zeros((512,1024),np.uint16);source=self.source()
        source.update(tpage=128|15,clut=128|1,u0=1,w=2)
        vram[0,960:962]=[0x0302,0x0504];vram[2,19:21]=[0x1234,0xabcd]
        words,_=module.decode_sprite(vram,source)
        self.assertEqual(words.tolist(),[[0x1234,0xabcd]])

    def test_observed_draw_uses_physical_buffer_offset_clip_and_window(self):
        vram=np.zeros((512,1024),np.uint16);vram[0,0]=0x3210;vram[2,:4]=[31,0,0x8000,31<<5]
        source=self.source();fields=list(source)
        view=dict(sourceCount=1,rows=[list(source.values())],batchList=[dict(firstSprite=0,spriteCount=1,hidden=0,skipCachedPackets=0)])
        sprites,_=module.layers(view,fields,vram)
        capture=dict(key='a',location=[1,2,3,1,1,1])
        draw=dict(position=[-162,-120],size=[4,1],uv=[0,0],clut=128,draw_mode=0xe1000000,
                  offset=[160,392],clip=[0,272,1,240],texture_window=0,mask_mode=0)
        audit=dict(format='pe2-gpu-state-audit-v1',complete=True,buffer_y=272,**capture,sprites=[draw])
        mask=module.observed_coverage(sprites,vram,audit,capture)
        self.assertEqual(int(np.count_nonzero(mask)),1)
        self.assertEqual(len(sprites[0][0]['observed_draws']),1)
        source.update(w=1,x0=0,y0=0)
        # A window forces bit 3 of U to one: texel 0 samples texel 8.
        vram[0,2]=3
        words,_=module.decode_sprite(vram,source,1|(1<<10))
        self.assertEqual(int(words[0,0]),31<<5)
        audit['complete']=False
        with self.assertRaises(ValueError):module.observed_coverage(sprites,vram,audit,capture)

    def test_direct_colour_wraps_uv_within_page(self):
        vram=np.zeros((512,1024),np.uint16);source=self.source()
        source.update(tpage=256|16,u0=255,v0=255,w=2,h=2)
        vram[511,255]=1;vram[511,0]=2;vram[256,255]=3;vram[256,0]=4
        words,_=module.decode_sprite(vram,source)
        self.assertEqual(words.tolist(),[[1,2],[3,4]])
        source['tpage']=384
        with self.assertRaises(ValueError):module.decode_sprite(vram,source)

    def test_capture_must_match_exact_location_and_mapped_file(self):
        capture=dict(format='pe2-static-view-survey-v2',matched_frames=30,key='a',location=[1,2,3,1,1,1])
        view={'file':9}
        scene=dict(room='room',unresolved=[],sprites={'views':[view]})
        catalog={'records':[dict(room='room',location=capture['location'],keys=['a'],mapped_file=9)]}
        self.assertIs(module.select_view(scene,catalog,capture),view)
        capture['key']='wrong'
        with self.assertRaises(ValueError):module.select_view(scene,catalog,capture)
        capture['key']='a';scene['unresolved']=[dict(block='sprites')]
        with self.assertRaises(ValueError):module.select_view(scene,catalog,capture)
        scene['sprites']['table']='SpriteViews'
        scene['unresolved']=[dict(block='sprites',what='SpriteViews[4]')]
        self.assertIs(module.select_view(scene,catalog,capture),view)
        scene['unresolved'][0]['what']='SpriteViews[8]'
        with self.assertRaises(ValueError):module.select_view(scene,catalog,capture)

    def test_survey_audit_rejects_changed_vram(self):
        with tempfile.TemporaryDirectory() as directory:
            root=Path(directory);scenes=root/'scenes';scenes.mkdir()
            location=[1,2,3,1,1,1];capture=dict(format='pe2-static-view-survey-v2',matched_frames=30,key='a',location=location)
            scene=dict(room='room',unresolved=[],sprites=dict(fields=[],views=[dict(file=9,sourceCount=0,rows=[],batchList=[])]))
            (scenes/'room.json').write_text(json.dumps(scene))
            data=bytes(1024*512*2)
            path=root/'1-2-3-1-1-1'/'0';path.mkdir(parents=True)
            (path/'report.json').write_text(json.dumps(capture));(path/'vram.bin').write_bytes(data)
            case=dict(room='room',location=location,key='a',parity_verified=True,
                      runs=[dict(report=capture,native_sha256=hashlib.sha256(data).hexdigest())])
            survey=root/'report.json';survey.write_text(json.dumps(dict(format='pe2-static-view-parity-survey-v1',selected_complete=True,cases=[case])))
            catalog={'records':[dict(room='room',location=location,keys=['a'],mapped_file=9)]}
            self.assertEqual(module.audit_survey(survey,scenes,catalog)['decoded'],1)
            (path/'vram.bin').write_bytes(bytes([1])+data[1:])
            report=module.audit_survey(survey,scenes,catalog)
            self.assertEqual(report['decoded'],0);self.assertEqual(report['unverified'],1)
            self.assertIn('VRAM changed',report['errors'][0]['error'])


if __name__=='__main__':unittest.main()
