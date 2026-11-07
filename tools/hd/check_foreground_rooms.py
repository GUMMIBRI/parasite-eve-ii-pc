#!/usr/bin/env python3
"""Exercise HD foreground integration across previously verified static cameras.

Builds synthetic colour materials from audited native texture references. All
fixtures/captures contain disc-derived data: keep output local and ignored.
This verifies renderer integration, never artwork, traversal or player masks.
"""
import argparse
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import sys
import numpy as np
from PIL import Image
from foreground import layers,read_vram,select_view
from foreground_pack import build as build_foreground
from pack import build as build_background,identity


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--survey',type=Path,default=Path('build-hd-study/state-clips/report.json'))
    parser.add_argument('--scenes',type=Path,default=Path('build-hd-study/scenes'))
    parser.add_argument('--catalog',type=Path,default=Path('build-hd-study/view-catalog.json'))
    parser.add_argument('--native',type=Path,default=Path('build-hd-study/native-catalog/native'))
    parser.add_argument('--binary',type=Path,default=Path('build-port/parasite-eve-ii-pc'))
    parser.add_argument('--disc',type=Path,required=True);parser.add_argument('--disc2',type=Path,required=True)
    parser.add_argument('--location',action='append',help='Select a six-component location; repeat to select more')
    parser.add_argument('--limit',type=int,default=0)
    parser.add_argument('--output',type=Path,default=Path('build-hd-study/foreground-room-check'))
    args=parser.parse_args()
    survey=json.loads(args.survey.read_text());catalog=json.loads(args.catalog.read_text())
    if survey.get('format')!='pe2-static-view-parity-survey-v1' or not survey.get('selected_complete'):
        raise ValueError('A completed source survey is required')
    selected=set(args.location or [])
    if args.limit<0:parser.error('--limit must be nonnegative')
    root=args.output.resolve();root.mkdir(parents=True,exist_ok=True)
    binary_hash=hashlib.sha256(args.binary.read_bytes()).hexdigest();results=[];errors=[];eligible=[]
    for case in survey['cases']:
        name='-'.join(map(str,case['location']))
        if selected and ','.join(map(str,case['location'])) not in selected:continue
        if not case['parity_verified']:continue
        capture_dir=args.survey.parent/name/'0'
        capture=json.loads((capture_dir/'report.json').read_text())
        scene=json.loads((args.scenes/(case['room']+'.json')).read_text())
        view=select_view(scene,catalog,capture)
        if view['sourceCount']:eligible.append((case,capture_dir,capture,scene,view))
    if selected- {','.join(map(str,c[0]['location'])) for c in eligible}:
        raise ValueError('Requested location has no verified source-bearing capture')
    if args.limit:eligible=eligible[:args.limit]
    if not eligible:raise ValueError('No source-bearing cameras selected')
    def save():
        (root/'report.json').write_text(json.dumps(dict(format='pe2-foreground-room-check-v1',
            binary_sha256=binary_hash,source_survey_sha256=hashlib.sha256(args.survey.read_bytes()).hexdigest(),
            selected=len(eligible),completed=len(results)+len(errors),passed=not errors and len(results)==len(eligible),
            cases=results,errors=errors,scope='Synthetic materials; forced static cameras, both buffers; no artwork or player-occlusion approval.'),indent=2)+'\n')
    save()
    for case,capture_dir,capture,scene,view in eligible:
        name='-'.join(map(str,case['location']));destination=root/name;destination.mkdir(exist_ok=True)
        try:
            if capture!=case['runs'][0]['report'] or capture['location']!=case['location'] or capture['key']!=case['key']:
                raise ValueError('Source capture identity changed')
            raw=read_vram(capture_dir)
            if hashlib.sha256(raw).hexdigest()!=case['runs'][0]['native_sha256']:raise ValueError('Source VRAM changed')
            sprites,_=layers(view,scene['sprites']['fields'],np.frombuffer(raw,dtype='<u2').reshape(512,1024))
            source=destination/'sources';source.mkdir(exist_ok=True)
            records=[]
            for record,_,words in sprites:
                (source/f'sprite-{record["index"]:04d}.rgb555').write_bytes(words.astype('<u2').tobytes());records.append(record)
            report=dict(format='pe2-foreground-source-audit-v1',capture=capture,sprites=records)
            (source/'report.json').write_text(json.dumps(report,indent=2)+'\n')
            native=(args.native/(case['key']+'.rgb555')).read_bytes()
            if identity(native)!=int(case['key'],16):raise ValueError('Native background key mismatch')
            base=destination/'base';combined=destination/'combined';base.mkdir(exist_ok=True);combined.mkdir(exist_ok=True)
            key,metadata,atlas=build_background(native,Image.new('RGB',(1792,960),(40,60,80)),-64,384)
            (base/f'{key:016x}.pe2bg').write_bytes(metadata);atlas.save(base/f'{key:016x}.png')
            shutil.copytree(base,combined,dirs_exist_ok=True)
            key,metadata,atlas=build_foreground(report,source,Image.new('RGB',(1792,960),(200,100,60)))
            context='-'.join(map(str,case['location'][:4]))
            (combined/f'{case["key"]}-{context}.pe2fg').write_bytes(metadata);atlas.save(combined/f'{key:016x}.fg.png')
            command=[sys.executable,str(Path(__file__).with_name('check_foreground_live.py')),
                '--binary',str(args.binary),'--disc',str(args.disc),'--disc2',str(args.disc2),
                '--base-pack',str(base),'--combined-pack',str(combined),'--location',','.join(map(str,case['location'])),
                '--key',case['key'],'--output',str(destination/'live')]
            if not any(r['covered_texels'] for r in records):command+=['--empty-sources',str(source)]
            with (destination/'check.log').open('w') as log:subprocess.run(command,stdout=log,stderr=subprocess.STDOUT,check=True,timeout=420)
            checked=json.loads((destination/'live/report.json').read_text())
            if not checked.get('passed') or checked['binary_sha256']!=binary_hash:raise ValueError('Incomplete or changed executable evidence')
            results.append(dict(location=case['location'],room=case['room'],key=case['key'],sources=len(records),empty_sources_verified=checked.get('empty_sources_verified',0),
                runs=[dict(case=r['case'],buffer_y=r['report']['buffer_y'],replacements=r['report']['foreground_replacements']) for r in checked['cases']]))
            print(f'PASS {name}: {len(records)} sources',flush=True)
        except Exception as error:
            errors.append(dict(location=case['location'],room=case['room'],error=str(error),
                diagnostic=(destination/'check.log').read_text()[-2000:] if (destination/'check.log').is_file() else None))
            print(f'UNVERIFIED {name}: {error}',flush=True)
        save()
    if hashlib.sha256(args.binary.read_bytes()).hexdigest()!=binary_hash:
        errors.append(dict(error='Executable changed during sweep'));save()
        raise RuntimeError('Executable changed during sweep')
    print(f'{len(results)} passed; {len(errors)} unverified',flush=True)
    if errors:raise SystemExit(1)


if __name__=='__main__':main()
