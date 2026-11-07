#!/usr/bin/env python3
"""Check one settled real-game foreground pack on both physical buffers.

Requires owner discs and local candidate packs. This is not an artwork approval
or an all-room/transition verification. Captures contain local game data.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import zlib
from PIL import Image
from survey import startup_replay,validate_capture
from foreground_evidence import check_material_evidence,verify_empty_sources,compare_gpu_commands,simulation_state


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--binary',type=Path,default=Path('build-port/parasite-eve-ii-pc'))
    parser.add_argument('--disc',type=Path,required=True);parser.add_argument('--disc2',type=Path,required=True)
    parser.add_argument('--base-pack',type=Path,required=True)
    parser.add_argument('--combined-pack',type=Path,required=True)
    parser.add_argument('--location',required=True,help='stage,area,view,room,warp,variant')
    parser.add_argument('--key',required=True,help='16-digit native background key')
    parser.add_argument('--empty-sources',type=Path,help='Audited all-zero native sources; require unchanged material instead of visible HD')
    parser.add_argument('--output',type=Path,default=Path('build-hd-study/foreground-live-check'))
    args=parser.parse_args();location=list(map(int,args.location.split(',')))
    if len(location)!=6 or len(args.key)!=16:parser.error('Expected a six-component location and native key')
    int(args.key,16)
    context='-'.join(map(str,location[:4]));descriptor=f'{args.key}-{context}.pe2fg'
    root=args.output.resolve();root.mkdir(parents=True,exist_ok=True);(root/'report.json').unlink(missing_ok=True)
    empty_sources=verify_empty_sources(args.empty_sources,args.key,location,(args.combined_pack/descriptor).read_bytes()) if args.empty_sources else 0
    replay=root/'startup.pad';startup_replay(replay)
    identity=hashlib.sha256(args.binary.read_bytes()).hexdigest();results=[]
    def run(name,pack,wide,settle):
        destination=root/name;destination.mkdir(exist_ok=True)
        for filename in ['report.json','frame.ppm','vram.bin','gpu-state.json','gpu-commands.bin']:(destination/filename).unlink(missing_ok=True)
        with tempfile.TemporaryDirectory(prefix='profile-',dir=root) as profile:
            Path(profile,'settings.ini').write_text('scale=4\n')
            env={k:v for k,v in os.environ.items() if not k.startswith('PE2_')}
            env.update(PSYZ_HEADLESS='gpu',PSYZ_RASTER_CLOCK='virtual',SDL_AUDIODRIVER='dummy',PE2_SKIPINTRO='1',
                       PE2_CONFIG_DIR=profile,PE2_MEMORY_CARD_DIR=profile+'/cards',PE2_PAD_REPLAY=str(replay),
                       PE2_START_LOCATION=args.location,PE2_SURVEY_KEEP_VIEW='1',PE2_SURVEY_SETTLE_FRAMES=str(settle),
                       PE2_SURVEY_TARGET=','.join(map(str,location[:4]))+':'+args.key,PE2_SURVEY_OUTPUT=str(destination),
                       PE2_DUMP_GPU_STATE='1')
            if pack is not None:env['PE2_HD_BACKGROUNDS']=str(pack.resolve())
            with (destination/'run.log').open('w') as log:
                subprocess.run([str(args.binary.resolve()),'--disc',str(args.disc.resolve()),'--disc2',str(args.disc2.resolve()),
                                '--widescreen',str(wide)],env=env,stdout=log,stderr=subprocess.STDOUT,check=True,timeout=40)
        report,native=validate_capture(destination,dict(keys=[args.key],location=location),True)
        frame=(destination/'frame.ppm').read_bytes()
        results.append(dict(case=name,report=report,native_sha256=hashlib.sha256(native).hexdigest(),
                            frame_sha256=hashlib.sha256(frame).hexdigest()))
        (destination/'vram.bin.z').write_bytes(zlib.compress(native));(destination/'vram.bin').unlink()
        with Image.open(destination/'frame.ppm') as image:image.save(destination/'frame.png')
        (destination/'frame.ppm').unlink()
        return report,native,frame
    def require_same_commands(first,second):
        evidence=compare_gpu_commands((root/first/'gpu-commands.bin').read_bytes(),(root/second/'gpu-commands.bin').read_bytes())
        first_state=simulation_state(json.loads((root/first/'report.json').read_text()))
        second_state=simulation_state(json.loads((root/second/'report.json').read_text()))
        evidence.update(first=first,second=second,first_simulation=first_state,second_simulation=second_state,
                        simulation_equal=first_state==second_state)
        with (root/'input-comparisons.jsonl').open('a') as file:file.write(json.dumps(evidence)+'\n')
        assert evidence['simulation_equal'],(first,second,'different simulation state; renderer comparison is unverified',evidence)
        assert evidence['equal'],(first,second,'different original GPU inputs; renderer comparison is unverified',evidence)
    (root/'input-comparisons.jsonl').unlink(missing_ok=True)
    original=run('original',None,0,30)
    for name,wide,settle in [('classic',0,30),('wide30',1,30),('wide31',1,31)]:
        base=run(name+'-base',args.base_pack,wide,settle)
        combined=run(name+'-combined',args.combined_pack,wide,settle)
        clock_fields=['draw_frame','game_tick','vsync_count']
        assert all(isinstance(pair[0].get(k),int) for pair in [base,combined] for k in clock_fields),(name,'missing simulation clock evidence')
        assert [base[0][k] for k in clock_fields]==[combined[0][k] for k in clock_fields],(name,'different simulation moments')
        require_same_commands(name+'-base',name+'-combined')
        assert base[1]==combined[1],(name,'foreground changed native VRAM')
        assert base[0]['buffer_y']==combined[0]['buffer_y'],(name,'different physical buffers')
        changed=base[2]!=combined[2]
        replacements=combined[0]['foreground_replacements']
        try:check_material_evidence(changed,replacements,empty=bool(empty_sources))
        except AssertionError as error:raise AssertionError(name,str(error)) from error
        if not wide:
            require_same_commands('original',name+'-base')
            assert base[1]==original[1],'Base material changed the original native framebuffer'
        if not wide:classic=base
    for name in ['bad-metadata','missing-atlas']:
        with tempfile.TemporaryDirectory(prefix=name+'-',dir=root) as directory:
            pack=Path(directory);shutil.copytree(args.combined_pack,pack,dirs_exist_ok=True)
            data=bytearray((pack/descriptor).read_bytes())
            if name=='bad-metadata':data[0]^=255;(pack/descriptor).write_bytes(data)
            else:(pack/f'{int.from_bytes(data[16:24],"little"):016x}.fg.png').unlink()
            capture=run(name,pack,0,30)
            require_same_commands('classic-base',name)
            assert not capture[0]['foreground_replacements'] and capture[1:]==classic[1:],name
    if hashlib.sha256(args.binary.read_bytes()).hexdigest()!=identity:raise RuntimeError('Executable changed during check')
    (root/'report.json').write_text(json.dumps(dict(passed=True,binary_sha256=identity,cases=results,empty_sources_verified=empty_sources,
        scope='One forced static camera. v3 captures present the completed draw buffer. '+('Audited empty sources require exact unchanged material; no visible HD activation is claimed.' if empty_sources else 'Both physical buffers require active foreground replacements in 16:9.')),indent=2)+'\n')
    print('PASS: '+('verified empty foreground' if empty_sources else 'live foreground material')+', both buffer parities, exact native VRAM and malformed-pack fallback')


if __name__=='__main__':main()
