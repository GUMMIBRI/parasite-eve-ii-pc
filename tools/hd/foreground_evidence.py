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


def normalized_gpu_commands(data):
    """Decode an original GP0 audit, ignoring only unused textured fields.

    Equality is supporting input evidence, not proof of equal VRAM, PGXP hints,
    or game state. Unknown commands remain byte-exact for conservative checks.
    """
    if len(data)%4:raise ValueError('Truncated GPU command audit')
    words=struct.unpack('<'+'I'*(len(data)//4),data);offset=0;commands=[]
    while offset<len(words):
        count=words[offset];offset+=1
        if not count or count>len(words)-offset:raise ValueError('Invalid GPU command audit length')
        command=list(words[offset:offset+count]);offset+=count;code=command[0]>>24
        if 0x20<=code<0x40:
            vertices=4 if code&8 else 3;gouraud=bool(code&16);textured=bool(code&4)
            expected=1+vertices*(1+textured+gouraud)-gouraud
            if count!=expected:raise ValueError('Invalid textured polygon length')
            cursor=1
            if textured and code&1:command[0]&=0xff000000
            for vertex in range(vertices):
                if vertex and gouraud:
                    command[cursor]&=0xffffff
                    if textured and code&1:command[cursor]=0
                    cursor+=1
                cursor+=1  # XY
                if textured:
                    if vertex>=2:command[cursor]&=0xffff  # UV high half unused
                    cursor+=1
        elif 0x60<=code<0x80 and code&4 and code&1:
            command[0]&=0xff000000  # raw texture ignores RGB modulation
        commands.append(tuple(command))
    if not commands:raise ValueError('Empty GPU command audit')
    return commands


def compare_gpu_commands(first,second):
    a=normalized_gpu_commands(first);b=normalized_gpu_commands(second)
    differing=next((i for i,(x,y) in enumerate(zip(a,b)) if x!=y),None)
    if differing is None and len(a)!=len(b):differing=min(len(a),len(b))
    return dict(equal=differing is None,first_count=len(a),second_count=len(b),
                first_difference=differing)


def simulation_state(report):
    """Require the capture's additional integer clocks and both gameplay RNGs."""
    state=report.get('simulation_state')
    fields=['anim_frame','frame_count','loop_count','loop_ticks','random_lcg','random_bios']
    if not isinstance(state,dict) or any(type(state.get(k)) is not int or not 0<=state[k]<=0xffffffff for k in fields):
        raise ValueError('Missing or invalid simulation-state evidence')
    return {key:state[key] for key in fields}
