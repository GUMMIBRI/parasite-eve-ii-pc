#ifndef PORT_GTE_COMPAT_H
#define PORT_GTE_COMPAT_H

/// Host implementations of the GTE inline macros the game uses and PsyZ's
/// libgte.h does not provide.
///
/// Everything here is written against PsyZ's register-level API
/// (`Psyz_GteDataRead/DataWrite/CtrlRead/CtrlWrite/Command`). Register numbers
/// are the COP2 data/control register numbers (see `include/gte_macros.inc`).
/// The macros take memory addresses, as Psy-Q's did; all memory access goes
/// through `memcpy`, so addresses may be unaligned and are never assumed to be
/// 32 bits wide. Compound macros (`gte_RotTransPers`, `gte_MulMatrix0`, ...)
/// issue the same sequence of primitives as Psy-Q's `gtemac.h`, so they leave
/// the same GTE registers modified.
///
/// Only meaningful on the host (`__psyz`). On the PS1 build the real inline
/// assembler macros from `decomp/gte.h` are used and this header is empty.

#ifdef __psyz

#include <stdint.h>
#include <stddef.h>
#include <libgpu.h>
#include <string.h>
#include <libgte.h>
#include <psyz/gte.h>

/* ------------------------------------------------------------------------ */
/* Memory helpers                                                           */
/* ------------------------------------------------------------------------ */

static inline unsigned int PortGte_Load32(const void* p) {
    unsigned int v;
    memcpy(&v, p, sizeof(v));
    return v;
}
static inline void PortGte_Store32(void* p, unsigned int v) {
    memcpy(p, &v, sizeof(v));
}
static inline unsigned int PortGte_LoadU16(const void* p) {
    uint16_t v;
    memcpy(&v, p, sizeof(v));
    return v;
}
static inline unsigned int PortGte_LoadS16(const void* p) {
    int16_t v;
    memcpy(&v, p, sizeof(v));
    return (unsigned int)(int)v;
}
static inline void PortGte_Store16(void* p, unsigned int v) {
    uint16_t h = (uint16_t)v;
    memcpy(p, &h, sizeof(h));
}
static inline void PortGte_Store8(void* p, unsigned int v) {
    uint8_t b = (uint8_t)v;
    memcpy(p, &b, sizeof(b));
}

/* Address operand: accepts any pointer (or integer) expression. */
#define PORTGTE_PTR(x) ((void*)(uintptr_t)(x))
#define PORTGTE_CPTR(x) ((const void*)(uintptr_t)(x))
#define PORTGTE_BYTES(x, off) ((char*)PORTGTE_PTR(x) + (off))

/* ------------------------------------------------------------------------ */
/* Register and command helpers                                             */
/* ------------------------------------------------------------------------ */

static inline void PortGte_LdIrFromS16(const void* p) {
    Psyz_GteDataWrite(9, PortGte_LoadU16(p));
    Psyz_GteDataWrite(10, PortGte_LoadU16((const char*)p + 2));
    Psyz_GteDataWrite(11, PortGte_LoadU16((const char*)p + 4));
}
static inline void PortGte_StIrToS16(void* p) {
    PortGte_Store16(p, Psyz_GteDataRead(9));
    PortGte_Store16((char*)p + 2, Psyz_GteDataRead(10));
    PortGte_Store16((char*)p + 4, Psyz_GteDataRead(11));
}
/* Pushes one packed screen XY into the SXY FIFO, as a write to SXYP does. */
static inline void PortGte_PushSxy(unsigned int xy) {
    Psyz_GteDataWrite(12, Psyz_GteDataRead(13));
    Psyz_GteDataWrite(13, Psyz_GteDataRead(14));
    Psyz_GteDataWrite(14, xy);
    Psyz_GteDataWrite(15, xy);
}
static inline void PortGte_ReadRotMatrix(MATRIX* m) {
    unsigned int w[8];
    int i;
    for (i = 0; i < 8; i++) {
        w[i] = Psyz_GteCtrlRead((unsigned)i);
    }
    /* RT: ctrl 0..4 are the nine halfwords, ctrl 5..7 the translation. */
    memcpy((char*)m + 0, &w[0], 4);
    memcpy((char*)m + 4, &w[1], 4);
    memcpy((char*)m + 8, &w[2], 4);
    memcpy((char*)m + 12, &w[3], 4);
    memcpy((char*)m + 16, &w[4], 4);
    memcpy((char*)m + 20, &w[5], 4);
    memcpy((char*)m + 24, &w[6], 4);
    memcpy((char*)m + 28, &w[7], 4);
}
static inline void PortGte_TransposeMatrix(const void* src, void* dst) {
    uint16_t t[9];
    int r, c;
    for (r = 0; r < 3; r++) {
        for (c = 0; c < 3; c++) {
            memcpy(&t[r * 3 + c], (const char*)src + 2 * (r * 3 + c), 2);
        }
    }
    for (r = 0; r < 3; r++) {
        for (c = 0; c < 3; c++) {
            memcpy((char*)dst + 2 * (r * 3 + c), &t[c * 3 + r], 2);
        }
    }
}
static inline void PortGte_RotTransLV(const void* in, void* out) {
    int32_t v[3];
    uint32_t r[3];
    int i;
    unsigned int lo[3], mid[3], hi[3];
    memcpy(v, in, sizeof(v));
    for (i = 0; i < 3; i++) {
        int32_t x = v[i];
        int neg = x < 0;
        int sub = neg ? 1024 : 0;
        lo[i] = (unsigned int)((x & 1023) - sub);
        mid[i] = (unsigned int)((((x >> 10) & 1023) - sub) + neg);
        hi[i] = (unsigned int)((x >> 20) + neg);
    }
    Psyz_GteDataWrite(0, (lo[0] & 0xFFFF) | (lo[1] << 16));
    Psyz_GteDataWrite(1, lo[2] & 0xFFFF);
    Psyz_GteDataWrite(2, (mid[0] & 0xFFFF) | (mid[1] << 16));
    Psyz_GteDataWrite(3, mid[2] & 0xFFFF);
    Psyz_GteDataWrite(4, (hi[0] & 0xFFFF) | (hi[1] << 16));
    Psyz_GteDataWrite(5, hi[2] & 0xFFFF);
    Psyz_GteCommand(0x4A480012); /* RT * V0 + TR, sf=1 */
    for (i = 0; i < 3; i++) {
        r[i] = Psyz_GteDataRead(25 + i);
    }
    Psyz_GteCommand(0x4A40E012); /* RT * V1, sf=0 */
    for (i = 0; i < 3; i++) {
        r[i] += (uint32_t)((int32_t)Psyz_GteDataRead(25 + i) >> 2);
    }
    Psyz_GteCommand(0x4A416012); /* RT * V2, sf=0 */
    for (i = 0; i < 3; i++) {
        r[i] += Psyz_GteDataRead(25 + i) << 8;
    }
    memcpy(out, r, sizeof(r));
}

/* ------------------------------------------------------------------------ */
/* Loads                                                                    */
/* ------------------------------------------------------------------------ */

/// IR1..3 = three signed 16-bit values at `r0`.
#define gte_ldsv(r0) PortGte_LdIrFromS16(PORTGTE_CPTR(r0))
/// IR1..3 = three 32-bit words at `r0` (truncated to 16 bits by the GTE).
#define gte_ldlvl(r0)                                                          \
    do {                                                                       \
        const void* port_p_ = PORTGTE_CPTR(r0);                                \
        Psyz_GteDataWrite(9, PortGte_Load32(port_p_));                         \
        Psyz_GteDataWrite(10, PortGte_Load32((const char*)port_p_ + 4));       \
        Psyz_GteDataWrite(11, PortGte_Load32((const char*)port_p_ + 8));       \
    } while (0)
/// IR1..3 = the first three bytes at `r0`, zero-extended (colour vector).
#define gte_ldcv(r0)                                                           \
    do {                                                                       \
        const uint8_t* port_p_ = (const uint8_t*)PORTGTE_CPTR(r0);             \
        Psyz_GteDataWrite(9, port_p_[0]);                                      \
        Psyz_GteDataWrite(10, port_p_[1]);                                     \
        Psyz_GteDataWrite(11, port_p_[2]);                                     \
    } while (0)
/// SXY0..2 = three packed screen coordinates (values, not addresses).
#define gte_ldsxy3(r0, r1, r2)                                                 \
    do {                                                                       \
        Psyz_GteDataWrite(12, (unsigned int)(r0));                             \
        Psyz_GteDataWrite(13, (unsigned int)(r1));                             \
        Psyz_GteDataWrite(14, (unsigned int)(r2));                             \
    } while (0)
/// Push one packed screen coordinate into the SXY FIFO.
#define gte_ldSXYP(r0) PortGte_PushSxy((unsigned int)(r0))
/// Single SZ FIFO entries.
#define gte_ldSZ0(r0) Psyz_GteDataWrite(16, (unsigned int)(r0))
#define gte_ldSZ1(r0) Psyz_GteDataWrite(17, (unsigned int)(r0))
#define gte_ldSZ2(r0) Psyz_GteDataWrite(18, (unsigned int)(r0))
#define gte_ldSZ3(r0) Psyz_GteDataWrite(19, (unsigned int)(r0))
/// Back colour (BK) control registers 13..15, raw values (no scaling).
#define gte_ldbkdir(r0, r1, r2)                                                \
    do {                                                                       \
        Psyz_GteCtrlWrite(13, (unsigned int)(r0));                             \
        Psyz_GteCtrlWrite(14, (unsigned int)(r1));                             \
        Psyz_GteCtrlWrite(15, (unsigned int)(r2));                             \
    } while (0)
/// Rotation matrix control regs 0,1 = the 8 bytes at `r0` (an SVECTOR: x, y,
/// z, pad), so R11,R12,R13 = x,y,z and R21 = pad, as the original did.
#define gte_ldsvrtrow0(r0)                                                     \
    do {                                                                       \
        const void* port_p_ = PORTGTE_CPTR(r0);                                \
        Psyz_GteCtrlWrite(0, PortGte_Load32(port_p_));                         \
        Psyz_GteCtrlWrite(1, PortGte_Load32((const char*)port_p_ + 4));        \
    } while (0)
/// Outer product operand 1 from an SVECTOR: the signed halfwords go,
/// sign-extended to 32 bits, into control regs 0, 2, 4 (R11, R22, R33 are the
/// low halves; the high halves spill into R12, R23 as on hardware).
#define gte_ldopv1SV(r0)                                                       \
    do {                                                                       \
        const void* port_p_ = PORTGTE_CPTR(r0);                                \
        Psyz_GteCtrlWrite(0, PortGte_LoadS16(port_p_));                        \
        Psyz_GteCtrlWrite(2, PortGte_LoadS16((const char*)port_p_ + 2));       \
        Psyz_GteCtrlWrite(4, PortGte_LoadS16((const char*)port_p_ + 4));       \
    } while (0)
/// Outer product operand 2 from an SVECTOR: IR1..3 (sign-extended halfwords).
#define gte_ldopv2SV(r0) PortGte_LdIrFromS16(PORTGTE_CPTR(r0))

/* ------------------------------------------------------------------------ */
/* Stores                                                                   */
/* ------------------------------------------------------------------------ */

/// Three halfwords = low 16 bits of IR1..3.
#define gte_stsv(r0) PortGte_StIrToS16(PORTGTE_PTR(r0))
/// Three bytes = low 8 bits of IR1..3.
#define gte_stcv(r0)                                                           \
    do {                                                                       \
        void* port_p_ = PORTGTE_PTR(r0);                                       \
        PortGte_Store8((char*)port_p_ + 0, Psyz_GteDataRead(9));               \
        PortGte_Store8((char*)port_p_ + 1, Psyz_GteDataRead(10));              \
        PortGte_Store8((char*)port_p_ + 2, Psyz_GteDataRead(11));              \
    } while (0)
/// IR0 as a 32-bit word.
#define gte_stdp(r0) PortGte_Store32(PORTGTE_PTR(r0), Psyz_GteDataRead(8))
/// MAC1 as a 32-bit word.
#define gte_stlvnl0(r0) PortGte_Store32(PORTGTE_PTR(r0), Psyz_GteDataRead(25))
/// Translation vector TR (control regs 5..7) as three 32-bit words.
#define gte_sttr(r0)                                                           \
    do {                                                                       \
        void* port_p_ = PORTGTE_PTR(r0);                                       \
        PortGte_Store32((char*)port_p_ + 0, Psyz_GteCtrlRead(5));              \
        PortGte_Store32((char*)port_p_ + 4, Psyz_GteCtrlRead(6));              \
        PortGte_Store32((char*)port_p_ + 8, Psyz_GteCtrlRead(7));              \
    } while (0)
/// Whole current rotation matrix and translation into a MATRIX.
#define gte_ReadRotMatrix(r0) PortGte_ReadRotMatrix((MATRIX*)PORTGTE_PTR(r0))

/// Screen XY stores. Go through PsyZ's store helper so PGXP sub-pixel
/// metadata follows the value into the polygon.
#define gte_stsxy2(r0) Psyz_GteStoreSxyTo(14, PORTGTE_PTR(r0))
#define PORTGTE_STSXY3_AT(r0, o0, o1, o2)                                      \
    do {                                                                       \
        char* port_p_ = (char*)PORTGTE_PTR(r0);                                \
        Psyz_GteStoreSxyTo(12, port_p_ + (o0));                                \
        Psyz_GteStoreSxyTo(13, port_p_ + (o1));                                \
        Psyz_GteStoreSxyTo(14, port_p_ + (o2));                                \
    } while (0)
/* Packet headers grow on the host; disk offsets would overwrite tag/length. */
#define gte_stsxy3_f3(r0) PORTGTE_STSXY3_AT(r0, offsetof(POLY_F3, x0), offsetof(POLY_F3, x1), offsetof(POLY_F3, x2))
#define gte_stsxy3_ft3(r0) PORTGTE_STSXY3_AT(r0, offsetof(POLY_FT3, x0), offsetof(POLY_FT3, x1), offsetof(POLY_FT3, x2))
#define gte_stsxy3_f4(r0) PORTGTE_STSXY3_AT(r0, offsetof(POLY_F4, x0), offsetof(POLY_F4, x1), offsetof(POLY_F4, x2))
#define gte_stsxy3_g4(r0) PORTGTE_STSXY3_AT(r0, offsetof(POLY_G4, x0), offsetof(POLY_G4, x1), offsetof(POLY_G4, x2))
#define gte_stsxy3_ft4(r0) PORTGTE_STSXY3_AT(r0, offsetof(POLY_FT4, x0), offsetof(POLY_FT4, x1), offsetof(POLY_FT4, x2))
#define gte_stsxy3_gt4(r0) PORTGTE_STSXY3_AT(r0, offsetof(POLY_GT4, x0), offsetof(POLY_GT4, x1), offsetof(POLY_GT4, x2))

/* ------------------------------------------------------------------------ */
/* Commands                                                                 */
/* ------------------------------------------------------------------------ */

/// MVMVA forms (see gte_macros.inc). rt = rotation matrix, v0 = vector V0,
/// ir = IR vector, tr = add translation. `sf0` = no 12-bit shift.
#define gte_rtv0tr() Psyz_GteCommand(0x4A480012)
#define gte_rtirtr() Psyz_GteCommand(0x4A498012)
#define gte_rtv0_sf0() Psyz_GteCommand(0x4A406012)
#define gte_rtir_sf0() Psyz_GteCommand(0x4A41E012)
/// IR1..3 squared, unshifted, clamped.
#define gte_sqr0() Psyz_GteCommand(0x4AA00428)
/// Normal colour colour triple (V0..V2).
#define gte_ncct() Psyz_GteCommand(0x4B18043F)
/// General purpose interpolation: MAC = IR0 * IR (gpf) or MAC + IR0 * IR (gpl).
#define gte_gpf12() Psyz_GteCommand(0x4B98003D)
#define gte_gpl12() Psyz_GteCommand(0x4BA8003E)

/* ------------------------------------------------------------------------ */
/* Compound macros                                                          */
/* ------------------------------------------------------------------------ */

#define gte_RotTransPers(r1, r2, r3, r4, r5)                                   \
    do {                                                                       \
        gte_ldv0(r1);                                                          \
        gte_rtps();                                                            \
        gte_stsxy(r2);                                                         \
        gte_stdp(r3);                                                          \
        gte_stflg(r4);                                                         \
        gte_stszotz(r5);                                                       \
    } while (0)

#define gte_RotTrans(r1, r2, r3)                                               \
    do {                                                                       \
        gte_ldv0(r1);                                                          \
        gte_rt();                                                              \
        gte_stlvnl(r2);                                                        \
        gte_stflg(r3);                                                         \
    } while (0)

#define gte_Lzc(r1, r2)                                                        \
    do {                                                                       \
        Psyz_GteDataWrite(30, (unsigned int)(r1));                             \
        PortGte_Store32(PORTGTE_PTR(r2), Psyz_GteDataRead(31));                \
    } while (0)

#define gte_LoadAverageShort12(r1, r2, r3, r4, r5)                             \
    do {                                                                       \
        gte_lddp(r3);                                                          \
        gte_ldsv(r1);                                                          \
        gte_gpf12();                                                           \
        gte_lddp(r4);                                                          \
        gte_ldsv(r2);                                                          \
        gte_gpl12();                                                           \
        gte_stsv(r5);                                                          \
    } while (0)

#define gte_MulMatrix0(r1, r2, r3)                                             \
    do {                                                                       \
        gte_SetRotMatrix(r1);                                                  \
        gte_ldclmv(PORTGTE_BYTES(r2, 0));                                      \
        gte_rtir();                                                            \
        gte_stclmv(PORTGTE_BYTES(r3, 0));                                      \
        gte_ldclmv(PORTGTE_BYTES(r2, 2));                                      \
        gte_rtir();                                                            \
        gte_stclmv(PORTGTE_BYTES(r3, 2));                                      \
        gte_ldclmv(PORTGTE_BYTES(r2, 4));                                      \
        gte_rtir();                                                            \
        gte_stclmv(PORTGTE_BYTES(r3, 4));                                      \
    } while (0)

#define gte_ApplyMatrix(r1, r2, r3)                                            \
    do {                                                                       \
        gte_SetRotMatrix(r1);                                                  \
        gte_ldv0(r2);                                                          \
        gte_rtv0();                                                            \
        gte_stlvnl(r3);                                                        \
    } while (0)

#define gte_ApplyMatrixSV(r1, r2, r3)                                          \
    do {                                                                       \
        gte_SetRotMatrix(r1);                                                  \
        gte_ldv0(r2);                                                          \
        gte_rtv0();                                                            \
        gte_stsv(r3);                                                          \
    } while (0)

#define gte_CompMatrix(r1, r2, r3)                                             \
    do {                                                                       \
        gte_MulMatrix0(r1, r2, r3);                                            \
        gte_SetTransMatrix(r1);                                                \
        gte_ldlv0(PORTGTE_BYTES(r2, 20));                                      \
        gte_rt();                                                              \
        gte_stlvnl(PORTGTE_BYTES(r3, 20));                                     \
    } while (0)

/* ------------------------------------------------------------------------ */
/* Game-specific helpers (not in Psy-Q)                                     */
/* ------------------------------------------------------------------------ */

/// Writes the transpose of `src`'s 3x3 into `dst`; translation untouched.
/// Reads all nine entries before writing, so `src == dst` is safe.
#define gte_TransposeMatrix(src, dst)                                          \
    PortGte_TransposeMatrix(PORTGTE_CPTR(src), PORTGTE_PTR(dst))

/// v->{vx,vy,vz} = m->m[0..2][col]
#define gte_ReadMatrixColumn(m, col, v)                                        \
    do {                                                                       \
        const char* port_m_ = (const char*)PORTGTE_CPTR(m);                    \
        char* port_v_ = (char*)PORTGTE_PTR(v);                                 \
        int port_c_ = (int)(col);                                              \
        uint16_t port_a_, port_b_, port_d_;                                    \
        memcpy(&port_a_, port_m_ + 2 * port_c_, 2);                            \
        memcpy(&port_b_, port_m_ + 6 + 2 * port_c_, 2);                        \
        memcpy(&port_d_, port_m_ + 12 + 2 * port_c_, 2);                       \
        memcpy(port_v_ + 0, &port_a_, 2);                                      \
        memcpy(port_v_ + 2, &port_b_, 2);                                      \
        memcpy(port_v_ + 4, &port_d_, 2);                                      \
    } while (0)

/// m->m[0..2][col] = v->{vx,vy,vz}
#define gte_WriteMatrixColumn(v, m, col)                                       \
    do {                                                                       \
        const char* port_v_ = (const char*)PORTGTE_CPTR(v);                    \
        char* port_m_ = (char*)PORTGTE_PTR(m);                                 \
        int port_c_ = (int)(col);                                              \
        uint16_t port_a_, port_b_, port_d_;                                    \
        memcpy(&port_a_, port_v_ + 0, 2);                                      \
        memcpy(&port_b_, port_v_ + 2, 2);                                      \
        memcpy(&port_d_, port_v_ + 4, 2);                                      \
        memcpy(port_m_ + 2 * port_c_, &port_a_, 2);                            \
        memcpy(port_m_ + 6 + 2 * port_c_, &port_b_, 2);                        \
        memcpy(port_m_ + 12 + 2 * port_c_, &port_d_, 2);                       \
    } while (0)

/// Rotates a signed 32-bit vector (3 x s32 at `in`) and adds TR; result to
/// `out` (3 x s32). May overlap. Clobbers V0..V2, MAC, IR, FLAG.
#define gte_RotTransLV(in, out)                                                \
    PortGte_RotTransLV(PORTGTE_CPTR(in), PORTGTE_PTR(out))

/* ------------------------------------------------------------------------ */
/* libgte functions that exist in libpsyz.a but are not declared            */
/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif
void MatrixNormal_0(MATRIX* m, MATRIX* n);
void MatrixNormal_1(MATRIX* m, MATRIX* n);
void MatrixNormal_2(MATRIX* m, MATRIX* n);
/* NOTE: libpsyz.a currently has no definition of the plain MatrixNormal (it is
 * an unported INCLUDE_ASM in psyz's decomp); declared so callers compile. */
void MatrixNormal(MATRIX* m, MATRIX* n);
#ifdef __cplusplus
}
#endif

#endif /* __psyz */

#endif /* PORT_GTE_COMPAT_H */
