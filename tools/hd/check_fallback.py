#!/usr/bin/env python3
"""Compare actual GPU frames and VRAM with widescreen requested off/on and no pack.

Supply an existing deterministic input replay and a tick it reaches. Uses isolated
profiles, private cards and a hidden GPU window. Captures are local game data.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import subprocess
import tempfile


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--binary',type=Path,required=True)
    parser.add_argument('--disc',type=Path,required=True)
    parser.add_argument('--disc2',type=Path)
    parser.add_argument('--replay',type=Path,required=True)
    parser.add_argument('--tick',type=int,default=6000)
    parser.add_argument('--output',type=Path,default=Path('build-hd-study/fallback-check'))
    parser.add_argument('--software-baseline',type=Path)
    args=parser.parse_args()
    args.output.mkdir(parents=True,exist_ok=True)
    (args.output/'report.json').unlink(missing_ok=True)
    runs=[]
    for backend in ['1','gpu']:
        for wide in [0,1]:
            destination=args.output/('software' if backend=='1' else 'gpu')/str(wide)
            destination.mkdir(parents=True,exist_ok=True)
            for capture in ['frame.ppm','vram.bin']:(destination/capture).unlink(missing_ok=True)
            # A new profile prevents an old preference or card from changing the replay.
            with tempfile.TemporaryDirectory(prefix='profile-',dir=destination) as profile:
                env={**os.environ,'PSYZ_HEADLESS':backend,'SDL_AUDIODRIVER':'dummy',
                     'PE2_SKIPINTRO':'1','PE2_CONFIG_DIR':str(Path(profile).resolve()),
                     'PE2_MEMORY_CARD_DIR':str((Path(profile)/'cards').resolve()),
                     'PE2_PAD_REPLAY':str(args.replay.resolve()),
                     'PE2_DUMP_FRAME':f'{args.tick}:{destination.resolve()}/frame.ppm',
                     'PE2_DUMP_VRAM':f'{args.tick}:{destination.resolve()}/vram.bin'}
                # Explicit inputs take precedence over inherited development overrides.
                for name in ['PE2_DISC','PE2_DISC2','PE2_WARP','PE2_START_LOCATION',
                             'PE2_PAD_CONTROL','PE2_PAD_CONTROL_FIFO','PE2_PAD_RECORD',
                             'PE2_HD_BACKGROUNDS','PE2_DUMP_BACKGROUNDS','PE2_AUTOPRESS','PE2_PAD_HOLD','PE2_DEBUG_PORT','PE_HD_BACKGROUNDS']:
                    env.pop(name,None)
                command=[str(args.binary.resolve()),str(args.disc.resolve()),'--widescreen',str(wide)]
                if args.disc2:command+=['--disc2',str(args.disc2.resolve())]
                with (destination/'run.log').open('w') as log:
                    subprocess.run(command,env=env,stdout=log,stderr=subprocess.STDOUT,check=True,timeout=120)
            captures={name:(destination/name).read_bytes() for name in ['frame.ppm','vram.bin']}
            if len(captures['vram.bin'])!=1024*512*2:raise RuntimeError('Incomplete VRAM capture')
            runs.append(dict(backend=backend,widescreen=wide,sha256={name:hashlib.sha256(data).hexdigest() for name,data in captures.items()}))
        if runs[-2]['sha256']!=runs[-1]['sha256']:
            raise RuntimeError(f'Fallback altered native VRAM or presentation for {backend}')
    if args.software_baseline and args.software_baseline.read_bytes()!=(args.output/'software/0/vram.bin').read_bytes():
        raise RuntimeError('Widescreen-off VRAM differs from the supplied pre-change software baseline')
    report=dict(passed=True,scope='This replay/checkpoint only; no pack; software and hidden GPU.',tick=args.tick,runs=runs)
    (args.output/'report.json').write_text(json.dumps(report,indent=2)+'\n')
    print('PASS: exact off/on frame and VRAM parity on software and hidden GPU')


if __name__=='__main__':main()
