#!/usr/bin/env python3
"""Freeze the generated includes the host build reads into include/generated (committed, no game data).

The build used to read build/include, written from the user's disc by tools/peassets (ninja). Every array of game data
in it is loaded from the disc at run time since phase 0; what the compiler still needs is the layout: types, sizes,
decoders and the registrations. This keeps those: each `#ifdef PE_EMBED_ASSETS ... #else X #endif` becomes X and the
leaf data includes (only read by the dropped branches) are not copied.

    freeze_includes.py [--src build/include] [--dst include/generated] [--objects build-port]

Which files are needed comes from the compiler's own depfiles of the build in --objects (built with the full set).
"""
from __future__ import annotations

import argparse
import re
import shutil
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
COND = re.compile(r"\s*#\s*(if|ifdef|ifndef)\b")
END = re.compile(r"\s*#\s*endif\b")
ELSE = re.compile(r"\s*#\s*else\b")
EMBED = re.compile(r"\s*#\s*ifdef\s+PE_EMBED_ASSETS\b")


def strip_embed(text: str) -> str:
    out: list[str] = []
    state = []            # per open conditional: 'plain', 'embed' (dropping), 'disc' (keeping the else branch)
    for line in text.splitlines():
        if EMBED.match(line):
            state.append("embed")
            continue
        if COND.match(line):
            state.append("plain")
            if "embed" in state[:-1]:
                continue
        elif END.match(line):
            top = state.pop()
            if top != "plain" or "embed" in state:
                continue
        elif ELSE.match(line) and state and state[-1] == "embed":
            state[-1] = "disc"
            continue
        if "embed" in state:
            continue
        out.append(line)
    if state:
        raise SystemExit("unbalanced conditionals")
    return "\n".join(out) + "\n"


def depfile_includes(objects: Path, src: Path) -> set[Path]:
    found: set[Path] = set()
    prefix = str(src.resolve()) + "/"
    for d in objects.rglob("*.o.d"):
        for tok in re.split(r"[\s\\]+", d.read_text()):
            if tok.startswith(prefix):
                found.add(Path(tok))
    return found


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--src", type=Path, default=ROOT / "build" / "include")
    ap.add_argument("--dst", type=Path, default=ROOT / "include" / "generated")
    ap.add_argument("--objects", type=Path, default=ROOT / "build-port")
    ap.add_argument("--all", action="store_true", help="copy every file, not only what the depfiles name (then build, then --prune)")
    ap.add_argument("--prune", action="store_true",
                    help="--src is the frozen tree itself: drop what the build in --objects no longer reads")
    args = ap.parse_args()
    src = args.src.resolve()
    if args.prune:
        wanted = depfile_includes(args.objects, src)
        gone = [p for p in src.rglob("*") if p.is_file() and p not in wanted]
        for p in gone:
            p.unlink()
        print(f"pruned {len(gone)} files, {len(wanted)} kept")
        return 0
    wanted = set(p for p in src.rglob("*") if p.is_file()) if args.all else depfile_includes(args.objects, src)
    # a leaf is read only by the dropped branch: keep what survives stripping
    if args.dst.exists():
        shutil.rmtree(args.dst)
    kept = total = 0
    for path in sorted(wanted):
        rel = path.relative_to(src)
        text = path.read_text()
        if "PE_EMBED_ASSETS" in text:
            text = strip_embed(text)
        dst = args.dst / rel
        dst.parent.mkdir(parents=True, exist_ok=True)
        dst.write_text(text)
        kept += 1
        total += len(text)
    print(f"{kept} files, {total / 1e6:.2f} MB -> {args.dst}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
