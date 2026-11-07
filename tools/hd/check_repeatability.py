#!/usr/bin/env python3
"""Measure static-camera repeatability, optionally interleaving HD pack variants.

Uses private profiles and owner discs. Captures contain game data: keep output
local and ignored. Input divergence is evidence of incomparable runs, never an
isolated renderer defect or proof that HD caused a change.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import subprocess
import tempfile
import zlib
from foreground_evidence import compare_gpu_commands,simulation_state
from survey import startup_replay,validate_capture


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--binary',type=Path,default=Path('build-port/parasite-eve-ii-pc'))
    for name in ['disc','disc2','output']:parser.add_argument('--'+name,type=Path,required=True)
    parser.add_argument('--location',required=True)
    parser.add_argument('--key',required=True)
    parser.add_argument('--runs',type=int,default=6,help='Repetitions of the complete variant sequence')
    parser.add_argument('--wide',type=int,choices=[0,1],default=0)
    parser.add_argument('--settle',type=int,default=31)
    parser.add_argument('--base-pack',type=Path)
    parser.add_argument('--combined-pack',type=Path)
    args=parser.parse_args();location=list(map(int,args.location.split(',')))
    if len(location)!=6 or len(args.key)!=16 or not 1<=args.runs<=100 or not 30<=args.settle<=36000:
        parser.error('Expected six location components, 16-digit key, 1..100 runs and 30..36000 settle frames')
    int(args.key,16)
    if bool(args.base_pack)!=bool(args.combined_pack):parser.error('Supply both pack variants or neither')
    root=args.output.resolve();root.mkdir(parents=True,exist_ok=False)
    replay=root/'startup.pad';startup_replay(replay,frames=max(8001,2*args.settle+4000))
    binary=args.binary.resolve();identity=hashlib.sha256(binary.read_bytes()).hexdigest()
    variants=[('original',None)]
    if args.base_pack:variants += [('base',args.base_pack),('combined',args.combined_pack)]
    rows=[];reference=None;variant_references={}
    def save(complete=False):
        (root/'report.json').write_text(json.dumps(dict(format='pe2-static-repeatability-v1',binary_sha256=identity,
            complete=complete,expected_runs=args.runs*len(variants),runs=rows,
            repeatable_within_variants=complete and all(row['equal_to_variant_reference'] for row in rows),
            native_inputs_match_original=complete and all(row['native_and_inputs_equal'] for row in rows),
            scope='One forced static camera; exact outputs, observed simulation state and original GP0 inputs. No traversal, artwork approval, all-game determinism or causal attribution.'),indent=2)+'\n')
    save()
    for repetition in range(args.runs):
        for mode,pack in variants:
            if hashlib.sha256(binary.read_bytes()).hexdigest()!=identity:raise RuntimeError('Executable changed during check')
            name=f'{repetition}-{mode}';destination=root/name;destination.mkdir()
            with tempfile.TemporaryDirectory(prefix='profile-',dir=root) as profile:
                Path(profile,'settings.ini').write_text('scale=4\n')
                env={k:v for k,v in os.environ.items() if not k.startswith('PE2_')}
                env.update(PSYZ_HEADLESS='gpu',PSYZ_RASTER_CLOCK='virtual',SDL_AUDIODRIVER='dummy',PE2_SKIPINTRO='1',
                    PE2_CONFIG_DIR=profile,PE2_MEMORY_CARD_DIR=profile+'/cards',PE2_PAD_REPLAY=str(replay),
                    PE2_PAD_RECORD=str(destination/'input.pad'),
                    PE2_START_LOCATION=args.location,PE2_SURVEY_KEEP_VIEW='1',PE2_SURVEY_SETTLE_FRAMES=str(args.settle),
                    PE2_SURVEY_TARGET=','.join(map(str,location[:4]))+':'+args.key,
                    PE2_SURVEY_OUTPUT=str(destination),PE2_DUMP_GPU_STATE='1')
                if pack:env['PE2_HD_BACKGROUNDS']=str(pack.resolve())
                command=[str(binary),'--disc',str(args.disc.resolve()),'--disc2',str(args.disc2.resolve()),'--widescreen',str(args.wide)]
                if pack is None:command.append('--no-hd-backgrounds')
                with (destination/'run.log').open('w') as log:
                    subprocess.run(command,env=env,stdout=log,stderr=subprocess.STDOUT,check=True,timeout=40)
            report,native=validate_capture(destination,dict(keys=[args.key],location=location),True)
            commands=(destination/'gpu-commands.bin').read_bytes();frame=(destination/'frame.ppm').read_bytes()
            inputs=(destination/'input.pad').read_bytes()
            state=simulation_state(report);clocks={k:report[k] for k in ['draw_frame','game_tick','vsync_count','buffer_y']}
            row=dict(case=name,mode=mode,report=report,native_sha256=hashlib.sha256(native).hexdigest(),frame_sha256=hashlib.sha256(frame).hexdigest(),
                input_sha256=hashlib.sha256(inputs).hexdigest(),input_samples=inputs.count(b'\n')-1)
            if reference is None:reference=(commands,native,frame,state,clocks,inputs,report.get('player_root'))
            comparison=compare_gpu_commands(reference[0],commands)
            row.update(commands=comparison,native_equal=reference[1]==native,frame_equal=reference[2]==frame,
                       simulation_equal=reference[3]==state,clocks_equal=reference[4]==clocks,input_equal=reference[5]==inputs,player_root_equal=reference[6]==report.get('player_root'))
            local=variant_references.setdefault(mode,(commands,native,frame,state,clocks,inputs,report.get('player_root')))
            row['equal_to_variant_reference']=(compare_gpu_commands(local[0],commands)['equal'] and
                local[1]==native and local[2]==frame and local[3]==state and local[4]==clocks and local[5]==inputs and local[6]==report.get('player_root'))
            # HD material intentionally changes frame RGB; assess native/input
            # repeatability separately when comparing across pack variants.
            row['native_and_inputs_equal']=comparison['equal'] and row['native_equal'] and row['simulation_equal'] and row['clocks_equal'] and row['input_equal'] and row['player_root_equal']
            (destination/'vram.bin.z').write_bytes(zlib.compress(native));(destination/'vram.bin').unlink()
            rows.append(row);save();print(name,row['native_and_inputs_equal'],flush=True)
    if hashlib.sha256(binary.read_bytes()).hexdigest()!=identity:raise RuntimeError('Executable changed during check')
    save(True)
    print('Completed: inspect report.json for per-run differences; no causal attribution is made.')


if __name__=='__main__':main()
