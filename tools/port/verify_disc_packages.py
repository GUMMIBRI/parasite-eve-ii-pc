#!/usr/bin/env python3
"""Check the C disc reader (src/port/disc_assets.c) against the extraction: for every package in the manifest,
the bytes it reads from the disc image must equal assets/USA/pe2pkg/<package>.pe2pkg.

Usage: verify_disc_packages.py <manifest.json> <discread-binary> <disc.cue> [disc2.cue]
Packages that are not on the given disc(s) are reported as 'absent', not as failures."""
import hashlib, json, subprocess, sys

manifest, tool = json.load(open(sys.argv[1])), sys.argv[2]
cues = sys.argv[3:]
ok = bad = absent = 0
for name, p in sorted(manifest['packages'].items()):
    want = hashlib.sha1(open(f'assets/USA/pe2pkg/{name}.pe2pkg', 'rb').read()).hexdigest()
    got = None
    for cue in cues:
        r = subprocess.run([tool, cue, str(p['stage']), str(p.get('disc_folder', 0)), str(p['disc_file'])],
                           capture_output=True)
        if r.returncode == 0:
            got = hashlib.sha1(r.stdout).hexdigest()
            break
    if got is None:
        absent += 1
    elif got == want:
        ok += 1
    else:
        bad += 1
        print('MISMATCH', name, p)
print(f'{ok} identical, {bad} different, {absent} absent from the given disc(s)')
sys.exit(1 if bad else 0)
