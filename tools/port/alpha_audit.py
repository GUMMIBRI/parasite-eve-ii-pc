#!/usr/bin/env python3
"""Read-only host ABI diagnostics and unresolved-placeholder inventory.

Uses each translation unit's actual build flags, including overlay variants.
Diagnostics are candidates for review, not proof that a callback is reachable.
"""
import argparse
from collections import Counter
from concurrent.futures import ThreadPoolExecutor
import json
from pathlib import Path
import re
import shlex
import subprocess

ROOT = Path(__file__).resolve().parents[2]


def inspect_unit(entry):
    args = entry.get('arguments') or shlex.split(entry['command'])
    clean = []
    skip = False
    for arg in args:
        if skip:
            skip = False
            continue
        if arg in ('-o', '-MF', '-MT', '-MQ'):
            skip = True
        elif arg not in ('-c', '-w', '-MD', '-MMD', '-MP') and not arg.startswith('-Wno-'):
            clean.append(arg)
    clean += ['-fsyntax-only', '-ferror-limit=0', '-fno-color-diagnostics',
              '-Wint-conversion', '-Wpointer-to-int-cast', '-Wint-to-pointer-cast',
              '-Wincompatible-pointer-types', '-Wincompatible-function-pointer-types',
              '-Wreturn-type', '-Warray-bounds', '-Wformat',
              '-Wimplicit-function-declaration', '-Wstrict-prototypes']
    run = subprocess.run(clean, cwd=entry['directory'], text=True,
                         stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    return {'file': entry['file'], 'command': clean, 'exitCode': run.returncode,
            'diagnostics': run.stdout}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--build-dir', type=Path, default=ROOT / 'build-all')
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--jobs', type=int, default=6)
    parser.add_argument('--binary', type=Path)
    opts = parser.parse_args()
    entries = json.loads((opts.build_dir / 'compile_commands.json').read_text())
    entries = [e for e in entries if str(ROOT / 'src') + '/' in e['file']
               and '/third_party/' not in e['file']
               and Path(e['file']).name not in ('asm_data.c', 'asset_parts_table.c', 'unresolved_stubs.c')]
    source = (ROOT / 'src/port/unresolved_stubs.c').read_text()
    functions = re.findall(r'weak\)\) void (\w+)\(void\)', source)
    data = re.findall(r'weak\)\) unsigned char (\w+)\[', source)
    with ThreadPoolExecutor(max_workers=opts.jobs) as pool:
        results = list(pool.map(inspect_unit, entries))
    warnings = Counter(re.findall(r'\[(-W[^\]]+)\]', '\n'.join(r['diagnostics'] for r in results)))
    report = {'translationUnits': len(results),
              'unitsWithErrors': sum(r['exitCode'] != 0 for r in results),
              'warningCounts': dict(warnings.most_common()),
              'placeholderFunctions': functions, 'placeholderData': data,
              'units': [r for r in results if r['diagnostics']]}
    if opts.binary:
        # Mach-O weak definitions: a strong implementation overrides the generated stub.
        nm = subprocess.run(['nm', '-m', str(opts.binary)], text=True, capture_output=True, check=True)
        weak = {m.group(1) for line in nm.stdout.splitlines()
                if 'weak' in line and (m := re.search(r' _(\w+)$', line))}
        report['binary'] = str(opts.binary)
        report['activePlaceholderFunctions'] = sorted(weak.intersection(functions))
        report['activePlaceholderData'] = sorted(weak.intersection(data))
    opts.output.parent.mkdir(parents=True, exist_ok=True)
    opts.output.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps({k: v for k, v in report.items() if k not in
                     ('units', 'placeholderFunctions', 'placeholderData',
                      'activePlaceholderFunctions', 'activePlaceholderData')}, indent=2))
    for key in ('placeholderFunctions', 'placeholderData', 'activePlaceholderFunctions', 'activePlaceholderData'):
        if key in report:
            print(f'{key}: {len(report[key])}')
    print(f'Full evidence: {opts.output}')


if __name__ == '__main__':
    main()
