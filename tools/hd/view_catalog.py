#!/usr/bin/env python3
"""Join logical room/view tables with exact native background identities.

This is a source-table survey, not runtime coverage. Unresolved and absent
backgrounds are explicit; they must not silently become passing runtime tests.
"""
import argparse
from collections import Counter,defaultdict
import json
from pathlib import Path
from inventory import SPECIAL


def catalog(scenes,native):
    by_file=defaultdict(list)
    for record in native['records']:
        stage=int(record['stage'].removeprefix('stage'))
        by_file[stage,record['folder'],record['mapped_view_file']].append(record)
    records=[]
    diagnostics=[]
    empty_rooms=[]
    for scene in scenes:
        diagnostics.extend(dict(room=scene['room'],**entry) for entry in scene.get('unresolved',[]) if entry['block'] in ['views','sprites'])
        if not any(group['views'] for group in scene['views']):empty_rooms.append(scene['room'])
        warps=scene['warps'].get('entries',[])
        default=scene['placements'].get('defaultVariant')
        variant=default if isinstance(default,int) and 1<=default<=255 else 1
        for group in scene['views']:
            for view in group['views']:
                candidates=by_file.get((scene['stage'],scene['room'],view['file']),[])
                keys=sorted({v['key'] for v in candidates if 'key' in v})
                reasons=[]
                if not view['withinViewCount']:reasons.append('outside declared logical view count')
                if not view['fileExists']:reasons.append('no view file')
                if not view['camera']:reasons.append('no camera')
                if not keys:reasons.append('no native background')
                if len(keys)>1:reasons.append('multiple native backgrounds')
                if group.get('mapWriters'):reasons.append('view map modified by room code')
                matching=[w for w in warps if w['initialView']==view['view']]
                options=matching or warps
                warp=options[0]['slot'] if options else None
                if warp is None:reasons.append('no authored arrival warp')
                row=dict(room=scene['room'],stage=scene['stage'],area=scene['area'],room_state=group['roomIndex'],
                         view=view['view'],mapped_file=view['file'],keys=keys,variant=variant,warp=warp,
                         warp_matches_view=bool(matching),runtime_verified=False,review=reasons,
                         special_renderers=sorted({r['review'] for r in candidates if r['review']!='unverified static candidate'} |
                                                  ({SPECIAL[scene['room']]} if scene['room'] in SPECIAL else set())),
                         eligible_for_start_test=not reasons)
                row['location']=[row[k] for k in ['stage','area','view','room_state','warp','variant']]
                records.append(row)
    return dict(format='pe2-logical-background-catalog-v1',note='Offline source-table mapping only. Runtime observation must confirm every tested target.',
                summary=dict(rooms=len(scenes),logical_views=len(records),start_test_candidates=sum(r['eligible_for_start_test'] for r in records),
                             with_background=sum(bool(r['keys']) for r in records),rooms_without_view_rows=empty_rooms,unresolved_diagnostics=len(diagnostics),reasons=dict(Counter(reason for r in records for reason in r['review']))),source_diagnostics=diagnostics,records=records)


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--scenes',type=Path,default=Path('build-hd-study/scenes'))
    parser.add_argument('--native',type=Path,default=Path('build-hd-study/native-catalog/index.json'))
    parser.add_argument('--output',type=Path,default=Path('build-hd-study/view-catalog.json'))
    args=parser.parse_args()
    source_report=json.loads((args.scenes/'_report.json').read_text())
    if source_report['errors']:raise SystemExit('Room scene export has errors; do not claim a complete view catalog')
    scenes=[json.loads(p.read_text()) for p in sorted(args.scenes.glob('*.json')) if not p.name.startswith('_')]
    native=json.loads(args.native.read_text())
    if native['errors']:raise SystemExit('Native decoding has errors')
    report=catalog(scenes,native)
    args.output.parent.mkdir(parents=True,exist_ok=True);args.output.write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps(report['summary'],indent=2))


if __name__=='__main__':main()
