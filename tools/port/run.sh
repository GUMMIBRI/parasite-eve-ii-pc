#!/bin/sh
# Run the port for N seconds (default 20) against a disc cue; the SDL handler swallows SIGTERM, so KILL.
cd "$(dirname "$0")/../.."
exec timeout -s KILL "${2:-20}" ./build-port/parasite-eve-ii-pc "${1:-$PE2_DISC}"
