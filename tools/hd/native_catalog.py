#!/usr/bin/env python3
"""Decode every inventoried BS through the game's native VLC/MDEC code.

Outputs are local disc-derived artwork inputs, never repository assets.
The input inventory must be complete; incomplete decode results fail the run.
"""
import argparse
from concurrent.futures import ThreadPoolExecutor,as_completed
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess

from PIL import Image
from pack import identity,native_image


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--inventory',type=Path,default=Path('build-hd-study/inventory/inventory.json'))
    parser.add_argument('--assets',type=Path,default=Path('assets/USA'))
    parser.add_argument('--decoder',type=Path,default=Path('build-port/hd_native_decode'))
    parser.add_argument('--output',type=Path,default=Path('build-hd-study/native-catalog'))
    parser.add_argument('--jobs',type=int,default=6)
    args=parser.parse_args()
    if args.jobs<1:parser.error('--jobs must be positive')
    inventory=json.loads(args.inventory.read_text())
    if inventory['summary']['missing']:raise SystemExit('Inventory has missing sources')
    destination=args.output.resolve();destination.mkdir(parents=True,exist_ok=True)
    (destination/'index.json').unlink(missing_ok=True)
    native=destination/'native';native.mkdir(exist_ok=True)
    jobs={}
    for record in inventory['records']:
        path=args.assets/record['raw_source']
        if not path.is_file():raise SystemExit(f'Missing exact BS input: {path}')
        digest=hashlib.sha256(path.read_bytes()).hexdigest()
        if digest!=record['raw_sha256']:raise SystemExit(f'Input changed since inventory: {path}')
        jobs.setdefault(digest,path.resolve())
    def decode(job):
        digest,path=job
        temporary=destination/(digest+'.tmp.rgb555')
        env={**os.environ,'PSYZ_HEADLESS':'1','SDL_AUDIODRIVER':'dummy'}
        result=subprocess.run([str(args.decoder.resolve()),str(path),str(temporary)],env=env,capture_output=True,text=True,timeout=30)
        if result.returncode:raise RuntimeError(f'{path}: {result.returncode}: {result.stderr[-600:]}')
        reported=result.stdout.strip().splitlines()[-1]
        if not re.fullmatch('[0-9a-f]{16}',reported):raise RuntimeError(f'Invalid decoder response: {reported}')
        data=temporary.read_bytes()
        if len(data)!=153600 or identity(data)!=int(reported,16):raise RuntimeError(f'Invalid native output: {path}')
        target=native/(reported+'.rgb555')
        if target.exists() and target.read_bytes()!=data:raise RuntimeError('Native identity collision')
        temporary.replace(target)
        # Each source has one job; equal native identities may atomically replace identical PNGs.
        png=destination/(digest+'.tmp.png')
        Image.fromarray(native_image(data)).save(png);png.replace(native/(reported+'.png'))
        return digest,dict(key=reported,native_sha256=hashlib.sha256(data).hexdigest(),native='native/'+reported+'.rgb555',image='native/'+reported+'.png')
    decoded={};errors={}
    with ThreadPoolExecutor(max_workers=args.jobs) as pool:
        futures={pool.submit(decode,job):job[0] for job in jobs.items()}
        for future in as_completed(futures):
            digest=futures[future]
            try:digest,data=future.result();decoded[digest]=data
            except Exception as error:errors[digest]=str(error)
            if (len(decoded)+len(errors))%200==0:print(f'{len(decoded)} decoded, {len(errors)} errors / {len(jobs)}',flush=True)
    records=[{**record,**decoded.get(record['raw_sha256'],{}),'runtime_verified':False} for record in inventory['records']]
    report=dict(format='pe2-native-background-catalog-v1',decoder_sha256=hashlib.sha256(args.decoder.read_bytes()).hexdigest(),
        note='Decoded with the game implementation, not a complete runtime room/view survey.',
        summary=dict(records=len(records),unique_bs=len(jobs),decoded_bs=len(decoded),unique_native=len({v['key'] for v in decoded.values()}),errors=len(errors)),
        errors=errors,records=records)
    (destination/'index.json').write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps(report['summary'],indent=2))
    if errors:raise SystemExit(1)


if __name__=='__main__':main()
