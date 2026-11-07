#!/usr/bin/env python3
"""Read-only geometry diagnostics for an HD canvas and its native background.

Reports local gradient alignment in authored foreground rectangles (or the
whole view). Scores are review aids, never artwork or occlusion approval.
No artwork is modified; canvas fitting uses the same coordinates as the packer.
"""
import argparse
import hashlib
import json
from pathlib import Path
import cv2
import numpy as np
from PIL import Image
from pack import identity,native_image,prepare_canvas


def assess(native,art,sources=None,left=-64,right=384,radius=9):
    if not 1<=radius<=32:raise ValueError('Search radius must be in 1..32 native pixels')
    key=f'{identity(native):016x}';source=native_image(native);input_size=list(art.size)
    if sources is not None:
        if sources.get('format')!='pe2-foreground-source-audit-v1' or sources.get('capture',{}).get('key')!=key:
            raise ValueError('Foreground audit belongs to another native view')
        records=sources['sprites']
        if len(records)>512 or len({r['index'] for r in records})!=len(records):raise ValueError('Invalid source records')
    else:records=[dict(index=None,screen_rect=[radius+1,radius+1,320-2*(radius+1),240-2*(radius+1)])]
    canvas=prepare_canvas(art,left,right,True)
    candidate=cv2.resize(np.asarray(canvas.convert('RGB')),(right-left,240),interpolation=cv2.INTER_AREA)
    def gradient(image):
        grey=cv2.cvtColor(image,cv2.COLOR_RGB2GRAY).astype(np.float32)
        return cv2.magnitude(cv2.Sobel(grey,cv2.CV_32F,1,0,ksize=3),cv2.Sobel(grey,cv2.CV_32F,0,1,ksize=3))
    a,b=gradient(source),gradient(candidate);regions=[]
    for record in records:
        rect=record['screen_rect']
        if len(rect)!=4 or any(type(v) is not int for v in rect) or rect[2]<1 or rect[3]<1:
            raise ValueError('Invalid foreground screen rectangle')
        x,y,w,h=rect
        # Keep the visible authored region, including near native side edges.
        # Generated side artwork supplies search samples beyond the 320px view.
        # Exclude only the source Sobel's artificial one-pixel reflected border.
        x0,y0=max(x-4,1),max(y-4,1);x1,y1=min(x+w+4,319),min(y+h+4,239)
        row=dict(source=record['index'],screen_rect=rect,informative=False)
        regions.append(row)
        if x0>=x1 or y0>=y1:row['reason']='outside searchable view';continue
        template=a[y0:y1,x0:x1]
        if float(template.std())<1e-6:row['reason']='no source gradient variation';continue
        dx0,dx1=max(-radius,left-x0),min(radius,right-x1)
        dy0,dy1=max(-radius,-y0),min(radius,240-y1)
        scores=[]
        for dy in range(dy0,dy1+1):
            for dx in range(dx0,dx1+1):
                score=float(cv2.matchTemplate(b[y0+dy:y1+dy,x0+dx-left:x1+dx-left],template,cv2.TM_CCOEFF_NORMED)[0,0])
                scores.append((score,dx,dy))
        # Prefer the smaller displacement only for exactly tied correlations;
        # expose ambiguous peaks rather than treating that preference as proof.
        ranked=sorted(scores,key=lambda v:(v[0],-abs(v[1])-abs(v[2])),reverse=True)
        best=ranked[0];gap=best[0]-ranked[1][0]
        row.update(informative=True,template_rect=[x0,y0,x1,y1],search_bounds=[dx0,dy0,dx1,dy1],
            search_truncated=[dx0,dy0,dx1,dy1]!=[-radius,-radius,radius,radius],best_shift_native_px=list(best[1:]),best_gradient_correlation=best[0],
            zero_shift_correlation=next(v[0] for v in scores if v[1:]==(0,0)),score_gap=gap,
            ambiguous=gap<0.01,on_search_boundary=abs(best[1])==radius or abs(best[2])==radius)
    return dict(format='pe2-art-registration-diagnostic-v1',key=key,input_size=input_size,canonical_size=list(canvas.size),
        left=left,right=right,radius=radius,regions=regions,approved=False,
        scope='Local downsampled gradient alignment only. Ambiguous/flat/clipped regions cannot prove alignment; no exact subpixel contour, artistic, actor-matte or occlusion approval.')


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    for name in ['native','art','output']:parser.add_argument('--'+name,type=Path,required=True)
    parser.add_argument('--sources',type=Path,help='Directory containing the foreground source audit report.json')
    parser.add_argument('--left',type=int,default=-64);parser.add_argument('--right',type=int,default=384)
    parser.add_argument('--radius',type=int,default=9)
    args=parser.parse_args();native=args.native.read_bytes()
    source_path=args.sources/'report.json' if args.sources else None
    sources=json.loads(source_path.read_text()) if source_path else None
    with Image.open(args.art) as art:report=assess(native,art,sources,args.left,args.right,args.radius)
    report.update(native_sha256=hashlib.sha256(native).hexdigest(),art_sha256=hashlib.sha256(args.art.read_bytes()).hexdigest(),
        sources_sha256=hashlib.sha256(source_path.read_bytes()).hexdigest() if source_path else None)
    args.output.parent.mkdir(parents=True,exist_ok=True);args.output.write_text(json.dumps(report,indent=2)+'\n')
    print(f'{report["key"]}: {len(report["regions"])} diagnostic regions; inspect {args.output}; no approval implied')


if __name__=='__main__':main()
