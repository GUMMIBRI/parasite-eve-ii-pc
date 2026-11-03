#!/usr/bin/env python3
"""Write C decoders for room layouts that carry pointers to stdout: gen_layout_decoders.py KIND [KIND...]

See tools/peassets/room/decoders.py: one disc record (PS1 layout, 32-bit addresses) to the host struct, pointers
accepted only as zero."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / "tools" / "peassets"))
from room.decoders import decoder  # noqa: E402

if __name__ == "__main__":
    print("#include <stdint.h>\n#include <stdlib.h>\n#include <string.h>\n")
    for k in sys.argv[1:]:
        print(decoder(k))
