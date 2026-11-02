#ifndef PORT_TMD_LAYOUT_H
#define PORT_TMD_LAYOUT_H
#include "main/tmd_types.h"
/* Expand PS1 packet capacities and pre-pass byte destinations for PsyZ's
 * native packet layout. Idempotent per source. The writable, trusted stream
 * must already be framed/validated (as by peTmdDecodeSource); no length is
 * present in a legacy compiled source. Failure leaves the source unchanged. */
/* Intermediate state: packet storage expanded, draw handlers still unresolved.
 * Handler resolution changes this to the game's ordinary resolved state (1). */
enum { PE_TMD_HOST_LAYOUT_READY = 2 };
int peTmdPreparePacketLayout(TmdSource* source);
#endif
