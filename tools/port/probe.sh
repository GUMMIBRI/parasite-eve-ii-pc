#!/bin/sh
# Run the port for N seconds (default 30); report how it ended and save a capture of the game window only
# (never the whole screen) to $2 (default /tmp/pe2_win.png). Needs PE2_DISC. Window lookup: tools/port/winid.swift.
cd "$(dirname "$0")/../.."
export PE2_FAST=${PE2_FAST-1}
SECS=${1:-30}; OUT=${2:-/tmp/pe2_win.png}
./build-port/parasite-eve-ii-pc "$PE2_DISC" >/tmp/pe2_run.log 2>&1 &
PID=$!
sleep "$SECS"
if kill -0 $PID 2>/dev/null; then
  echo "still running after ${SECS}s"
  ID=$(/tmp/pe2_winid 2>/dev/null); [ -n "$ID" ] && screencapture -x -l "$ID" "$OUT" && echo "window capture: $OUT"
  kill -9 $PID
else
  wait $PID; echo "exited rc=$?"
fi
grep -v "platform\|ResetGraph" /tmp/pe2_run.log | tail -5
