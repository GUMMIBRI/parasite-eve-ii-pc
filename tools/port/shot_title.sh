#!/bin/sh
# Run the port until the intro movie has ended, then capture the game window (only that window) once.
# Usage: shot_title.sh [seconds-after-movie] [out.png]   (needs PE2_DISC)
cd "$(dirname "$0")/../.."
AFTER=${1:-6}; OUT=${2:-/tmp/pe2_title.png}
PE2_TRACE=1 PE2_FAST=1 ./build-port/parasite-eve-ii-pc "$PE2_DISC" >/tmp/pe2_run.log 2>&1 &
PID=$!
# movie runs first (movieStep 3); wait for it to end
until grep -aq "movieStep=3" /tmp/pe2_run.log || ! kill -0 $PID 2>/dev/null; do sleep 1; done
until grep -aqE "tick=[0-9]+ movieStep=0" /tmp/pe2_run.log && [ "$(grep -ac 'movieStep=3' /tmp/pe2_run.log)" -gt 5 ] && [ "$(tail -1 /tmp/pe2_run.log | grep -ac 'movieStep=0')" = 1 ] || ! kill -0 $PID 2>/dev/null; do sleep 1; done
sleep "$AFTER"
ID=$(/tmp/pe2_winid 2>/dev/null); [ -n "$ID" ] && screencapture -x -l "$ID" "$OUT" && echo "window capture: $OUT"
kill -9 $PID 2>/dev/null
