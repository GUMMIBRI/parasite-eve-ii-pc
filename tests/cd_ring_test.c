#include <libcd.h>
#include <psyz/cd.h>
#include "port/psyq_compat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
void Psyz_PadsOverride(int port, char* frame, int length) { (void)port; (void)frame; (void)length; }

/* Real CD producer and SDK consumer: four ten-sector frames fill the ring exactly. */
static void check_ring(int ring_sectors)
{
    enum { FRAME_SECTORS = 10, FRAMES = 12, PAYLOAD = 2016 };
    char dir[] = "/tmp/pe2_cd_ring_XXXXXX", cue[256], bin[256];
    CHECK(mkdtemp(dir));
    snprintf(cue, sizeof cue, "%s/test.cue", dir);
    snprintf(bin, sizeof bin, "%s/test.bin", dir);
    FILE* file = fopen(bin, "wb"); CHECK(file);
    for (int frame = 1; frame <= FRAMES; ++frame) {
        for (int part = 0; part < FRAME_SECTORS; ++part) {
            unsigned char sector[2352] = {0};
            StHEADER header = {0};
            CdlLOC pos;
            CdIntToPos((frame - 1) * FRAME_SECTORS + part, &pos);
            memcpy(sector + 12, &pos, 3);
            sector[15] = 2; sector[18] = sector[22] = 8;
            header.id = 0x160; header.type = 0x8001;
            header.secCount = part; header.nSectors = FRAME_SECTORS;
            header.frameCount = frame; header.frameSize = FRAME_SECTORS * PAYLOAD;
            header.width = 320; header.height = 192;
            memcpy(sector + 24, &header, 32);
            memset(sector + 56, frame, PAYLOAD);
            /* A zero payload prefix must never be mistaken for a free wrap header. */
            sector[56] = sector[57] = 0;
            CHECK(fwrite(sector, 1, sizeof sector, file) == sizeof sector);
        }
    }
    fclose(file); file = fopen(cue, "w"); CHECK(file);
    fputs("FILE \"test.bin\" BINARY\n  TRACK 01 MODE2/2352\n    INDEX 01 00:00:00\n", file);
    fclose(file);
    CHECK(Psyz_CdSetDiskPath(cue) == 0);
    CdInit();
    unsigned char* ring = calloc(ring_sectors, 2048); CHECK(ring);
    StSetRing((u_long*)ring, ring_sectors);
    StSetStream(1, 0, 1000, NULL, NULL);
    CdlLOC start; CdIntToPos(0, &start);
    CHECK(CdControlB(CdlSetloc, &start.minute, NULL));
    CHECK(CdRead2(CdlModeStream | CdlModeSpeed | CdlModeSize1));
    for (int frame = 1; frame <= FRAMES; ++frame) {
        for (int pump = 0; pump < 80; ++pump) Psyz_CdPump();
        u_long *data, *words;
        if (StGetNext(&data, &words) != 0) {
            fprintf(stderr, "STR frame %d unavailable after producer pump (ring %d)\n", frame, ring_sectors);
            extern s32 StRingIdx1, StRingIdx2, StRingIdx3, StEndFrame;
            extern StHEADER* StRingAddr;
            fprintf(stderr, "indices %d %d %d end %d\n", StRingIdx1, StRingIdx2, StRingIdx3, StEndFrame);
            for (int i = 0; i < ring_sectors; ++i) if (StRingAddr[i].id != 3)
                fprintf(stderr, "header %d id%d frame%u\n", i, StRingAddr[i].id, (unsigned)StRingAddr[i].frameCount);
            exit(1);
        }
        CHECK(((StHEADER*)words)->frameCount == (unsigned)frame);
        for (int byte = 0; byte < FRAME_SECTORS * PAYLOAD; ++byte)
            CHECK(((unsigned char*)data)[byte] == (byte % PAYLOAD < 2 ? 0 : frame));
        CHECK(StFreeRing(data) == 0);
    }
    StUnSetRing(); CdControlB(CdlStop, NULL, NULL);
    free(ring); unlink(cue); unlink(bin); rmdir(dir);
}

int main(void)
{
    check_ring(40);
    check_ring(41);
    check_ring(37);
    puts("STR ring: frame order and payload preserved through exact and partial wraps");
    return 0;
}
