#!/usr/bin/env python3
"""Source-guided candidate normalization for fixed-camera HD backgrounds.

Keeps original high-contrast geometry/colour marks and low-frequency lighting;
uses generated microtexture in surface interiors and generated side artwork.
This audit does not approve artistic quality, occluders or runtime correctness.
"""
import argparse
import hashlib
import json
from pathlib import Path

import cv2
import numpy as np
from PIL import Image
from pack import identity,native_image


def normalize(native,generated,left=-64,right=384,fit=False):
    size=((right-left)*4,960)
    if left>0 or right<320 or left%16 or right%16:raise ValueError('Invalid canvas bounds')
    if generated.size!=size:
        if not fit:raise ValueError(f'Expected {size}, got {generated.size}; fitting must be explicit')
        generated=generated.resize(size,Image.Resampling.LANCZOS)
    generated=generated.convert('RGBA')
    if generated.getchannel('A').getextrema()!=(255,255):raise ValueError('Generated base canvas must be opaque')
    source=native_image(native)
    base=np.array(Image.fromarray(source).resize((1280,960),Image.Resampling.LANCZOS)).astype(np.float32)
    material=np.array(generated)[:,:,:3].astype(np.float32)
    start=-left*4;end=start+1280
    candidate=material[:,start:end]
    # Microtexture only. Original large-scale structure/lighting is never replaced.
    residual=candidate-cv2.GaussianBlur(candidate,(0,0),1.2)
    residual=np.clip(residual,-16,16)
    grey=cv2.cvtColor(source,cv2.COLOR_RGB2GRAY)
    edges=cv2.Canny(cv2.GaussianBlur(grey,(0,0),1.1),20,45)
    hsv=cv2.cvtColor(source,cv2.COLOR_RGB2HSV)
    marks=(((hsv[:,:,0]<8)|(hsv[:,:,0]>172)|((hsv[:,:,0]>=15)&(hsv[:,:,0]<=42))) &
           (hsv[:,:,1]>90)&(hsv[:,:,2]>30))
    protected=cv2.dilate(((edges!=0)|marks).astype(np.uint8),np.ones((3,3),np.uint8))
    protected=np.repeat(np.repeat(protected,4,axis=0),4,axis=1).astype(bool)
    protected[:,:8]=True;protected[:,-8:]=True;protected[:8]=True;protected[-8:]=True
    distance=cv2.distanceTransform((~protected).astype(np.uint8),cv2.DIST_L2,3)
    weight=np.minimum(distance/6,1)
    centre=np.clip(np.rint(base+residual*weight[:,:,None]),0,255).astype(np.uint8)
    output=np.clip(np.rint(material),0,255).astype(np.uint8)
    output[:,start:end]=centre
    # Match the boundary colours, fading correction outwards into generated sides.
    if start:
        delta=cv2.GaussianBlur((base[:,0]-material[:,start])[:,None,:],(1,0),sigmaX=0.1,sigmaY=24)[:,0,:]
        for x in range(start):
            t=(x+1)/start
            output[:,x]=np.clip(np.rint(material[:,x]+delta*t*t),0,255).astype(np.uint8)
        output[:,start-1]=centre[:,0]
    if end<output.shape[1]:
        delta=cv2.GaussianBlur((base[:,-1]-material[:,end-1])[:,None,:],(1,0),sigmaX=0.1,sigmaY=24)[:,0,:]
        for x in range(end,output.shape[1]):
            t=(output.shape[1]-x)/(output.shape[1]-end)
            output[:,x]=np.clip(np.rint(material[:,x]+delta*t*t),0,255).astype(np.uint8)
        output[:,end]=centre[:,-1]
    baseline=base.astype(np.uint8)
    mismatches=int(np.count_nonzero(centre[protected]!=baseline[protected]))
    assert mismatches==0
    report=dict(key=f'{identity(native):016x}',size=list(size),left=left,right=right,
        protected_pixels=int(protected.sum()),centre_pixels=1280*960,protected_channel_mismatches=mismatches,
        enhanced_pixels=int(np.count_nonzero(np.any(centre!=baseline,axis=2))),
        centre_max_channel_delta=int(np.max(np.abs(centre.astype(int)-baseline.astype(int)))),
        status='source-geometry candidate; artistic/semantic, foreground and runtime review still required')
    return Image.fromarray(output),report


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--native',type=Path,required=True)
    parser.add_argument('--generated',type=Path,required=True)
    parser.add_argument('--output',type=Path,required=True)
    parser.add_argument('--left',type=int,default=-64)
    parser.add_argument('--right',type=int,default=384)
    parser.add_argument('--fit-canvas',action='store_true')
    args=parser.parse_args()
    source=args.native.read_bytes()
    with Image.open(args.generated) as generated:
        original_size=generated.size
        result,report=normalize(source,generated,args.left,args.right,args.fit_canvas)
    args.output.parent.mkdir(parents=True,exist_ok=True);result.save(args.output)
    report.update(native_sha256=hashlib.sha256(source).hexdigest(),generated_sha256=hashlib.sha256(args.generated.read_bytes()).hexdigest(),
                  input_size=list(original_size),explicit_canvas_fit=args.fit_canvas,output_sha256=hashlib.sha256(args.output.read_bytes()).hexdigest())
    args.output.with_suffix('.audit.json').write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps(report,indent=2))


if __name__=='__main__':main()
