#!/usr/bin/env python3
"""Rewrite the generated declared-clip includes (build/include/assets/<group>/*clips*.inc) with registry-bound arrays.

The build rule (ninja_config.py, rule animation-source) writes the same files; this regenerates just those from the
user's extraction. Run with the project's venv Python."""
import sys
from pathlib import Path
sys.path.insert(0, '.')
import ninja_config as nc
from tools.buildsteps import gen_animation_source as gas, gen_model_source as gms

clips, _banks = nc.declared_animation_sources('USA')
for package, _usd, inc in clips:
    inc = Path(inc)
    inc.write_text(gas.clips_source(package, Path('assets/USA')))
models = nc.model_source_includes('USA')
for name, _usd, inc in models:
    Path(inc).write_text(gms.source(name, Path('assets/USA')))
print(f'{len(clips)} clip and {len(models)} model includes written', file=sys.stderr)
