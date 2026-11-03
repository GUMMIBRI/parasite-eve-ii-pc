#ifndef PORT_ASM_APPLY_H
#define PORT_ASM_APPLY_H
/* Fills a global that tools/port/gen_asm_data.py converted from the disassembly: `runs` copy numbers from the
 * PlayStation record to the host struct (widening 32-bit `long`s), `ptrs` set the pointers. The tables are layout
 * and pointer topology only; every number comes from the user's disc. */
#include <stdint.h>
#include <string.h>
#include "port/psyq_compat.h"

typedef struct { uint32_t host, ps1, count; uint8_t psz, hsz, sgn; } PeAsmRun;
/* `target` is the object the original pointed at; without one the pointer is read from the disc record. */
typedef struct { uint32_t host, ps1; void* target; } PeAsmPtr;

static inline void peAsmApply(void* dst, const unsigned char* src, const PeAsmRun* runs, int nr, const PeAsmPtr* ptrs, int np)
{
    unsigned char* d = (unsigned char*)dst;
    for (int i = 0; i < nr; i++) {
        const PeAsmRun* r = &runs[i];
        if (r->psz == r->hsz) {
            memcpy(d + r->host, src + r->ps1, (size_t)r->count * r->psz);
            continue;
        }
        for (uint32_t k = 0; k < r->count; k++) {          /* 4-byte disc `long` to the host's 8 bytes */
            uint32_t v;
            memcpy(&v, src + r->ps1 + k * r->psz, 4);
            int64_t w = r->sgn ? (int64_t)(int32_t)v : (int64_t)v;
            memcpy(d + r->host + k * r->hsz, &w, 8);
        }
    }
    for (int i = 0; i < np; i++) {
        void* p = ptrs[i].target;
        if (!p) {
            uint32_t v;
            memcpy(&v, src + ptrs[i].ps1, 4);
            p = !v ? NULL : (v >= 0x80000000u && v < 0x80200000u) ? PS1_RAM_PTR(v) : (void*)(uintptr_t)v;
        }
        memcpy(d + ptrs[i].host, &p, sizeof p);
    }
}
#endif
