#!/usr/bin/env python3
"""Client for the PE1 DuckStation regtest AI socket (default: local runner on port 49711).

The fork's `advance` reply acknowledges submission, not completion. Always poll
until paused before changing input or taking a reference screenshot. Recorded
PE2PAD samples represent emulated frames; align boot/game state before comparing
them with the native port's pad polls.
"""
import argparse
import json
from pathlib import Path
import socket
import struct
import time
import zlib

BUTTONS = {0: "Select", 3: "Start", 4: "Up", 5: "Right", 6: "Down",
           7: "Left", 8: "L2", 9: "R2", 10: "L1", 11: "R1",
           12: "Triangle", 13: "Circle", 14: "Cross", 15: "Square"}


class DuckStation:
    def __init__(self, host="127.0.0.1", port=49711, timeout=60):
        self.timeout = timeout
        self.socket = socket.create_connection((host, port), timeout=timeout)
        self.stream = self.socket.makefile("rb")
        if self.line() != "OK ai-control ready":
            self.close()
            raise RuntimeError("unexpected AI control greeting")

    def close(self):
        self.stream.close()
        self.socket.close()

    def line(self):
        line = self.stream.readline(4097)
        if not line or len(line) > 4096 or not line.endswith(b"\n"):
            raise RuntimeError("incomplete AI control reply")
        reply = line.decode("ascii").strip()
        if reply.startswith("ERR"):
            raise RuntimeError(reply)
        return reply

    def command(self, text):
        self.socket.sendall((text + "\n").encode("ascii"))
        return self.line()

    def status(self):
        reply = self.command("status")
        if not reply.startswith("OK "):
            raise RuntimeError(reply)
        return {key: int(value) for key, value in
                (part.split("=", 1) for part in reply[3:].split())}

    def advance(self, frames, mask):
        before = self.status()
        if not before["running"] or not before["paused"]:
            raise RuntimeError("advance requires a booted, paused reference")
        if frames < 1 or frames >= before["frames_remaining"]:
            raise ValueError("advance must leave at least one frame in the runner")
        if not 0 <= mask <= 0xFFFF or mask & 6:
            raise ValueError("use a 16-bit digital-pad mask without L3/R3")
        self.command("release")
        names = [f"{name}=1" for bit, name in BUTTONS.items() if mask & (1 << bit)]
        if names:
            self.command("buttons " + " ".join(names))
        self.command(f"advance {frames}")
        deadline = time.monotonic() + self.timeout
        while True:
            after = self.status()
            if after["paused"] and after["advance_remaining"] == 0:
                break
            if time.monotonic() >= deadline:
                raise TimeoutError("advance is still running; query status before retrying")
            time.sleep(0.01)
        if before["frames_remaining"] - after["frames_remaining"] != frames:
            raise RuntimeError("reference did not advance the requested frame count")
        return after

    def screenshot(self, path):
        if not self.status()["paused"]:
            raise RuntimeError("pause the reference before capturing")
        header = self.command("screenshot").split()
        if len(header) != 6 or header[0] != "SCREENSHOT":
            raise RuntimeError("unexpected screenshot header")
        width, height, pitch, size, frame = map(int, header[1:])
        if not (0 < width <= 8192 and 0 < height <= 8192 and
                width * 4 <= pitch <= 65536 and size == pitch * height):
            raise RuntimeError("invalid RGBA screenshot dimensions")
        pixels = self.stream.read(size)
        if len(pixels) != size:
            raise RuntimeError("truncated RGBA screenshot")
        def chunk(kind, data):
            return (struct.pack(">I", len(data)) + kind + data +
                    struct.pack(">I", zlib.crc32(kind + data)))
        rows = b"".join(b"\0" + pixels[y * pitch:y * pitch + width * 4]
                        for y in range(height))
        png = b"\x89PNG\r\n\x1a\n"
        png += chunk(b"IHDR", struct.pack(">IIBBBBB", width, height, 8, 6, 0, 0, 0))
        png += chunk(b"IDAT", zlib.compress(rows)) + chunk(b"IEND", b"")
        path.write_bytes(png)
        return {"frame": frame, "width": width, "height": height, "path": str(path)}


def append_input(path, frames, mask):
    # Append only after the emulator confirms every requested frame completed.
    if path.exists():
        lines = path.read_text(encoding="ascii").splitlines()
        if not lines or lines[0] != "PE2PAD 1":
            raise ValueError("invalid input recording header")
        for index, line in enumerate(lines[1:]):
            recorded_index, value = line.split()
            if int(recorded_index) != index or len(bytes.fromhex(value)) != 34:
                raise ValueError("invalid existing input recording")
        start = len(lines) - 1
    else:
        path.write_text("PE2PAD 1\n", encoding="ascii")
        start = 0
    sample = bytes((0, 0x41, (~mask) & 255, ((~mask) >> 8) & 255)) + bytes(30)
    with path.open("a", encoding="ascii") as out:
        for index in range(start, start + frames):
            out.write(f"{index} {sample.hex()}\n")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--host", default="127.0.0.1")
    parser.add_argument("--port", type=int, default=49711)
    parser.add_argument("--timeout", type=float, default=60)
    commands = parser.add_subparsers(dest="command", required=True)
    commands.add_parser("status")
    advance = commands.add_parser("advance")
    advance.add_argument("frames", type=int)
    advance.add_argument("--buttons", type=lambda x: int(x, 0), default=0)
    advance.add_argument("--record", type=Path, help="append one PE2PAD sample per emulated frame")
    screenshot = commands.add_parser("screenshot")
    screenshot.add_argument("output", type=Path)
    args = parser.parse_args()
    client = DuckStation(args.host, args.port, args.timeout)
    try:
        if args.command == "status":
            result = client.status()
        elif args.command == "advance":
            if args.record:
                append_input(args.record, 0, args.buttons)
            result = client.advance(args.frames, args.buttons)
            if args.record:
                append_input(args.record, args.frames, args.buttons)
        else:
            result = client.screenshot(args.output)
        print(json.dumps(result, sort_keys=True))
    finally:
        client.close()


if __name__ == "__main__":
    main()
