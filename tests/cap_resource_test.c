#include "port/cap_asset.h"
#include "main/fs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
_Alignas(16) unsigned char gHostRam[0x200000];
FsResourceSlot gFsResourceSlots[50];
CapFile* gCapFile;
const TextGlyphCell* gCapGlyphCells;
CapCommandRef* gCapCommandEntries;
CapSequenceRecord* gCapSelectedSequence;
int main(void)
{
    /* Minimal CAP with one command, one text and a terminator. */
    const unsigned char disk[] = {
        'C','A','P','2', 8,0,0,0, 20,0,0,0, 28,0,0,0, 68,0,0,0,
        0,0,8,12, 0,0,255,255,
        2,0,12,0,
        1,0,2,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,24,0,0,0,
        0,0,0,0,0,0,0,0,255,255,255,255,
        2,0,0,0, 0,0,0,0, 32,0,0,0
    };
    void* raw = gHostRam + 0x190010;
    memcpy(raw, disk, sizeof disk);
    gFsResourceSlots[3].kind = FILE_SYSTEM_RESOURCE_DATA;
    gFsResourceSlots[3].data = raw;
    peCapSetResourceSize(3, sizeof disk);
    CapFile* file = peCapResolveResource(raw);
    CHECK(file != NULL && file != raw);
    CapCommand* command = file->commands.table->entries[1].command;
    command->counter = 2;
    CHECK(peCapResolveResource(raw) == file && peCapResolveResource(file) == file);
    CHECK(peCapResolveResource(raw)->commands.table->entries[1].command->counter == 2);
    memset(raw, 0, sizeof disk); /* loaded views own their storage */
    CHECK(file->glyphs.cells[0].height == 12);
    gCapFile = file; gCapGlyphCells = file->glyphs.cells;
    gCapCommandEntries = file->commands.table->entries;
    gCapSelectedSequence = file->commands.table->entries[1].sequence;
    peCapResourcesReset();
    CHECK(!gCapFile && !gCapGlyphCells && !gCapCommandEntries && !gCapSelectedSequence);
    memcpy(raw, disk, sizeof disk); peCapSetResourceSize(3, sizeof disk);
    file = peCapResolveResource(raw); CHECK(file != NULL);
    CHECK(file->commands.table->entries[1].command->counter == 0); /* replacement resets live state */
    peCapResourcesReset();
    gFsResourceSlots[3].data = gHostRam + sizeof(gHostRam) - 4;
    peCapSetResourceSize(3, sizeof disk);
    CHECK(peCapResolveResource(gFsResourceSlots[3].data) == NULL);
    CHECK(peCapResolveResource((void*)(uintptr_t)0x80190010) == NULL);
    CHECK(peCapResolveResource(NULL) == NULL);
    puts("CAP resource sharing, replacement and bounds OK");
    return 0;
}
