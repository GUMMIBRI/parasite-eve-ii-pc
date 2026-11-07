#!/usr/bin/env python3
"""Inventory locally extracted backgrounds; outputs contain disc-derived data.

Run after peassets extraction. Keep the output in an ignored build directory.
Source file indices are mapped view files, not proof of reachable logical views.
"""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path
import re
import shutil
import sys
from concurrent.futures import ProcessPoolExecutor

# These authored renderers need live checks before accepting static replacements.
SPECIAL = {
    'akropolis_square': 'scrolling panorama',
    'shelter_r47': 'scrolling backdrop',
    'shelter_b1_pod_access_tunnel': 'scripted scrolling image',
    'dryfield_underpass': 'depth-sorted foreground sprites',
    'neo_ark_garden': 'depth-sorted foreground sprites',
    'neo_ark_pyramid': 'puzzle overlay',
    'dryfield_night_water_hole': 'animated water overlays',
    'akropolis_west_elevator_hall': 'additive light effect',
}


def inventory(manifest: dict, assets: Path) -> dict:
    from PIL import Image
    records = []
    for stage, data in sorted(manifest.items()):
        folders = data.get('folders', {})
        if 'files' in data:
            folders = {name: {'file0': files} for name, files in data['files'].items()}
        for folder, files in sorted(folders.items()):
            for file_id, chunks in sorted(files.items()):
                for chunk, desc in sorted(chunks.items()):
                    if not isinstance(desc, dict) or desc.get('type') != 'room_background':
                        continue
                    source = assets / desc['path']
                    relative = Path(desc['path']).with_suffix('.bs')
                    raw = assets / 'raw' / relative if relative.parts[0]=='bs' else assets / 'raw/bs' / relative
                    match = re.fullmatch(r'file(\d+)', file_id)
                    record = dict(stage=stage, folder=folder, file=file_id,
                                  mapped_view_file=int(match[1]) if match else None,
                                  chunk=chunk, source=desc['path'], raw_source=str(raw.relative_to(assets)),
                                  exists=source.is_file() or raw.is_file(),
                                  review=SPECIAL.get(folder, 'unverified static candidate'),
                                  runtime_verified=False)
                    if stage == 'stage0':
                        record['review'] = 'non-field screen: classify separately'
                    if source.is_file():
                        with Image.open(source) as image:
                            rgb = image.convert('RGB')
                            record.update(size=list(rgb.size),
                                file_sha256=hashlib.sha256(source.read_bytes()).hexdigest(),
                                pixels_sha256=hashlib.sha256(rgb.tobytes()).hexdigest())
                    if raw.is_file():
                        record['raw_sha256']=hashlib.sha256(raw.read_bytes()).hexdigest()
                    records.append(record)
    groups = Counter(r['pixels_sha256'] for r in records if 'pixels_sha256' in r)
    return dict(format='pe2-background-inventory-v1',
        note='Offline manifest inventory; logical-view reachability, animation and foreground coverage require runtime verification. No artwork approved.',
        summary=dict(records=len(records), missing=sum(not r['exists'] for r in records),
                     unique_rgb=len(groups), unique_raw=len({r['raw_sha256'] for r in records if 'raw_sha256' in r}), stages=dict(Counter(r['stage'] for r in records)),
                     dimensions=dict(Counter('x'.join(map(str,r['size'])) for r in records if 'size' in r))),
        records=records)


def export_source(job):
    from PIL import Image
    source,target=job
    if not target.exists():
        if source.suffix=='.bs':
            sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'peassets'))
            from bs_codec import decode_bs_file
            image,_=decode_bs_file(source)
            image.save(target)
        else:shutil.copyfile(source,target)
    with Image.open(target) as image:
        rgb=image.convert('RGB')
        return target.stem,dict(size=list(rgb.size),pixels_sha256=hashlib.sha256(rgb.tobytes()).hexdigest())


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--assets', type=Path, default=Path('assets/USA'))
    parser.add_argument('--output', type=Path, default=Path('build-hd-study/inventory'))
    parser.add_argument('--jobs', type=int, default=6)
    parser.add_argument('--export', action='store_true', help='Copy one source PNG per unique RGB image for local artwork study')
    args = parser.parse_args()
    report = inventory(json.loads((args.assets/'stages.json').read_text()), args.assets)
    args.output.mkdir(parents=True, exist_ok=True)
    (args.output/'inventory.json').write_text(json.dumps(report, indent=2)+'\n')
    if args.export:
        destination=args.output/'sources'; destination.mkdir(exist_ok=True)
        jobs={}
        for record in report['records']:
            if not record['exists']:continue
            key=record.get('raw_sha256',record.get('pixels_sha256'))
            source=args.assets/record['source']
            if not source.is_file():source=args.assets/record['raw_source']
            jobs[key]=(source,destination/(key+'.png'))
        with ProcessPoolExecutor(max_workers=args.jobs) as pool:
            decoded=dict(pool.map(export_source,jobs.values()))
        for record in report['records']:
            key=record.get('raw_sha256',record.get('pixels_sha256'))
            if key in decoded:record.update(decoded[key],exported='sources/'+key+'.png')
        report['summary']['dimensions']=dict(Counter('x'.join(map(str,r['size'])) for r in report['records'] if 'size' in r))
        report['summary']['unique_rgb']=len({r['pixels_sha256'] for r in report['records'] if 'pixels_sha256' in r})
        (args.output/'inventory.json').write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps(report['summary'], indent=2))
    if report['summary']['missing']:
        raise SystemExit('Missing decoded sources; inventory is incomplete.')


if __name__ == '__main__':
    main()
