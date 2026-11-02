#include "gameplay/sprites.h"
#include "port/gpu_len.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
void Psyz_PadsOverride(int port, char* frame, int length) { (void)port; (void)frame; (void)length; }
int main(void)
{
    SpriteDrawModePacket packet;
    memset(&packet, 0xA5, sizeof packet);
    packet.sprite.packed.color = 0x00808080;
    setlen(&packet.drawMode, 1); packet.drawMode.code[0] = 0xE100023E;
    setSprt(&packet.sprite.sprt);
    CHECK(MargePrim(&packet.drawMode, &packet.sprite.sprt) == 0);
    unsigned length = getlen(&packet.drawMode);
    /* The game fills attributes after the merge, and cached packets are
     * copied/relinked. These stores must leave the native header/NOP intact. */
    packet.sprite.packed.position = 0xFFF00020;
    packet.sprite.packed.uv = 0x6850; packet.sprite.sprt.clut = 0x3C0B;
    packet.sprite.packed.size = 0x00080010;
    CHECK(packet.sprite.sprt.code == 0x64 && packet.sprite.sprt.x0 == 32 && packet.sprite.sprt.y0 == -16);
    CHECK(packet.sprite.sprt.u0 == 0x50 && packet.sprite.sprt.v0 == 0x68);
    CHECK(packet.sprite.sprt.w == 16 && packet.sprite.sprt.h == 8);
    SpriteDrawModePacket copy; memcpy(&copy, &packet, sizeof copy);
    const u32* commands = (const u32*)((const u8*)&copy + sizeof(OT_TYPE));
    unsigned spriteWord = (OFFSET_OF(SpriteDrawModePacket, sprite.sprt.r0) - sizeof(OT_TYPE)) / 4;
    CHECK(length == spriteWord + 4 && commands[0] == 0xE100023E);
    CHECK(commands[spriteWord] == 0x64808080 && commands[spriteWord + 1] == 0xFFF00020);
    CHECK(commands[spriteWord + 2] == 0x3C0B6850 && commands[spriteWord + 3] == 0x00080010);
    CHECK(commands[spriteWord - 1] == (sizeof(u_long) == 8 ? PSYZ_MERGED_PRIM_NOP : 0));
    /* The HP/MP caps reserve SPRT arena slots but emit only SPRT_8 words. */
    SPRT cap; memset(&cap, 0, sizeof cap);
    setlen((SPRT_8*)&cap, sizeof(SPRT_8) / sizeof(u32) - 1); setcode(&cap, 0x75);
    CHECK(getlen(&cap) == 3 && getcode(&cap) == 0x75);
    puts("native sprite packed views, merged/cached commands and fixed-size caps OK");
    return 0;
}
