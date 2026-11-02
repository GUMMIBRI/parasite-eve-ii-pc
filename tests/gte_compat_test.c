/* Host test for include/port/gte_compat.h. Plain C, exits nonzero on failure.
 *
 * Build and run:
 *   cmake --build build-port --target gte_compat_test && build-port/gte_compat_test
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "decomp/types.h"
#include "decomp/gte.h"
#include "main/gfx.h"

static int g_fail;
#define CHECK(cond)                                                            \
    do {                                                                       \
        if (!(cond)) {                                                         \
            printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond);             \
            g_fail++;                                                          \
        }                                                                      \
    } while (0)
#define CHECK_EQ(a, b)                                                         \
    do {                                                                       \
        long long a_ = (long long)(a), b_ = (long long)(b);                    \
        if (a_ != b_) {                                                        \
            printf("FAIL %s:%d: %s == %s (%lld vs %lld)\n", __FILE__,          \
                   __LINE__, #a, #b, a_, b_);                                  \
            g_fail++;                                                          \
        }                                                                      \
    } while (0)
#define CHECK_NEAR(a, b, tol)                                                  \
    do {                                                                       \
        long long a_ = (long long)(a), b_ = (long long)(b);                    \
        if (a_ - b_ > (tol) || b_ - a_ > (tol)) {                              \
            printf("FAIL %s:%d: %s ~= %s (%lld vs %lld)\n", __FILE__,          \
                   __LINE__, #a, #b, a_, b_);                                  \
            g_fail++;                                                          \
        }                                                                      \
    } while (0)

static MATRIX make_matrix(const short m[3][3], int tx, int ty, int tz) {
    MATRIX r;
    memset(&r, 0, sizeof(r));
    memcpy(r.m, m, sizeof(r.m));
    r.t[0] = tx;
    r.t[1] = ty;
    r.t[2] = tz;
    return r;
}

static void test_ldsv_stsv(void) {
    SVECTOR in = {-1234, 32767, -32768, 0};
    short out[3] = {0};
    gte_ldsv(&in);
    CHECK_EQ((short)Psyz_GteDataRead(9), -1234);
    CHECK_EQ((short)Psyz_GteDataRead(10), 32767);
    CHECK_EQ((short)Psyz_GteDataRead(11), -32768);
    gte_stsv(out);
    CHECK_EQ(out[0], -1234);
    CHECK_EQ(out[1], 32767);
    CHECK_EQ(out[2], -32768);
    /* unaligned source and destination */
    unsigned char buf[16] = {0}, dst[16] = {0};
    memcpy(buf + 1, &in, 6);
    gte_ldsv(buf + 1);
    gte_stsv(dst + 3);
    CHECK(memcmp(dst + 3, &in, 6) == 0);
}

static void test_ldlvl_ldcv_stcv(void) {
    int lv[3] = {100, -200, 300};
    unsigned char cv[3] = {1, 200, 255}, out[3] = {0};
    gte_ldlvl(lv);
    CHECK_EQ((short)Psyz_GteDataRead(9), 100);
    CHECK_EQ((short)Psyz_GteDataRead(10), -200);
    CHECK_EQ((short)Psyz_GteDataRead(11), 300);
    gte_ldcv(cv);
    CHECK_EQ((short)Psyz_GteDataRead(9), 1);
    CHECK_EQ((short)Psyz_GteDataRead(10), 200);
    CHECK_EQ((short)Psyz_GteDataRead(11), 255);
    gte_stcv(out);
    CHECK(memcmp(out, cv, 3) == 0);
}

static void test_transpose(void) {
    short a[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    MATRIX s = make_matrix(a, 11, 22, 33), d;
    memset(&d, 0x55, sizeof(d));
    gte_TransposeMatrix(&s, &d);
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            CHECK_EQ(d.m[r][c], s.m[c][r]);
    CHECK_EQ(((unsigned char*)&d)[18], 0x55); /* padding untouched */
    CHECK_EQ(d.t[0], 0x55555555);              /* translation untouched */
    gte_TransposeMatrix(&s, &s); /* in place */
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            CHECK_EQ(s.m[r][c], d.m[r][c]);
}

static void test_matrix_columns(void) {
    short a[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    MATRIX m = make_matrix(a, 0, 0, 0);
    SVECTOR v = {0, 0, 0, 77};
    for (int c = 0; c < 3; c++) {
        gte_ReadMatrixColumn(&m, c, &v);
        CHECK_EQ(v.vx, a[0][c]);
        CHECK_EQ(v.vy, a[1][c]);
        CHECK_EQ(v.vz, a[2][c]);
        CHECK_EQ(v.pad, 77);
    }
    SVECTOR w = {-10, -20, -30, 0};
    gte_WriteMatrixColumn(&w, &m, 1);
    CHECK_EQ(m.m[0][1], -10);
    CHECK_EQ(m.m[1][1], -20);
    CHECK_EQ(m.m[2][1], -30);
    CHECK_EQ(m.m[0][0], 1);
    CHECK_EQ(m.m[2][2], 9);
}

static void test_mulmatrix0(void) {
    short a[3][3] = {{4096, 0, 0}, {0, 2048, 100}, {-300, 4000, 1000}};
    short b[3][3] = {{1000, -2000, 3000}, {4000, 5000, -6000}, {7000, 800, 90}};
    MATRIX ma = make_matrix(a, 1, 2, 3), mb = make_matrix(b, 4, 5, 6), mc;
    memset(&mc, 0, sizeof(mc));
    gte_MulMatrix0(&ma, &mb, &mc);
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            long sum = 0;
            for (int k = 0; k < 3; k++)
                sum += (long)a[r][k] * b[k][c];
            CHECK_EQ(mc.m[r][c], (short)(sum >> 12));
        }
    }
    /* Psy-Q leaves RT = first operand. */
    MATRIX rot;
    gte_ReadRotMatrix(&rot);
    CHECK(memcmp(rot.m, ma.m, sizeof(rot.m)) == 0);
}

static void test_apply_rot_trans(void) {
    short rz[3][3] = {{0, -4096, 0}, {4096, 0, 0}, {0, 0, 4096}}; /* 90deg Z */
    MATRIX m = make_matrix(rz, 10, 20, 30);
    SVECTOR v = {100, 200, 300, 0}, sv = {0};
    VECTOR out = {0};
    int flag = -1;

    gte_ApplyMatrix(&m, &v, &out);
    CHECK_EQ(out.vx, -200);
    CHECK_EQ(out.vy, 100);
    CHECK_EQ(out.vz, 300);

    gte_ApplyMatrixSV(&m, &v, &sv);
    CHECK_EQ(sv.vx, -200);
    CHECK_EQ(sv.vy, 100);
    CHECK_EQ(sv.vz, 300);

    gte_SetRotMatrix(&m);
    gte_SetTransMatrix(&m);
    gte_RotTrans(&v, &out, &flag);
    CHECK_EQ(out.vx, -200 + 10);
    CHECK_EQ(out.vy, 100 + 20);
    CHECK_EQ(out.vz, 300 + 30);
    CHECK_EQ(flag, 0);

    int tr[3];
    gte_sttr(tr);
    CHECK_EQ(tr[0], 10);
    CHECK_EQ(tr[1], 20);
    CHECK_EQ(tr[2], 30);
    MATRIX rd;
    memset(&rd, 0, sizeof(rd));
    gte_ReadRotMatrix(&rd);
    CHECK(memcmp(rd.m, m.m, sizeof(rd.m)) == 0);
    CHECK_EQ(rd.t[0], 10);
    CHECK_EQ(rd.t[2], 30);

    /* rtv0tr / rtirtr / rtv0_sf0 / rtir_sf0 */
    gte_ldv0(&v);
    gte_rtv0tr();
    gte_stlvnl(&out);
    CHECK_EQ(out.vx, -190);
    CHECK_EQ(out.vy, 120);
    CHECK_EQ(out.vz, 330);
    gte_rtirtr(); /* IR now holds the previous result */
    gte_stlvnl(&out);
    CHECK_EQ(out.vx, -120 + 10); /* RT * (-190,120,330) = (-120, -190, 330) */
    CHECK_EQ(out.vy, -190 + 20);
    CHECK_EQ(out.vz, 330 + 30);
    gte_ldv0(&v);
    gte_rtv0_sf0();
    gte_stlvnl0(&flag);
    CHECK_EQ(flag, -200 * 4096);
    short ir[3] = {1, 2, 3};
    gte_ldsv(ir);
    gte_rtir_sf0();
    gte_stlvnl(&out);
    CHECK_EQ(out.vx, -2 * 4096);
    CHECK_EQ(out.vy, 1 * 4096);
    CHECK_EQ(out.vz, 3 * 4096);
}

static void test_comp_matrix(void) {
    short a[3][3] = {{0, -4096, 0}, {4096, 0, 0}, {0, 0, 4096}};
    short b[3][3] = {{4096, 0, 0}, {0, 4096, 0}, {0, 0, 4096}};
    MATRIX ma = make_matrix(a, 100, 200, 300);
    MATRIX mb = make_matrix(b, 1, 2, 3), mc;
    memset(&mc, 0, sizeof(mc));
    gte_CompMatrix(&ma, &mb, &mc);
    CHECK(memcmp(mc.m, ma.m, sizeof(mc.m)) == 0);
    /* t = ma.t + ma.R * mb.t = (100-2, 200+1, 300+3) */
    CHECK_EQ(mc.t[0], 98);
    CHECK_EQ(mc.t[1], 201);
    CHECK_EQ(mc.t[2], 303);
}

static void test_rottranspers(void) {
    short id[3][3] = {{4096, 0, 0}, {0, 4096, 0}, {0, 0, 4096}};
    MATRIX m = make_matrix(id, 0, 0, 0);
    gte_SetRotMatrix(&m);
    gte_SetTransMatrix(&m);
    gte_SetGeomOffset(160, 120);
    gte_SetGeomScreen(500);
    Psyz_GteCtrlWrite(27, 0); /* DQA */
    Psyz_GteCtrlWrite(28, 0); /* DQB */

    SVECTOR v = {100, -50, 1000, 0};
    int sxy = 0, p = -1, flag = -1, otz = 0;
    gte_RotTransPers(&v, &sxy, &p, &flag, &otz);
    /* sx = 160 + 100*500/1000, sy = 120 - 50*500/1000 (UNR divide: +-1) */
    CHECK_NEAR((short)(sxy & 0xFFFF), 160 + 50, 1);
    CHECK_NEAR((short)(sxy >> 16), 120 - 25, 1);
    CHECK_EQ(p, 0);
    CHECK_EQ(flag, 0);
    CHECK_EQ(otz, 1000 >> 2);
    CHECK_EQ(Psyz_GteDataRead(19), 1000); /* SZ3 */

    /* a rotated point with translation, behind nothing: 2D shift */
    short r90[3][3] = {{0, -4096, 0}, {4096, 0, 0}, {0, 0, 4096}};
    MATRIX m2 = make_matrix(r90, 0, 0, 500);
    gte_SetRotMatrix(&m2);
    gte_SetTransMatrix(&m2);
    SVECTOR v2 = {100, 0, 500, 0}; /* -> (0, 100, 1000) */
    gte_RotTransPers(&v2, &sxy, &p, &flag, &otz);
    CHECK_NEAR((short)(sxy & 0xFFFF), 160, 1);
    CHECK_NEAR((short)(sxy >> 16), 120 + 50, 1);
    CHECK_EQ(otz, 250);
}

static void test_sxy_stores(void) {
    gte_ldsxy3(0x00020001u, 0x00040003u, 0x00060005u);
    unsigned char buf[48];
    unsigned int w;
    memset(buf, 0, sizeof(buf));
    gte_stsxy3_gt4(buf);
    memcpy(&w, buf + 8, 4);  CHECK_EQ(w, 0x00020001u);
    memcpy(&w, buf + 20, 4); CHECK_EQ(w, 0x00040003u);
    memcpy(&w, buf + 32, 4); CHECK_EQ(w, 0x00060005u);
    memset(buf, 0, sizeof(buf));
    gte_stsxy3_f3(buf);
    memcpy(&w, buf + 8, 4);  CHECK_EQ(w, 0x00020001u);
    memcpy(&w, buf + 12, 4); CHECK_EQ(w, 0x00040003u);
    memcpy(&w, buf + 16, 4); CHECK_EQ(w, 0x00060005u);
    memset(buf, 0, sizeof(buf));
    gte_stsxy3_ft4(buf);
    memcpy(&w, buf + 16, 4); CHECK_EQ(w, 0x00040003u);
    memcpy(&w, buf + 24, 4); CHECK_EQ(w, 0x00060005u);
    memset(buf, 0, sizeof(buf));
    gte_stsxy3_g4(buf);
    memcpy(&w, buf + 24, 4); CHECK_EQ(w, 0x00060005u);
    gte_stsxy3_ft3(buf);
    gte_stsxy3_f4(buf);

    /* ldSXYP pushes: SXY0<-SXY1<-SXY2<-new */
    gte_ldSXYP(0x00080007u);
    gte_stsxy2(&w);
    CHECK_EQ(w, 0x00080007u);
    gte_stsxy01c(buf);
    memcpy(&w, buf, 4);     CHECK_EQ(w, 0x00040003u);
    memcpy(&w, buf + 4, 4); CHECK_EQ(w, 0x00060005u);
    gte_stsxy(&w);
    CHECK_EQ(w, 0x00080007u);

    /* nclip on a known triangle: (0,0) (10,0) (0,10) */
    gte_ldsxy3(0u, 10u, 10u << 16);
    gte_nclip();
    int opz;
    gte_stopz(&opz);
    CHECK_EQ(opz, 100);
}

static void test_ldsz(void) {
    gte_ldSZ0(10);
    gte_ldSZ1(20);
    gte_ldSZ2(30);
    gte_ldSZ3(40);
    unsigned int z[4];
    gte_stsz4(&z[0], &z[1], &z[2], &z[3]);
    CHECK_EQ(z[0], 10);
    CHECK_EQ(z[1], 20);
    CHECK_EQ(z[2], 30);
    CHECK_EQ(z[3], 40);
}

static void test_gpf_gpl(void) {
    short ir[3] = {1000, -2000, 3000}, out[3];
    gte_lddp(2048); /* IR0 = 0.5 */
    gte_ldsv(ir);
    gte_gpf12();
    gte_stsv(out);
    CHECK_EQ(out[0], 500);
    CHECK_EQ(out[1], -1000);
    CHECK_EQ(out[2], 1500);
    short ir2[3] = {4096, 4096, -4096};
    gte_lddp(1024); /* IR0 = 0.25 */
    gte_ldsv(ir2);
    gte_gpl12();
    gte_stsv(out);
    CHECK_EQ(out[0], 500 + 1024);
    CHECK_EQ(out[1], -1000 + 1024);
    CHECK_EQ(out[2], 1500 - 1024);

    short a[3] = {4096, -4096, 8192}, b[3] = {0, 4096, 0};
    gte_LoadAverageShort12(a, b, 3072, 1024, out);
    CHECK_EQ(out[0], 3072);
    CHECK_EQ(out[1], -3072 + 1024);
    CHECK_EQ(out[2], 6144);
}

static void test_sqr0(void) {
    short ir[3] = {3, -4, 100}, out[3];
    int m1;
    gte_ldsv(ir);
    gte_sqr0();
    gte_stsv(out);
    gte_stlvnl0(&m1);
    CHECK_EQ(out[0], 9);
    CHECK_EQ(out[1], 16);
    CHECK_EQ(out[2], 10000);
    CHECK_EQ(m1, 9);
    short big[3] = {200, 0, 0};
    gte_ldsv(big);
    gte_sqr0();
    gte_stsv(out);
    gte_stlvnl0(&m1);
    CHECK_EQ(out[0], 32767); /* saturated IR, MAC keeps 40000 */
    CHECK_EQ(m1, 40000);
}

static void test_lzc(void) {
    int r;
    gte_Lzc(0, &r);          CHECK_EQ(r, 32);
    gte_Lzc(1, &r);          CHECK_EQ(r, 31);
    gte_Lzc(0x00010000, &r); CHECK_EQ(r, 15);
    gte_Lzc(0x7fffffff, &r); CHECK_EQ(r, 1);
    gte_Lzc(-1, &r);         CHECK_EQ(r, 32);
    gte_Lzc(-2, &r);         CHECK_EQ(r, 31);
    gte_Lzc((int)0x80000000, &r); CHECK_EQ(r, 1);
}

static void test_dot_and_cross(void) {
    /* gfxDotProduct pattern: row0 from SVECTOR, then rtv0_sf0 */
    SVECTOR a = {2, 3, 4, 0}, b = {10, 20, 30, 0};
    int dot;
    gte_ldsvrtrow0(&a);
    gte_ldv0(&b);
    gte_rtv0_sf0();
    gte_stlvnl0(&dot);
    CHECK_EQ(dot, 2 * 10 + 3 * 20 + 4 * 30);

    /* outer product via SV loaders: (1,0,0) x (0,1,0) = (0,0,1) at sf=12 */
    SVECTOR x = {4096, 0, 0, 0}, y = {0, 4096, 0, 0}, z = {0};
    gte_ldopv1SV(&x);
    gte_ldopv2SV(&y);
    gte_op12();
    gte_stsv(&z);
    CHECK_EQ(z.vx, 0);
    CHECK_EQ(z.vy, 0);
    CHECK_EQ(z.vz, 4096);
}

static void test_rottranslv(void) {
    short id[3][3] = {{4096, 0, 0}, {0, 4096, 0}, {0, 0, 4096}};
    MATRIX m = make_matrix(id, 5, 6, 7);
    gte_SetRotMatrix(&m);
    gte_SetTransMatrix(&m);
    int in[3] = {100000, -50000, 12345}, out[3];
    gte_RotTransLV(in, out);
    CHECK_EQ(out[0], 100000 + 5);
    CHECK_EQ(out[1], -50000 + 6);
    CHECK_EQ(out[2], 12345 + 7);
    int in2[3] = {-1, 0x12345678, -0x10000000};
    gte_RotTransLV(in2, in2); /* overlap */
    CHECK_EQ(in2[0], -1 + 5);
    CHECK_EQ(in2[1], 0x12345678 + 6);
    CHECK_EQ(in2[2], -0x10000000 + 7);
    /* scaled by 0.5 */
    short half[3][3] = {{2048, 0, 0}, {0, 2048, 0}, {0, 0, 2048}};
    MATRIX mh = make_matrix(half, 0, 0, 0);
    gte_SetRotMatrix(&mh);
    gte_SetTransMatrix(&mh);
    int in3[3] = {2000000, -2000000, 4};
    gte_RotTransLV(in3, out);
    CHECK_EQ(out[0], 1000000);
    CHECK_EQ(out[1], -1000000);
    CHECK_EQ(out[2], 2);
}

static void test_ncct(void) {
    short l[3][3] = {{3000, 1000, 0}, {0, 3000, 500}, {500, 0, 3000}};
    short c[3][3] = {{4096, 0, 0}, {0, 3000, 0}, {0, 0, 2000}};
    MATRIX ml = make_matrix(l, 0, 0, 0), mc = make_matrix(c, 0, 0, 0);
    gte_SetLightMatrix(&ml);
    gte_SetColorMatrix(&mc);
    gte_SetBackColor(20, 30, 40);
    SVECTOR n = {0, 0, 4096, 0};
    CVECTOR col = {128, 128, 128, 0}, o0, o1, o2, s;
    gte_ldv3(&n, &n, &n);
    gte_ldrgb(&col);
    gte_ncct();
    gte_strgb3(&o0, &o1, &o2);
    gte_ldv0(&n);
    gte_ldrgb(&col);
    gte_nccs();
    gte_strgb(&s);
    CHECK(memcmp(&o0, &s, 3) == 0);
    CHECK(memcmp(&o1, &s, 3) == 0);
    CHECK(memcmp(&o2, &s, 3) == 0);
}

static void test_bkdir(void) {
    gte_ldbkdir(0x111, 0x222, 0x333);
    CHECK_EQ(Psyz_GteCtrlRead(13), 0x111);
    CHECK_EQ(Psyz_GteCtrlRead(14), 0x222);
    CHECK_EQ(Psyz_GteCtrlRead(15), 0x333);
}

static void test_matrixnormal2(void) {
    /* rows: 0 = X (given), 2 = Z (given), 1 rebuilt = Z x X; all normalised */
    short a[3][3] = {{4000, 0, 0}, {0, 0, 0}, {0, 0, 4000}};
    MATRIX m = make_matrix(a, 0, 0, 0), n;
    memset(&n, 0, sizeof(n));
    MatrixNormal_2(&m, &n);
    CHECK_NEAR(n.m[0][0], 4096, 8);
    CHECK_NEAR(n.m[2][2], 4096, 8);
    CHECK_NEAR(n.m[1][1], 4096, 8);
    CHECK_NEAR(n.m[0][1], 0, 2);
    CHECK_NEAR(n.m[1][0], 0, 2);
}

/* VECTOR3 is passed directly to GTE 32-bit XYZ loads/stores and aliases
 * MATRIX.t in target placement. Exercise both real interoperability paths. */
static void test_vector3_abi(void) {
    short id[3][3] = {{4096,0,0},{0,4096,0},{0,0,4096}};
    MATRIX m = make_matrix(id, 100, 200, 300);
    VECTOR3 input = {7230, -580, -6789};
    struct { VECTOR3 xyz; uint32_t guard[2]; } output;
    memset(&output, 0x55, sizeof output);
    gte_SetRotMatrix(&m); gte_SetTransMatrix(&m);
    gte_ldlvl(&input); gte_rtirtr(); gte_stlvl(&output.xyz);
    CHECK_EQ(output.xyz.vx, 7330);
    CHECK_EQ(output.xyz.vy, -380);
    CHECK_EQ(output.xyz.vz, -6489);
    CHECK_EQ(output.guard[0], 0x55555555);
    CHECK_EQ(output.guard[1], 0x55555555);
    struct { MATRIX matrix; uint32_t guard[4]; } placed;
    memset(&placed, 0x55, sizeof placed);
    VECTOR3* translation = GRAPHICS_MATRIX_TRANSLATION(&placed.matrix);
    translation->vx = -6800; translation->vy = -1258; translation->vz = 2796;
    CHECK_EQ(placed.matrix.t[0], -6800);
    CHECK_EQ(placed.matrix.t[1], -1258);
    CHECK_EQ(placed.matrix.t[2], 2796);
    for (int i=0; i<4; ++i) CHECK_EQ(placed.guard[i], 0x55555555);
}

int main(void) {
    test_vector3_abi();
    test_ldsv_stsv();
    test_ldlvl_ldcv_stcv();
    test_transpose();
    test_matrix_columns();
    test_mulmatrix0();
    test_apply_rot_trans();
    test_comp_matrix();
    test_rottranspers();
    test_sxy_stores();
    test_ldsz();
    test_gpf_gpl();
    test_sqr0();
    test_lzc();
    test_dot_and_cross();
    test_rottranslv();
    test_ncct();
    test_bkdir();
    test_matrixnormal2();
    if (g_fail) {
        printf("%d check(s) failed\n", g_fail);
        return 1;
    }
    printf("gte_compat_test: all checks passed\n");
    return 0;
}
