#!/usr/bin/env python3
"""Build a PE2BG1 atlas from an exact native RGB555 capture and registered 4x art.

Art is never re-framed. Optional explicit canvas fitting handles size-only
normalization; native references remain authoritative.
--test-pattern is a synthetic renderer fixture, not distributable room artwork.
Outputs can contain game data and must stay in an ignored build directory.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct

import numpy as np
from PIL import Image


def identity(data):
    value=14695981039346656037
    for byte in data:value=((value^byte)*1099511628211)&((1<<64)-1)
    return value


def native_image(data):
    if len(data)!=320*240*2:raise ValueError('Native capture must contain exactly 320x240 RGB555 words')
    words=np.frombuffer(data,dtype='<u2').reshape(240,320)
    return np.stack([((words>>shift)&31)*255//31 for shift in [0,5,10]],axis=-1).astype(np.uint8)


def prepare_canvas(art,left,right,fit=False):
    if left < -96 or left>0 or right<320 or right>416 or left%16 or right%16:
        raise ValueError('Bounds must be 16-pixel aligned within -96..0 and 320..416')
    expected=((right-left)*4,960)
    if art.convert('RGBA').getchannel('A').getextrema()!=(255,255):
        raise ValueError('Base artwork must be opaque across its entire claimed span')
    if art.size!=expected:
        if not fit:raise ValueError(f'Artwork must be exactly {expected[0]}x960, got {art.size}')
        # Only tolerate integer-size aspect rounding, never fit a different crop.
        if abs(art.width*expected[1]-art.height*expected[0])>max(*art.size,*expected):
            raise ValueError('Canvas fit cannot change the artwork aspect ratio')
        art=art.resize(expected,Image.Resampling.LANCZOS)
    return art


def build(native,art,left,right,fit=False):
    art=prepare_canvas(art,left,right,fit)
    rgb=native_image(native)
    count=(right-left)//16*15
    rows=(count+15)//16
    atlas=Image.new('RGBA',(16*68,rows*136))
    art=art.convert('RGBA')
    if art.getchannel('A').getextrema()!=(255,255):raise ValueError('Base artwork must be opaque across its entire claimed span')
    for cell,(y,x) in enumerate((y,x) for y in range(0,240,16) for x in range(left,right,16)):
        material=art.crop(((x-left)*4,y*4,(x-left+16)*4,(y+16)*4))
        reference=Image.new('RGBA',(64,64))
        if 0<=x<320:
            reference=Image.fromarray(rgb[y:y+16,x:x+16]).convert('RGBA').resize((64,64),Image.Resampling.NEAREST)
        for plane,tile in enumerate([material,reference]):
            # Two-pixel edge-replicated gutters avoid filtering across cells.
            pixels=np.array(tile);pixels=np.pad(pixels,((2,2),(2,2),(0,0)),mode='edge')
            atlas.paste(Image.fromarray(pixels),(cell%16*68,cell//16*68+plane*rows*68))
    key=identity(native)
    metadata=struct.pack('<8sQIIiiIIII',b'PE2BG1\0\0',key,320,240,left,right,1,4,count,0)
    return key,metadata,atlas


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--native',type=Path,required=True)
    source=parser.add_mutually_exclusive_group(required=True)
    source.add_argument('--art',type=Path)
    source.add_argument('--test-pattern',action='store_true')
    parser.add_argument('--fit-canvas',action='store_true',help='Explicit size-only material normalization; preserve aspect and native references')
    parser.add_argument('--left',type=int,default=-64)
    parser.add_argument('--right',type=int,default=384)
    parser.add_argument('--output',type=Path,required=True)
    args=parser.parse_args()
    native=args.native.read_bytes()
    if args.test_pattern:
        art=Image.new('RGB',((args.right-args.left)*4,960))
        from PIL import ImageDraw
        draw=ImageDraw.Draw(art)
        for y in range(15):
            for x in range((args.right-args.left)//16):
                draw.rectangle((x*64,y*64,x*64+63,y*64+63),fill=((x*19)%224+16,(y*29)%224+16,144))
    else:art=Image.open(args.art)
    input_size=art.size
    key,metadata,atlas=build(native,art,args.left,args.right,args.fit_canvas)
    args.output.mkdir(parents=True,exist_ok=True)
    atlas.save(args.output/f'{key:016x}.png')
    (args.output/f'{key:016x}.pe2bg').write_bytes(metadata)
    provenance=dict(format='PE2BG1',key=f'{key:016x}',native_sha256=hashlib.sha256(native).hexdigest(),
        art_sha256=hashlib.sha256(args.art.read_bytes()).hexdigest() if args.art else None,
        left=args.left,right=args.right,scale=4,test_fixture=args.test_pattern,
        input_size=list(input_size),explicit_canvas_fit=args.fit_canvas,
        note='Material canvas fitting is opt-in and never changes framing; native coverage/reference pixels are retained. Registration and artistic review are separate gates.')
    (args.output/f'{key:016x}.json').write_text(json.dumps(provenance,indent=2)+'\n')
    print(f'{key:016x}: {atlas.size}, {args.left}..{args.right}')


if __name__=='__main__':main()
