/* Exercise the production CAP gradient through the real native GPU backend.
 * A poisoned unused DR_MODE word must not become another GP0 command. */
#include "port/gpu_len.h"
#include "../src/gameplay/captions.c"
#include <stdlib.h>
#include <string.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
DisplayState gDisplayState;
OT_TYPE* gGpuCurrentOt;
void* gGpuPrimCursor;
s16 gCapTextBlockLeftX;
s16 gCapTextBoxHeight;
void Psyz_PadsOverride(int p, char* f, int n) { (void)p; (void)f; (void)n; }
int main(void)
{
    ResetGraph(0);
    DRAWENV env;
    SetDefDrawEnv(&env, 0, 0, 320, 240);
    PutDrawEnv(&env);
    DrawSync(0);
    _Alignas(8) u16 pixels[16], readback[16];
    for (int i = 0; i < 16; ++i) pixels[i] = 0x1234 + i;
    RECT texture = {896, CAP_TEXT_BOX_BOTTOM_Y + 5, 16, 1};
    LoadImage(&texture, (u_long*)pixels);
    DrawSync(0);
    _Alignas(16) unsigned char arena[2 * sizeof(POLY_G4) + sizeof(DR_MODE)];
    memset(arena, 0, sizeof arena);
    /* Retained arena bytes observed in the native CAP failure. In a valid
     * gradient these colour padding bytes are ignored by the GPU. */
    ((POLY_G4*)arena)->pad2 = 2;
    DR_MODE* mode = (DR_MODE*)(arena + 2 * sizeof(POLY_G4));
    mode->code[1] = (u_long)0x73fe77ff7fff7fffULL;
    OT_TYPE ot[4];
    ClearOTagR(ot, 4);
    gGpuCurrentOt = ot;
    gGpuPrimCursor = arena;
    gCapTextBlockLeftX = 0;
    gCapTextBoxHeight = 16;
    _capDrawTextBackground();
    CHECK(gGpuPrimCursor == arena + sizeof arena);
    DrawOTag(&ot[3]);
    DrawSync(0);
    StoreImage(&texture, (u_long*)readback);
    DrawSync(0);
    CHECK(memcmp(pixels, readback, sizeof pixels) == 0);
    CHECK(getlen(mode) == 1 && mode->code[0] == 0xE100020A);
    setlen(mode, sizeof(*mode) / sizeof(u32) - 1);
    CHECK(getlen(mode) == 2);
    puts("CAP background: one-word draw mode, poisoned spare word and off-screen texture preserved OK");
    return 0;
}
