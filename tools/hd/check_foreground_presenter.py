#!/usr/bin/env python3
"""Probe clipped foreground HD cells on a real hidden GPU, using synthetic VRAM."""
import argparse
import json
import os
from pathlib import Path
import subprocess

import numpy as np
from PIL import Image
from foreground import decode_sprite


def atlas(words,inset=False):
    height,width=words.shape;columns=(width+15)//16;count=columns*((height+15)//16)
    rows=(count+15)//16;output=Image.new('RGBA',(16*68,rows*136))
    rgb=np.stack([((words>>bit)&31)*255//31 for bit in [0,5,10]],axis=-1).astype(np.uint8)
    for cell in range(count):
        x,y=cell%columns*16,cell//columns*16
        if inset:x,y=min(x,width-16),min(y,height-16)
        source=np.zeros((16,16,4),np.uint8);crop=rgb[y:y+16,x:x+16]
        source[:crop.shape[0],:crop.shape[1],:3]=crop;source[:,:,3]=255
        reference=np.repeat(np.repeat(source,4,axis=0),4,axis=1)
        material=np.full((64,64,4),[192,64,128,255],np.uint8)
        for plane,tile in enumerate([material,reference]):
            output.paste(Image.fromarray(np.pad(tile,((2,2),(2,2),(0,0)),mode='edge')),
                         (cell%16*68,cell//16*68+plane*rows*68))
    return output


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--probe',type=Path,default=Path('build-port/foreground_presenter_probe'))
    parser.add_argument('--output',type=Path,default=Path('build-hd-study/foreground-presenter'))
    parser.add_argument('--backend',choices=['gpu','software'],default='gpu')
    parser.add_argument('--ot',action='store_true',help='Exercise registered live-OT substitution and packet restoration')
    args=parser.parse_args();root=args.output.resolve();root.mkdir(parents=True,exist_ok=True)
    (root/'report.json').unlink(missing_ok=True)
    vram=np.zeros((512,1024),np.uint16);vram[:240,:320]=0x1084
    vram[:240,:320:2]|=0x8000
    for y in range(256):
        indices=(np.arange(256)+y*3)%16
        vram[y,832:960]=indices[::2]|(indices[1::2]<<8)
    for i in range(256):vram[255,i]=(i&31)|(((i*3)&31)<<5)|(((i*7)&31)<<10)|(0x8000 if i%3==0 else 0)
    vram[255,0]=0;vram[255,1]=0x8000
    native=root/'synthetic-vram.bin';native.write_bytes(vram.astype('<u2').tobytes())
    env={k:v for k,v in os.environ.items() if not k.startswith('PE2_')}
    env.update(PSYZ_HEADLESS='gpu' if args.backend=='gpu' else '1',SDL_AUDIODRIVER='dummy')
    if args.ot:env['PE2_PROBE_OT']='1'
    results=[]
    # Raw/modulated, all blend modes, native fallback, two aspect modes,
    # source UV wrapping and partial right/bottom cells. A later green tile
    # checks depth order; an outside blue tile checks restored clip state.
    cases=[(8,23,flags,4,0,0,True,0) for flags in range(16)]
    cases += [(w,h,1,scale,wide,palette,available,0) for w,h,scale,wide,palette,available in [
        (24,56,4,0,0,True),(208,240,4,0,0,True),(8,23,4,1,0,True),
        (8,23,1,0,0,True),(8,23,4,0,1,True),(8,23,4,0,0,False)]]
    cases += [(8,23,3,4,0,0,True,mask) for mask in [1,2,3]]
    cases=[(*case,0) for case in cases]
    if args.ot:cases.append((8,23,1,4,0,0,True,0,1))
    cases=[(*case,0,0) for case in cases]
    if args.ot:cases += [(32,40,flags,4,wide,0,True,mask,0,1,1)
                        for flags,wide,mask in [(1,0,0),(1,1,0),(0,1,0),(1,1,1),(1,1,2),(1,1,3),(3,1,0)]]
    cases=[(*case,0,0) for case in cases]
    if args.ot:
        cases += [(8,23,flags,4,1,0,True,0,0,0,0,1,0) for flags in range(16)]
        cases += [(8,23,3,4,1,0,True,mask,0,0,0,1,0) for mask in [1,2,3]]
        cases += [(8,23,1,4,wide,0,True,0,0,0,1,1,0) for wide in [0,1]]
        cases += [(8,23,1,4,wide,0,True,0,0,0,0,1,1) for wide in [0,1]]
    for index,(width,height,flags,scale,wide,palette,available,mask,window,inset,feedback,aligned,no_staging) in enumerate(cases):
        source=dict(w=width,h=height,tpage=128|13,clut=255*64,u0=248,v0=248)
        words,_=decode_sprite(vram,source);image=root/f'{width}-{height}.png';atlas(words,inset).save(image)
        prefix=root/f'case-{index:02d}'
        command=[str(args.probe.resolve()),str(native),'123456789abcdef0',str(image) if available else 'none',
                 str(prefix),str(width),str(height),str(flags),str(scale),str(wide),str(palette)]
        current_env={**env,'PE2_PROBE_MASK':str(mask)}
        if window:current_env['PE2_PROBE_WINDOW']='1'
        if inset:current_env['PE2_PROBE_INSET']='1'
        if feedback:current_env['PE2_PROBE_FEEDBACK']='1'
        if aligned:current_env['PE2_PROBE_ALIGNED']='1'
        if no_staging:current_env['PE2_PROBE_NO_STAGING']='1'
        process=subprocess.run(command,env=current_env,capture_output=True,text=True,timeout=30)
        prefix.with_suffix('.log').write_text(process.stdout+process.stderr)
        assert process.returncode==0,(index,process.stdout,process.stderr[-1500:])
        original=np.array(Image.open(str(prefix)+'.original.ppm'))
        enhanced=np.array(Image.open(str(prefix)+'.hd.ppm'))
        changed=int(np.count_nonzero(original!=enhanced))
        if scale==1 or not available or palette or window or args.backend=='software' or (args.ot and wide and not inset and not aligned) or (inset and flags&2) or no_staging:assert changed==0,index
        elif mask!=3:assert changed>0,index
        green=lambda pixels:np.all(pixels==[0,255,0],axis=2)
        assert np.array_equal(green(original),green(enhanced)),('front primitive overwritten',index)
        if not wide and not palette and not window:
            potential=np.zeros((240,320),bool)
            # Source origin (153,109), current clip (150,100,80,100).
            w=min(width,230-153);h=min(height,200-109)
            start=152 if aligned else 153
            potential[109:109+h,start:start+w]=words[:h,:w]!=0
            sy,sx=original.shape[0]//240,original.shape[1]//320
            assert original.shape[:2]==(240*sy,320*sx)
            potential=np.repeat(np.repeat(potential,sy,axis=0),sx,axis=1)
            assert np.array_equal(original[~potential],enhanced[~potential]),('coverage leaked',index)
        results.append(dict(width=width,height=height,flags=flags,scale=scale,wide=wide,palette_changed=palette,
                            atlas_available=available,mask_mode=mask,texture_window=window,inset=inset,feedback=feedback,aligned=aligned,staging_allowed=not no_staging,native_differences=0,changed_channels=changed))
    (root/'report.json').write_text(json.dumps(dict(passed=True,backend=args.backend,ot_substitution=args.ot,cases=results,
        scope='Synthetic explicit-state foreground builder; not live room/OT integration.'),indent=2)+'\n')
    print(f'PASS: {len(results)} clipped foreground {args.backend} cases preserve all native VRAM')


if __name__=='__main__':main()
