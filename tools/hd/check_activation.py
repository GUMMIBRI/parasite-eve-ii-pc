#!/usr/bin/env python3
"""Check real host CLI/settings activation using isolated profiles and owner discs."""
import argparse
import json
import os
from pathlib import Path
import subprocess
import tempfile


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--binary',type=Path,default=Path('build-port/parasite-eve-ii-pc'))
    parser.add_argument('--disc',type=Path,required=True)
    parser.add_argument('--disc2',type=Path,required=True)
    parser.add_argument('--output',type=Path,default=Path('build-hd-study/activation-check'))
    args=parser.parse_args()
    root=args.output.resolve();root.mkdir(parents=True,exist_ok=True)
    (root/'report.json').unlink(missing_ok=True)
    checks=[]
    with tempfile.TemporaryDirectory(prefix='profile-',dir=root) as profile:
        env={k:v for k,v in os.environ.items() if not k.startswith('PE2_')}
        env.update(PSYZ_HEADLESS='1',SDL_AUDIODRIVER='dummy',PE2_CONFIG_DIR=profile)
        def run(name,options=(),override=None,valid=True):
            command=[str(args.binary.resolve()),'--validate-discs',*options]
            process=subprocess.run(command,env={**env,**(override or {})},capture_output=True,text=True,timeout=20)
            (root/(name+'.log')).write_text(process.stdout+process.stderr)
            assert (process.returncode==0)==valid,(name,process.returncode,process.stderr)
            checks.append(name)
        def preferences():
            return dict(line.split('=',1) for line in (Path(profile)/'settings.ini').read_text().splitlines() if '=' in line)
        pack=root/'pack = example';pack.mkdir(exist_ok=True)
        relative=os.path.relpath(pack)
        run('select-relative', ['--disc',str(args.disc.resolve()),'--disc2',str(args.disc2.resolve()),'--hd-backgrounds',relative])
        saved=preferences()
        assert saved['hd_backgrounds']=='1' and Path(saved['hd_background_path']).is_absolute()
        assert Path(saved['hd_background_path']).resolve()==pack
        run('reload');assert preferences()['hd_background_path']==saved['hd_background_path']
        run('disable',['--no-hd-backgrounds']);assert preferences()['hd_backgrounds']=='0'
        run('reload-disabled');assert preferences()['hd_backgrounds']=='0'
        run('environment',override={'PE2_HD_BACKGROUNDS':str(pack)})
        assert preferences()['hd_backgrounds']=='1' and preferences()['hd_background_path']==str(pack)
        run('cli-overrides-environment',['--no-hd-backgrounds'],{'PE2_HD_BACKGROUNDS':str(pack)})
        assert preferences()['hd_backgrounds']=='0'
        run('cli-overrides-invalid-environment',['--no-hd-backgrounds'],{'PE2_HD_BACKGROUNDS':'bad\npath'})
        assert preferences()['hd_backgrounds']=='0'
        before=(Path(profile)/'settings.ini').read_bytes()
        run('invalid-environment',override={'PE2_HD_BACKGROUNDS':'bad\npath'},valid=False)
        assert (Path(profile)/'settings.ini').read_bytes()==before
        for name,options in [
            ('missing',['--hd-backgrounds']),('empty',['--hd-backgrounds','']),
            ('newline',['--hd-backgrounds','bad\npath']),('too-long',['--hd-backgrounds','x'*4096]),
            ('duplicate',['--hd-backgrounds',str(pack),'--hd-backgrounds',str(pack)]),
            ('conflict',['--hd-backgrounds',str(pack),'--no-hd-backgrounds']),
            ('reverse-conflict',['--no-hd-backgrounds','--hd-backgrounds',str(pack)]),
            ('duplicate-off',['--no-hd-backgrounds','--no-hd-backgrounds'])]:
            run(name,options,valid=False)
            assert (Path(profile)/'settings.ini').read_bytes()==before,name
    (root/'report.json').write_text(json.dumps(dict(passed=True,checks=checks),indent=2)+'\n')
    print('PASS: persisted pack selection, disable/reload, environment/CLI precedence, invalid-option rejection')


if __name__=='__main__':main()
