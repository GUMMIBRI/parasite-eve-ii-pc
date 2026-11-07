#!/usr/bin/env python3
"""Version and install local HD pack folders. No download or artistic approval.

Payloads include native reference planes: keep owner-disc packs private.
Select the printed installed version directory in the game's Background pack UI.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re
import shutil
import tempfile
import struct
from PIL import Image

MANIFEST='pe2-pack.json'
TOKEN=re.compile(r'[a-zA-Z0-9][a-zA-Z0-9._-]{0,63}\Z')
PAYLOAD=re.compile(r'(?:[0-9a-f]{16}\.(?:png|pe2bg)|[0-9a-f]{16}\.fg\.png|[0-9a-f]{16}(?:-[0-9]+){4}\.pe2fg)\Z')


def digest(path):
    result=hashlib.sha256()
    with path.open('rb') as source:
        for chunk in iter(lambda:source.read(1024*1024),b''):result.update(chunk)
    return result.hexdigest()


def read_manifest(root):
    path=root/MANIFEST
    if path.is_symlink():raise ValueError('Manifest must not be a symlink')
    data=json.loads(path.read_text())
    if data.get('format')!='pe2-local-pack-v1':raise ValueError('Unknown manifest format')
    if any(not isinstance(data.get(k),str) or not TOKEN.fullmatch(data[k]) for k in ['id','version']):
        raise ValueError('Invalid pack identity or version')
    files=data.get('files')
    if not isinstance(files,dict) or not files or len(files)>20000:raise ValueError('Invalid file inventory')
    if any(PAYLOAD.fullmatch(file.name) and file.name not in files for file in root.iterdir()):
        raise ValueError('Unlisted renderer payload in pack folder')
    for name,entry in files.items():
        if not PAYLOAD.fullmatch(name):raise ValueError('Invalid payload filename')
        if not isinstance(entry,dict) or type(entry.get('size')) is not int or not 0<entry['size']<=128*1024*1024:
            raise ValueError('Invalid payload size')
        if not isinstance(entry.get('sha256'),str) or not re.fullmatch('[0-9a-f]{64}',entry['sha256']):
            raise ValueError('Invalid payload hash')
        file=root/name
        if file.is_symlink() or not file.is_file() or file.stat().st_size!=entry['size'] or digest(file)!=entry['sha256']:
            raise ValueError('Missing or changed payload: '+name)
    backgrounds=[name for name in files if name.endswith('.pe2bg')]
    if not backgrounds:raise ValueError('Pack has no backgrounds')
    for name in backgrounds:
        atlas=name[:-6]+'.png'
        if atlas not in files:raise ValueError('Missing background atlas')
        raw=(root/name).read_bytes()
        if len(raw)!=48:raise ValueError('Invalid background header')
        magic,key,w,h,left,right,flags,scale,cells,reserved=struct.unpack('<8sQIIiiIIII',raw)
        if (magic!=b'PE2BG1\0\0' or key!=int(name[:16],16) or not key or (w,h)!=(320,240)
            or not -96<=left<=0 or not 320<=right<=416 or left%16 or right%16
            or (flags,scale,reserved)!=(1,4,0) or cells!=(right-left)//16*15):
            raise ValueError('Invalid background metadata')
        with Image.open(root/atlas) as image:
            if image.format!='PNG' or image.size!=(1088,((cells+15)//16)*136):raise ValueError('Invalid background atlas')
            image.verify()
    for name in files:
        if name.endswith('.pe2fg'):
            raw=(root/name).read_bytes()
            if len(raw)<48 or raw[:8] not in [b'PE2FG1\0\0',b'PE2FG2\0\0']:raise ValueError('Invalid foreground header')
            magic,background,atlas_key,stage,area,view,room,count,cells=struct.unpack('<8sQQ6I',raw[:48])
            context=[int(v) for v in name[:-6].split('-')[1:]]
            if (not background or background!=int(name[:16],16) or not atlas_key or atlas_key==background
                or context!=[stage,area,view,room] or not 1<=stage<=5 or not 1<=area<=255
                or not 1<=view<=50 or not 1<=room<=255 or not 1<=count<=512 or not 1<=cells<=960
                or len(raw)!=48+count*16 or f'{background:016x}.pe2bg' not in files):
                raise ValueError('Invalid foreground identity, context or extent')
            next_cell=0;previous=-1
            for offset in range(48,len(raw),16):
                source,tpage,clut,w,h,u,v,first=struct.unpack('<IHHHHBBH',raw[offset:offset+16])
                inset=bool(source&4096) if magic==b'PE2FG2\0\0' else False
                if magic==b'PE2FG2\0\0':source&=~4096
                if (not previous<source<=4095 or tpage>511 or (tpage>>7)&3==3 or clut>32767
                    or not 1<=w<=320 or not 1<=h<=240 or (inset and (w<16 or h<16)) or first!=next_cell):
                    raise ValueError('Invalid foreground source record')
                previous=source;next_cell+=((w+15)//16)*((h+15)//16)
            if next_cell!=cells:raise ValueError('Invalid foreground cell count')
            atlas=f'{atlas_key:016x}.fg.png'
            if atlas not in files:raise ValueError('Missing foreground atlas')
            with Image.open(root/atlas) as image:
                if image.format!='PNG' or image.size!=(1088,((cells+15)//16)*136):raise ValueError('Invalid foreground atlas')
                image.verify()
    return data


def create(root,pack_id,version):
    if not TOKEN.fullmatch(pack_id) or not TOKEN.fullmatch(version):raise ValueError('Invalid identity or version')
    if (root/MANIFEST).exists() or (root/MANIFEST).is_symlink():raise ValueError('Manifest already exists; create a new version folder')
    files={}
    for path in sorted(root.iterdir()):
        if PAYLOAD.fullmatch(path.name):
            if path.is_symlink() or not path.is_file():raise ValueError('Payload must be a regular file')
            files[path.name]=dict(size=path.stat().st_size,sha256=digest(path))
    data=dict(format='pe2-local-pack-v1',id=pack_id,version=version,files=files,
              scope='Local owner-disc pack integrity only; no artwork approval or distribution permission.')
    path=root/MANIFEST;created=False
    try:
        with path.open('x') as output:
            created=True
            output.write(json.dumps(data,indent=2)+'\n')
        read_manifest(root)
    except Exception:
        if created:path.unlink(missing_ok=True)
        raise
    return data


def install(source,destination):
    data=read_manifest(source)
    destination.mkdir(parents=True,exist_ok=True)
    target=destination/(data['id']+'--'+data['version'])
    if target.exists() or target.is_symlink():raise ValueError('Version already installed; existing versions are immutable')
    with tempfile.TemporaryDirectory(prefix='.pe2-install-',dir=destination) as temporary:
        staged=Path(temporary)/'payload';staged.mkdir()
        for name in [MANIFEST,*data['files']]:shutil.copyfile(source/name,staged/name)
        copied=read_manifest(staged)
        if copied!=data:raise ValueError('Manifest changed during installation')
        # Recheck immediately before publishing. Failed copies never become versions.
        if target.exists() or target.is_symlink():raise ValueError('Version already installed')
        staged.rename(target)
    return target


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    commands=parser.add_subparsers(dest='command',required=True)
    make=commands.add_parser('manifest');make.add_argument('source',type=Path);make.add_argument('--id',required=True);make.add_argument('--version',required=True)
    check=commands.add_parser('verify');check.add_argument('source',type=Path)
    copy=commands.add_parser('install');copy.add_argument('source',type=Path);copy.add_argument('--destination',type=Path,required=True)
    args=parser.parse_args()
    try:
        if args.command=='manifest':create(args.source,args.id,args.version);print(args.source/MANIFEST)
        elif args.command=='verify':data=read_manifest(args.source);print(f'{data["id"]} {data["version"]}: {len(data["files"])} verified files')
        else:print(install(args.source,args.destination))
    except (ValueError,OSError,TypeError) as error:parser.exit(1,str(error)+'\n')


if __name__=='__main__':main()
