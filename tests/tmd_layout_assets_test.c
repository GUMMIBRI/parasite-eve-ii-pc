/* Exercise the same generated model data the game consumes, so the test also
 * catches stream-family/offset assumptions absent from synthetic fixtures. */
#include "port/tmd_layout.h"
#include <libgpu.h>
#include <stdio.h>
#include "assets/weapons/m93r/model.inc"
static u32 ayaStream[] = {
#include "assets/aya_10400_model_01A48_stream.inc"
};
int main(void)
{
    TmdSource aya = { .stream = ayaStream, .bufferHalfBytes = 22360, .preXformRegionBytes = 5800 };
    if (peTmdPreparePacketLayout(&gM93rWeaponModel) != 0 ||
        gM93rWeaponModel.bufferHalfBytes != 4 * sizeof(POLY_GT3) + 28 * sizeof(POLY_GT4) ||
        gM93rWeaponModel.preXformRegionBytes != 0) return 1;
    if (peTmdPreparePacketLayout(&aya) != 0 ||
        aya.bufferHalfBytes != 260 * sizeof(POLY_GT3) + 230 * sizeof(POLY_GT4) ||
        aya.preXformRegionBytes != 80 * sizeof(POLY_GT3) + 50 * sizeof(POLY_GT4)) return 1;
    printf("real model layouts OK: M93R=%d Aya=%d pre=%d\n", gM93rWeaponModel.bufferHalfBytes,
           aya.bufferHalfBytes, aya.preXformRegionBytes);
    return 0;
}
