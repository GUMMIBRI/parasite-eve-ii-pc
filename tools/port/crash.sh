#!/bin/sh
# Run under lldb and print where it crashed (needs PE2_DISC).
cd "$(dirname "$0")/../.."
timeout -s KILL 120 lldb -b -o "run \"$PE2_DISC\"" -o "bt 10" ./build-port/parasite-eve-ii-pc 2>&1 | grep -E "stop reason|frame #" | sed 's/0x[0-9a-f]* //' | cut -c1-200
