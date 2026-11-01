#ifndef GTE_H
#define GTE_H

/// GTE command macros that emit real COP2 instructions.
///
/// Psy-Q's `inline_c.h` writes every GTE *command* as two `nop`s followed by a
/// placeholder word (`gte_rtps()` emits `.word 0x0000007f`). Sony's DMPSX tool
/// then rewrote each placeholder in the compiled object into the real COP2
/// instruction, and the game was built from that output. This toolchain has no
/// DMPSX step, so this header takes its place: it keeps Psy-Q's macro names and
/// its `nop; nop;` prefix, and substitutes the instruction word DMPSX would
/// have produced. Code can then call the SDK macros the way the original source
/// did, including through the compound macros in `gtemac.h`.
///
/// Only the commands change. The register load and store macros in
/// `inline_c.h` already emit real `lwc2`/`swc2`/`mtc2`/`ctc2` instructions and
/// are used unchanged. The words match the instruction table in
/// `gte_macros.inc`, the assembler-side replacement for DMPSX.
///
/// Notation in the comments below. Inputs are the vector registers V0..V2, the
/// IR vector IR1..3 with its scalar IR0, the input colour RGBC and the control
/// matrices: the rotation matrix RT with translation TR, the light matrix LLM,
/// the light colour matrix LCM and the background colour BK.
/// Results land in MAC1..3 and IR1..3 (and MAC0 for scalar results); colours
/// are pushed into the colour FIFO RGB0..2, screen points into SXY0..2 and
/// depths into SZ0..3. Products are shifted right by 12 bits for 4.12 fixed
/// point; the `0` and `_sf0` forms leave them unshifted. Commands marked
/// "clamped" limit IR1..3 to non-negative values.
///
/// Only the commands the game's code uses are defined, directly or through a
/// `gtemac.h` compound (`gte_rt` is reached only that way, from `gte_RotTrans`
/// and `gte_CompMatrix`). Every other command - the remaining MVMVA forms, the
/// depth-cue, `nc`/`ncd`, `cc`/`cdp` and unshifted (`0`) commands, and all the
/// `_b` forms that drop the leading `nop`s - keeps Psy-Q's placeholder, which
/// still compiles and assembles but is not a GTE instruction. A function that
/// needs one must add it here first, with the word from `gte_macros.inc`.

/// Host build: there is no COP2 and no DMPSX. PsyZ's libgte.h maps the SDK
/// macros it knows onto its GTE emulation, and port/gte_compat.h supplies the
/// rest in portable C.
#include <libgte.h>
#include "port/gte_compat.h"

#endif
