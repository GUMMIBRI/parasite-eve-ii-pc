#!/usr/bin/env python3
"""Build a local foreground candidate atlas from audited sources and registered art.

The RGB material follows the artwork; original native texels retain coverage,
STP and palette fallback. This creates no artistic/occlusion approval.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import numpy as np
from PIL import Image
from pack import identity


def build(report,source_root,art=None,left=-64,materials=None):
    if report.get('format')!='pe2-foreground-source-audit-v1':raise ValueError('Expected a foreground source audit')
    if (art is None)==(materials is None):raise ValueError('Choose registered artwork or individual source materials')
    if art is not None:
        if art.height!=960 or art.width%64 or left%16 or not -96<=left<=0 or not 320<=left+art.width//4<=416:
            raise ValueError('Expected registered 4x artwork with complete aligned native bounds')
        if art.convert('RGBA').getchannel('A').getextrema()!=(255,255):raise ValueError('Artwork must be opaque')
    sources=report['sprites']
    if not sources or len(sources)>512:raise ValueError('Expected 1..512 source records')
    count=sum(((r['source']['w']+15)//16)*((r['source']['h']+15)//16) for r in sources)
    if not 1<=count<=960:raise ValueError('Foreground atlas exceeds the bounded per-view budget')
    rows=(count+15)//16;atlas=Image.new('RGBA',(1088,rows*136));entries=[];cell=0
    previous=-1
    for record in sources:
        index=record['index'];s=record['source'];w,h=s['w'],s['h']
        if not previous<index<=4095 or not 1<=w<=320 or not 1<=h<=240:raise ValueError('Invalid source identity/extent')
        previous=index
        raw=(source_root/f'sprite-{index:04d}.rgb555').read_bytes()
        if len(raw)!=w*h*2 or hashlib.sha256(raw).hexdigest()!=record['native_sha256']:raise ValueError('Native source changed since audit')
        words=np.frombuffer(raw,dtype='<u2').reshape(h,w)
        rgb=np.stack([((words>>b)&31)*255//31 for b in [0,5,10]],axis=-1).astype(np.uint8)
        if materials is not None:
            with Image.open(materials/f'sprite-{index:04d}.png') as image:
                if image.size!=(w*4,h*4):raise ValueError('Individual material must be exactly 4x its native source')
                rgba=np.array(image.convert('RGBA'))
                covered=np.repeat(np.repeat(words!=0,4,axis=0),4,axis=1)
                if np.any(rgba[:,:,3][covered]!=255):raise ValueError('Material cannot remove native-covered foreground pixels')
                material=image.convert('RGB')
        else:
            material=art.convert('RGB').crop(((s['x0']+160-left)*4,(s['y0']+120)*4,
                                           (s['x0']+160-left+w)*4,(s['y0']+120+h)*4))
        inset=w>=16 and h>=16 and not s.get('codeFlags',0)&2
        entries.append(struct.pack('<IHHHHBBH',index|(4096 if inset else 0),s['tpage']&511,s['clut'],w,h,s['u0'],s['v0'],cell))
        for y in range(0,h,16):
            for x in range(0,w,16):
                sx,sy=(min(x,w-16),min(y,h-16)) if inset else (x,y)
                reference=np.zeros((16,16,4),np.uint8);crop=rgb[sy:sy+16,sx:sx+16]
                reference[:crop.shape[0],:crop.shape[1],:3]=crop;reference[:,:,3]=255
                ref=Image.fromarray(reference).resize((64,64),Image.Resampling.NEAREST)
                tile=material.crop((sx*4,sy*4,(sx+16)*4,(sy+16)*4)).convert('RGBA');tile.putalpha(255)
                for plane,image in enumerate([tile,ref]):
                    atlas.paste(Image.fromarray(np.pad(np.array(image),((2,2),(2,2),(0,0)),mode='edge')),
                                (cell%16*68,cell//16*68+plane*rows*68))
                cell+=1
    background=int(report['capture']['key'],16)
    key=identity(b'PE2FG2'+atlas.tobytes())
    if not key or key==background:raise ValueError('Atlas identity collision')
    location=report['capture']['location'][:4]
    header=struct.pack('<8sQQ6I',b'PE2FG2\0\0',background,key,*location,len(sources),count)
    return key,header+b''.join(entries),atlas


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--sources',type=Path,required=True,help='Foreground export directory with report.json')
    material=parser.add_mutually_exclusive_group(required=True)
    material.add_argument('--art',type=Path,help='Registered base canvas; candidate crops, not blend approval')
    material.add_argument('--materials',type=Path,help='Individual 4x sprite-NNNN.png material directory')
    parser.add_argument('--left',type=int,default=-64)
    parser.add_argument('--output',type=Path,required=True,help='Existing/local background pack directory')
    args=parser.parse_args();report=json.loads((args.sources/'report.json').read_text())
    if args.art:
        with Image.open(args.art) as art:key,metadata,atlas=build(report,args.sources,art,args.left)
    else:key,metadata,atlas=build(report,args.sources,materials=args.materials)
    args.output.mkdir(parents=True,exist_ok=True)
    context='-'.join(map(str,report['capture']['location'][:4]));base=report['capture']['key']
    name=f'{base}-{context}'
    atlas.save(args.output/f'{key:016x}.fg.png');(args.output/(name+'.pe2fg')).write_bytes(metadata)
    provenance=dict(format='PE2FG2',background_key=base,atlas_key=f'{key:016x}',context=context,
                    source_audit_sha256=hashlib.sha256((args.sources/'report.json').read_bytes()).hexdigest(),
                    art_sha256=hashlib.sha256(args.art.read_bytes()).hexdigest() if args.art else None,
                    individual_materials={f'sprite-{r["index"]:04d}.png':hashlib.sha256((args.materials/f'sprite-{r["index"]:04d}.png').read_bytes()).hexdigest() for r in report['sprites']} if args.materials else None,
                    left=args.left if args.art else None,candidate_only=True,
                    note='Individual 4x RGB materials or candidate base crops; blending/occlusion, moving layers and artistic consistency require runtime review.')
    (args.output/(name+'.foreground.json')).write_text(json.dumps(provenance,indent=2)+'\n')
    print(f'{name}: {len(report["sprites"])} sources, atlas {key:016x} {atlas.size}')


if __name__=='__main__':main()
