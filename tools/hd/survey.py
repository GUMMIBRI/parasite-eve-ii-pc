#!/usr/bin/env python3
"""Forced static-camera off/on parity survey; not a natural gameplay replay.

A case passes only when both runs capture the expected native source and exact
logical location after settling. Original/HD image data stays in ignored output.
"""
import argparse
from concurrent.futures import ThreadPoolExecutor,as_completed
import hashlib
import json
import os
from pathlib import Path
import subprocess
import tempfile
import zlib

from PIL import Image


def startup_replay(path,frames=8001):
    with path.open('w') as output:
        output.write('PE2PAD 1\n')
        for index in range(frames):
            mask=8 if 150<=index<158 else 0
            if 200<=index<4000 and index%60<8:mask|=0x4000
            reply=bytes([0,0x41,(~mask)&255,((~mask)>>8)&255])+bytes(30)
            output.write(f'{index} {reply.hex()}\n')


def validate_capture(directory,target,require_gpu_state=False):
    report=json.loads((directory/'report.json').read_text())
    if report.get('format')!='pe2-static-view-survey-v2' or report.get('matched_frames',0)<30:
        raise ValueError('Missing current settled-frame evidence')
    if report['key']!=target['keys'][0] or report['location']!=target['location']:
        raise ValueError(f'Captured a different source/location: {report}')
    if require_gpu_state:
        audit=json.loads((directory/'gpu-state.json').read_text())
        if audit.get('format')!='pe2-gpu-state-audit-v1' or not audit.get('complete') or audit.get('buffer_y') not in [0,272] or audit.get('key')!=report['key'] or audit.get('location')!=report['location']:
            raise ValueError('GPU-state traversal is incomplete or belongs to another frame')
    native=(directory/'vram.bin').read_bytes()
    if len(native)!=1024*512*2:raise ValueError('Incomplete VRAM capture')
    with Image.open(directory/'frame.ppm') as image:
        if image.size!=(report['width'],report['height']):raise ValueError('Capture dimensions disagree')
        if not image.getbbox():raise ValueError('Black loading frame is not valid survey evidence')
    return report,native


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--catalog',type=Path,default=Path('build-hd-study/view-catalog.json'))
    parser.add_argument('--binary',type=Path,default=Path('build-port/parasite-eve-ii-pc'))
    parser.add_argument('--disc',type=Path,required=True)
    parser.add_argument('--disc2',type=Path,required=True)
    parser.add_argument('--output',type=Path,default=Path('build-hd-study/survey'))
    parser.add_argument('--room')
    parser.add_argument('--limit',type=int,default=0,help='0 tests every eligible candidate; scope is recorded')
    parser.add_argument('--jobs',type=int,default=4)
    parser.add_argument('--timeout',type=float,default=40)
    parser.add_argument('--gpu-state',action='store_true',help='Require a complete ordered GPU-state audit for each capture')
    parser.add_argument('--backend',choices=['software','gpu'],default='software')
    args=parser.parse_args()
    if args.limit<0 or args.jobs<1:parser.error('Invalid limit/jobs')
    catalog=json.loads(args.catalog.read_text())
    eligible=[r for r in catalog['records'] if r['eligible_for_start_test']]
    selected=[r for r in eligible if not args.room or r['room']==args.room]
    if args.limit:selected=selected[:args.limit]
    if not selected:raise SystemExit('No eligible views selected')
    root=args.output.resolve();root.mkdir(parents=True,exist_ok=True)
    (root/'report.json').unlink(missing_ok=True)
    replay=root/'startup.pad';startup_replay(replay)
    binary_hash=hashlib.sha256(args.binary.read_bytes()).hexdigest()
    def run_case(target):
        case='-'.join(map(str,target['location']))
        directory=root/case;directory.mkdir(exist_ok=True)
        runs=[];data=[]
        for wide in [0,1]:
            capture=directory/str(wide);capture.mkdir(exist_ok=True)
            for name in ['report.json','frame.ppm','vram.bin','gpu-state.json']:(capture/name).unlink(missing_ok=True)
            with tempfile.TemporaryDirectory(prefix='profile-',dir=directory) as profile:
                env={k:v for k,v in os.environ.items() if not k.startswith('PE2_')}
                env.update(PSYZ_HEADLESS='1' if args.backend=='software' else 'gpu',PSYZ_RASTER_CLOCK='virtual',SDL_AUDIODRIVER='dummy',PE2_SKIPINTRO='1',
                    PE2_CONFIG_DIR=profile,PE2_MEMORY_CARD_DIR=str(Path(profile)/'cards'),PE2_PAD_REPLAY=str(replay),
                    PE2_START_LOCATION=','.join(map(str,target['location'])),PE2_SURVEY_KEEP_VIEW='1',
                    PE2_SURVEY_TARGET=','.join(map(str,target['location'][:4]))+':'+target['keys'][0],PE2_SURVEY_OUTPUT=str(capture))
                if args.gpu_state:env['PE2_DUMP_GPU_STATE']='1'
                command=[str(args.binary.resolve()),'--disc',str(args.disc.resolve()),'--disc2',str(args.disc2.resolve()),'--widescreen',str(wide)]
                with (capture/'run.log').open('w') as log:
                    process=subprocess.run(command,env=env,stdout=log,stderr=subprocess.STDOUT,timeout=args.timeout)
                logPath=capture/'run.log';logData=logPath.read_bytes()
                warnings=logData.count(b'unsupported command')
                if len(logData)>256*1024:
                    (capture/'run.log.z').write_bytes(zlib.compress(logData));logPath.unlink()
                if process.returncode:raise RuntimeError(f'{case}/{wide}: exited {process.returncode}')
            if not (capture/'report.json').is_file():
                raise RuntimeError(f'{case}/{wide}: replay ended without a settled target capture')
            report,native=validate_capture(capture,target,args.gpu_state)
            image=(capture/'frame.ppm').read_bytes()
            runs.append(dict(widescreen=wide,report=report,renderer_warnings=warnings,
                             gpu_state_sha256=hashlib.sha256((capture/'gpu-state.json').read_bytes()).hexdigest() if args.gpu_state else None,
                             native_sha256=hashlib.sha256(native).hexdigest(),frame_sha256=hashlib.sha256(image).hexdigest()))
            data.append((native,image))
            (capture/'vram.bin.z').write_bytes(zlib.compress(native));(capture/'vram.bin').unlink()
            with Image.open(capture/'frame.ppm') as rendered:rendered.save(capture/'frame.png')
            (capture/'frame.ppm').unlink()
        if data[0]!=data[1]:raise RuntimeError(f'{case}: widescreen fallback changed VRAM or rendered pixels')
        return dict(location=target['location'],room=target['room'],key=target['keys'][0],parity_verified=True,
                    forced_static_view=True,runs=runs)
    passed=[];errors=[]
    with ThreadPoolExecutor(max_workers=args.jobs) as pool:
        futures={pool.submit(run_case,target):target for target in selected}
        for future in as_completed(futures):
            target=futures[future]
            try:passed.append(future.result())
            except Exception as error:errors.append(dict(location=target['location'],room=target['room'],error=str(error)))
            print(f'{len(passed)} matched parity, {len(errors)} unverified / {len(selected)}',flush=True)
    if hashlib.sha256(args.binary.read_bytes()).hexdigest()!=binary_hash:raise SystemExit('Binary changed during survey; results cannot be attributed to one build')
    report=dict(format='pe2-static-view-parity-survey-v1',binary_sha256=binary_hash,
                scope=dict(eligible_total=len(eligible),selected=len(selected),requested_room=args.room,limit=args.limit,gpu_state=args.gpu_state,backend=args.backend,
                           note='Forced static cameras; excludes unresolved source entries; not physical traversal or all-game correctness.'),
                selected_complete=True,parity_verified=len(passed),unverified=len(errors),
                cases=passed,errors=errors,source_diagnostics=catalog.get('source_diagnostics',[]))
    (root/'report.json').write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps({k:report[k] for k in ['scope','parity_verified','unverified']},indent=2))
    if errors:raise SystemExit(1)


if __name__=='__main__':main()
