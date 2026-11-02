#ifndef PORT_TMD_SOURCE_H
#define PORT_TMD_SOURCE_H
#include <stddef.h>
#include <stdint.h>
#include "main/tmd_types.h"
/* Decode a PS1 source descriptor from a writable, little-endian package image.
 * The image must be 4-byte aligned and remain alive while the source is used.
 * Arrays stay in the image; only the pointer-bearing descriptor is expanded.
 * Returns 0 on success, -1 for malformed/unsupported input. Output is unchanged
 * on failure. This validates storage/stream framing, not primitive vertex indices.
 * GPU buffer capacities still need conversion to host packet sizes before use. */
int peTmdDecodeSource(TmdSource* out, void* image, size_t bytes,
                      uint32_t loadAddress, size_t sourceOffset);
#endif
