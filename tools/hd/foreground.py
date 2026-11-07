#!/usr/bin/env python3
"""Export authored view-sprite coverage from a verified local VRAM capture.

These are potential occluders, not a reconstruction of live OT visibility.
All output contains disc-derived pixels and must stay local/ignored.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re
import zlib

import numpy as np
from PIL import Image


def decode_sprite(vram,source):
    """Resolve PS1 texture-page/CLUT addressing, retaining zero and STP words."""
    if vram.shape!=(512,1024):raise ValueError('Expected full native VRAM')
    width,height=source['w'],source['h']
    if not (0<=width<=1024 and 0<=height<=1024):raise ValueError('Invalid sprite dimensions')
    page=source['tpage'];mode=(page>>7)&3
    if mode==3:raise ValueError('Reserved texture depth')
    u=(source['u0']+np.arange(width))&255
    v=(source['v0']+np.arange(height))&255
    shift=[2,1,0][mode]
    x=(page&15)*64+(u>>shift);y=((page>>4)&1)*256+v
    if len(x) and x.max()>=1024:raise ValueError('Texture rectangle exceeds VRAM')
    packed=vram[y[:,None],x[None,:]]
    if mode<2:
        bits=4 if mode==0 else 8
        index=(packed>>((u&((1<<shift)-1))*bits)[None,:])&((1<<bits)-1)
        cx=(source['clut']&63)*16;cy=source['clut']>>6
        if cy>=512 or (index.size and cx+int(index.max())>=1024):raise ValueError('CLUT exceeds VRAM')
        words=vram[cy,cx+index]
    else:words=packed
    rgb=np.stack([((words>>bit)&31)*255//31 for bit in [0,5,10]],axis=-1).astype(np.uint8)
    rgba=np.concatenate([rgb,((words!=0)*255).astype(np.uint8)[...,None]],axis=-1)
    return words,rgba


def layers(view,fields,vram):
    if view['sourceCount']!=len(view['rows']):raise ValueError('Incomplete source table')
    coverage=np.zeros((240,320),np.uint8)
    result=[]
    for index,row in enumerate(view['rows']):
        if len(row)!=len(fields):raise ValueError('Incomplete source row')
        source=dict(zip(fields,row));words,rgba=decode_sprite(vram,source)
        batches=[dict(index=i,**batch) for i,batch in enumerate(view['batchList'])
                 if batch['firstSprite']<=index<batch['firstSprite']+batch['spriteCount']]
        x,y=source['x0']+160,source['y0']+120
        left,top,right,bottom=max(x,0),max(y,0),min(x+source['w'],320),min(y+source['h'],240)
        if batches and left<right and top<bottom:
            mask=rgba[top-y:bottom-y,left-x:right-x,3]
            coverage[top:bottom,left:right]=np.maximum(coverage[top:bottom,left:right],mask)
        record=dict(index=index,source=source,batches=batches,screen_rect=[x,y,source['w'],source['h']],
                    covered_texels=int(np.count_nonzero(words)),stp_texels=int(np.count_nonzero(words&0x8000)),
                    semitransparent_texels=int(np.count_nonzero((words!=0)&((words&0x8000)!=0))) if source['codeFlags']&2 else 0,
                    native_sha256=hashlib.sha256(words.astype('<u2').tobytes()).hexdigest())
        result.append((record,rgba,words))
    return result,coverage


def select_view(scene,catalog,capture):
    if capture.get('format')!='pe2-static-view-survey-v2' or capture.get('matched_frames',0)<30:
        raise ValueError('A settled current-format capture is required')
    matches=[r for r in catalog['records'] if r['location']==capture['location'] and r['room']==scene['room']]
    if len(matches)!=1 or matches[0]['keys']!=[capture['key']]:raise ValueError('Capture/catalog identity mismatch')
    for entry in scene.get('unresolved',[]):
        if entry['block']!='sprites':continue
        scoped=re.fullmatch(re.escape(scene['sprites'].get('table',''))+r'\[(\d+)\]',entry.get('what',''))
        if scoped and int(scoped[1])!=matches[0]['mapped_file']-1:continue
        raise ValueError('Source sprite table is unresolved')
    views=[v for v in scene['sprites']['views'] if v['file']==matches[0]['mapped_file']]
    if len(views)!=1:raise ValueError('Mapped sprite view is unresolved')
    return views[0]


def read_vram(directory):
    raw=directory/'vram.bin'
    data=raw.read_bytes() if raw.is_file() else zlib.decompress((directory/'vram.bin.z').read_bytes())
    if len(data)!=1024*512*2:raise ValueError('Incomplete VRAM capture')
    return data


def audit_survey(survey_path,scenes_path,catalog):
    survey=json.loads(survey_path.read_text())
    if survey.get('format')!='pe2-static-view-parity-survey-v1' or not survey.get('selected_complete'):
        raise ValueError('A completed runtime survey is required')
    scenes={p.stem:json.loads(p.read_text()) for p in scenes_path.glob('*.json') if not p.name.startswith('_')}
    results=[];errors=[]
    for case in survey['cases']:
        try:
            if not case['parity_verified']:raise ValueError('Unverified survey input')
            scene=scenes[case['room']]
            directory=survey_path.parent/('-'.join(map(str,case['location'])))/'0'
            capture=json.loads((directory/'report.json').read_text())
            if capture!=case['runs'][0]['report'] or capture['location']!=case['location'] or capture['key']!=case['key']:
                raise ValueError('Capture metadata changed since the runtime survey')
            view=select_view(scene,catalog,capture)
            data=read_vram(directory)
            if hashlib.sha256(data).hexdigest()!=case['runs'][0]['native_sha256']:
                raise ValueError('VRAM changed since the runtime survey')
            sprites,mask=layers(view,scene['sprites']['fields'],np.frombuffer(data,dtype='<u2').reshape(512,1024))
            results.append(dict(location=case['location'],room=case['room'],key=case['key'],sources=len(sprites),
                                potential_pixels=int(np.count_nonzero(mask))))
        except Exception as error:errors.append(dict(location=case['location'],room=case['room'],error=str(error)))
    return dict(format='pe2-foreground-source-survey-v1',
                scope='Authored sources sampled from passing static-view VRAM captures; not live visibility or HD masks.',
                decoded=len(results),unverified=len(errors),cases=results,errors=errors,runtime_visibility_verified=False,
                source_survey_sha256=hashlib.sha256(survey_path.read_bytes()).hexdigest())


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    mode=parser.add_mutually_exclusive_group(required=True)
    mode.add_argument('--scene',type=Path)
    mode.add_argument('--survey',type=Path,help='Audit all passing runtime survey captures; metadata output only')
    parser.add_argument('--scenes',type=Path,default=Path('build-hd-study/scenes'))
    parser.add_argument('--catalog',type=Path,default=Path('build-hd-study/view-catalog.json'))
    parser.add_argument('--capture',type=Path)
    parser.add_argument('--output',type=Path,required=True)
    args=parser.parse_args()
    if args.scene and not args.capture:parser.error('--scene requires --capture')
    args.output.mkdir(parents=True,exist_ok=True);(args.output/'report.json').unlink(missing_ok=True)
    catalog=json.loads(args.catalog.read_text())
    if args.survey:
        report=audit_survey(args.survey,args.scenes,catalog)
        (args.output/'report.json').write_text(json.dumps(report,indent=2)+'\n')
        print(f"{report['decoded']} source decodes; {report['unverified']} unverified")
        if report['unverified']:raise SystemExit(1)
        return
    scene=json.loads(args.scene.read_text())
    capture=json.loads((args.capture/'report.json').read_text())
    view=select_view(scene,catalog,capture)
    data=read_vram(args.capture)
    sprites,coverage=layers(view,scene['sprites']['fields'],np.frombuffer(data,dtype='<u2').reshape(512,1024))
    args.output.mkdir(parents=True,exist_ok=True)
    records=[]
    for record,rgba,words in sprites:
        name=f"sprite-{record['index']:04d}"
        if rgba.size:Image.fromarray(rgba).save(args.output/(name+'.png'))
        (args.output/(name+'.rgb555')).write_bytes(words.astype('<u2').tobytes())
        records.append(record)
    Image.fromarray(coverage).save(args.output/'potential-coverage.png')
    report=dict(format='pe2-foreground-source-audit-v1',room=scene['room'],capture=capture,mapped_file=view['file'],
                vram_sha256=hashlib.sha256(data).hexdigest(),sprites=records,
                covered_screen_pixels=int(np.count_nonzero(coverage)),draw_areas=view['drawAreaList'],
                runtime_visibility_verified=False,hd_foreground_implemented=False,
                limits=['Potential authored sources, including hidden/skipped batches; not live OT visibility.',
                        'Texture window, live packet changes, draw-area ordering and model depth are not captured.',
                        'No inferred HD alpha, feathering, extra geometry or sprite resampling.'])
    (args.output/'report.json').write_text(json.dumps(report,indent=2)+'\n')
    print(f"{len(records)} authored sprite sources; {report['covered_screen_pixels']} potential covered screen pixels")


if __name__=='__main__':main()
