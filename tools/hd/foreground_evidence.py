"""Strict evidence for static foregrounds that cannot produce visible material."""
import hashlib
import json
import struct


def verify_empty_sources(directory,key,location,metadata):
    """Prove all audited native words are zero, including the PS1 STP bit.

    A black reference RGB is insufficient: native 0x8000 is covered black.
    Reject changed or incomplete inputs instead of relaxing visible checks.
    """
    report=json.loads((directory/'report.json').read_text())
    capture=report.get('capture',{})
    if report.get('format')!='pe2-foreground-source-audit-v1' or capture.get('key')!=key or capture.get('location')!=location:
        raise ValueError('Empty-source proof belongs to another capture')
    records=report.get('sprites',[])
    if not 1<=len(records)<=512:raise ValueError('Empty-source proof needs complete source records')
    if len(metadata)!=48+16*len(records):raise ValueError('Empty-source descriptor length mismatch')
    magic,background,atlas,*fields=struct.unpack_from('<8sQQ6I',metadata)
    if magic not in [b'PE2FG1\0\0',b'PE2FG2\0\0'] or background!=int(key,16) or not atlas or atlas==background or fields[:4]!=location[:4] or fields[4]!=len(records):
        raise ValueError('Empty-source proof does not match foreground descriptor')
    previous=-1;cells=0
    for ordinal,record in enumerate(records):
        index=record['index'];source=record['source'];width,height=source['w'],source['h']
        if not isinstance(index,int) or not previous<index<=4095 or not 1<=width<=320 or not 1<=height<=240:
            raise ValueError('Invalid empty-source identity/extent')
        entry=list(struct.unpack_from('<IHHHHBBH',metadata,48+ordinal*16))
        if magic==b'PE2FG2\0\0':entry[0]&=~4096
        expected=[index,source['tpage']&511,source['clut'],width,height,source['u0'],source['v0'],cells]
        if entry!=expected:raise ValueError('Empty-source proof contains different foreground sources')
        cells+=((width+15)//16)*((height+15)//16)
        previous=index
        native=(directory/f'sprite-{index:04d}.rgb555').read_bytes()
        if len(native)!=width*height*2 or hashlib.sha256(native).hexdigest()!=record['native_sha256']:
            raise ValueError('Empty-source input changed since audit')
        if any(native):raise ValueError('Foreground contains covered native texels')
    if fields[5]!=cells:raise ValueError('Empty-source descriptor cell count mismatch')
    return len(records)


def check_material_evidence(changed,replacements,empty=False):
    if not isinstance(replacements,int) or replacements<0:
        raise AssertionError('Invalid foreground replacement count')
    if empty:
        if changed:raise AssertionError('Verified empty foreground changed the rendered frame')
    elif not replacements or not changed:
        raise AssertionError('Visible foreground needs active replacements and a material change')
