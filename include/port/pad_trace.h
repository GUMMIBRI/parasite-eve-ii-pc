#ifndef PORT_PAD_TRACE_H
#define PORT_PAD_TRACE_H
#include <stdint.h>
#include <stdio.h>
/* One port-zero VBlank sample per line: decimal index, then raw pad bytes in
 * hex. Status, controller ID, active-low buttons and analog axes are retained.
 * This is a native interchange format, not a DuckStation recording format. */
int pePadTraceHeader(FILE* file, int writing);
int pePadTraceWrite(FILE* file, uint64_t index, const char* pad, size_t length);
/* 1 = complete sample, 0 = clean EOF, -1 = invalid/truncated sample or I/O error.
 * Failure leaves the destination unchanged. */
int pePadTraceRead(FILE* file, uint64_t index, char* pad, size_t length);
/* Development stdin command: advance COUNT MASK, or quit. Outputs change
 * only for a valid advance. Returns 1=advance, 0=quit, -1=invalid. */
int pePadControlParse(const char* line, uint32_t* count, uint16_t* mask);
#endif
