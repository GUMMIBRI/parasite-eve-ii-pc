#!/usr/bin/env python3
"""Rewrite the generated declared-clip includes (build/include/assets/<group>/*clips*.inc) with registry-bound arrays.

The build rule (ninja_config.py, rule animation-source) writes the same files; this regenerates just those from the
user's extraction. Run with the project's venv Python."""
import sys
from pathlib import Path
sys.path.insert(0, '.')
import ninja_config as nc
from tools.buildsteps import gen_animation_source as gas

clips, _banks = nc.declared_animation_sources('USA')
for package, _usd, inc in clips:
    inc = Path(inc)
    inc.write_text(gas.clips_source(package, Path('assets/USA')))
print(f'{len(clips)} clip includes written', file=sys.stderr)
