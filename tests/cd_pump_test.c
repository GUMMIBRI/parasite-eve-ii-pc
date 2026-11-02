#include <libcd.h>
#include <psyz/cd.h>
#include "port/psyq_compat.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
void Psyz_PadsOverride(int port, char* frame, int length) { (void)port; (void)frame; (void)length; }
static int hold = 1, calls, sectors;
static void ready(u_char status, u_char* result)
{
    (void)result;
    CHECK(status == CdlDataReady);
    ++calls;
    if (hold) return; /* an STR ring with no space must retain sector 0 */
    unsigned char header[12], payload[2048];
    CHECK(CdGetSector(header, 3) != 0);
    CHECK(CdPosToInt((CdlLOC*)header) == sectors);
    if (sectors == 2) {
        CHECK(CdGetSector(payload, 15) != 0);
        CHECK(CdGetSector(payload + 60, 497) != 0);
        for (unsigned i = 0; i < sizeof payload; ++i) CHECK(payload[i] == (unsigned char)(i + 2));
        CHECK(CdGetSector(payload, 1) == 0); /* consumed sector cannot be replayed */
        CdControlF(CdlPause, NULL);
    } /* sectors 0 and 1 are deliberately skipped after their headers */
    ++sectors;
}
int main(void)
{
    char dir[] = "/tmp/pe2_cd_pump_XXXXXX";
    CHECK(mkdtemp(dir) != NULL);
    char cue[256], bin[256];
    snprintf(cue, sizeof cue, "%s/test.cue", dir);
    snprintf(bin, sizeof bin, "%s/test.bin", dir);
    FILE* file = fopen(bin, "wb"); CHECK(file != NULL);
    for (int i = 0; i < 4; ++i) {
        unsigned char data[2352] = {0}; CdlLOC pos;
        CdIntToPos(i, &pos); memcpy(data + 12, &pos, 3);
        data[15] = 2; data[18] = data[22] = 8;
        for (unsigned j = 0; j < 2048; ++j) data[24 + j] = (unsigned char)(j + i);
        CHECK(fwrite(data, 1, sizeof data, file) == sizeof data);
    }
    fclose(file); file = fopen(cue, "w"); CHECK(file != NULL);
    fputs("FILE \"test.bin\" BINARY\n  TRACK 01 MODE2/2352\n    INDEX 01 00:00:00\n", file); fclose(file);
    CHECK(Psyz_CdSetDiskPath(cue) == 0);
    CdInit();
    u_char mode = CdlModeSpeed | CdlModeSize1; CdlLOC pos;
    CdControlB(CdlSetmode, &mode, NULL); CdIntToPos(0, &pos);
    CdControlF(CdlReadN, &pos.minute); CdReadyCallback(ready);
    Psyz_CdPump(); CHECK(calls == 1 && sectors == 0);
    Psyz_CdPump(); CHECK(calls == 2 && sectors == 0);
    hold = 0; Psyz_CdPump(); CHECK(sectors == 3);
    CdReadyCallback(NULL); CdControlB(CdlStop, NULL, NULL);
    unlink(cue); unlink(bin); rmdir(dir);
    puts("CD pump: unread sectors held, header-only sectors skipped, split scene header/payload consumed in FIFO order OK");
    return 0;
}
