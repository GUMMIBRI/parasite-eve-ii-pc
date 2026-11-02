#include "port/cap_asset.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

struct PeCapAsset {
    CapFile file;
    unsigned char* bytes;
    CapSequenceTable* sequences;
    CapCommandTable* commands;
};

static uint32_t word(const unsigned char* p)
{
    return (uint32_t)p[0] | (uint32_t)p[1] << 8 |
           (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24;
}
static unsigned half(const unsigned char* p) { return p[0] | (unsigned)p[1] << 8; }
static int range(size_t length, size_t offset, size_t bytes)
{
    return offset <= length && bytes <= length - offset;
}

static void* tableAllocation(size_t header, size_t count, size_t stride)
{
    if (count > (SIZE_MAX - header) / stride) return NULL;
    return calloc(1, header + count * stride);
}

void peCapFree(PeCapAsset* asset)
{
    if (!asset) return;
    free(asset->commands);
    free(asset->sequences);
    free(asset->bytes);
    free(asset);
}
CapFile* peCapAssetFile(PeCapAsset* asset) { return asset ? &asset->file : NULL; }

PeCapAsset* peCapDecode(const void* data, size_t bytes)
{
    const unsigned char* raw = data;
    const uint32_t endian = 1;
    if (!raw || *(const unsigned char*)&endian != 1 || bytes < 20 ||
        memcmp(raw, "CAP", 3) != 0) return NULL;
    size_t glyphs = word(raw + 8), sequences = word(raw + 12), commands = word(raw + 16);
    if (glyphs < 20 || (glyphs & 3) || (sequences & 1) || (commands & 3) ||
        !range(bytes, sequences, 4) || !range(bytes, commands, 4) ||
        glyphs > sequences || commands < sequences + 4) return NULL;
    unsigned count = half(raw + sequences), stride = half(raw + sequences + 2);
    uint32_t commandCount = word(raw + commands);
    size_t slotBytes = commands - sequences - 4;
    size_t slots = slotBytes / 12;
    if (count > INT16_MAX || stride != 12 || slotBytes % 12 ||
        commandCount > INT32_MAX || commandCount > (bytes - commands - 4) / 4) return NULL;
    _Static_assert(sizeof(TextGlyphCell) == 4, "packed glyph cells");
    _Static_assert(sizeof(CapCommand) == 12, "command bytes stay packed");
    _Static_assert(offsetof(CapSequenceTable, records) ==
                   offsetof(CapSequenceTable, firstCommand) + sizeof(CapSequenceRecord), "native slot stride");
    PeCapAsset* asset = calloc(1, sizeof(*asset));
    if (!asset) return NULL;
    asset->bytes = malloc(bytes);
    asset->sequences = tableAllocation(sizeof(CapSequenceTable), slots, sizeof(CapSequenceRecord));
    asset->commands = tableAllocation(sizeof(CapCommandTable), commandCount, sizeof(CapCommandRef));
    unsigned char* kinds = calloc(slots ? slots : 1, 1);
    if (!asset->bytes || !asset->sequences || !asset->commands || !kinds) goto fail;
    memcpy(asset->bytes, raw, bytes);
    memcpy(asset->file.magic, raw, 4);
    asset->file.field_4 = (s32)word(raw + 4);
    asset->file.glyphs.cells = (TextGlyphCell*)(asset->bytes + glyphs);
    asset->file.sequences.table = asset->sequences;
    asset->file.commands.table = asset->commands;
    asset->sequences->count = count;
    asset->sequences->slotSize = sizeof(CapSequenceRecord);
    asset->commands->count = commandCount;
    unsigned char* native = (unsigned char*)&asset->sequences->firstCommand;
    unsigned records = 0;
    int expectCommand = 1;
    size_t textStart = sequences;
    for (size_t i = 0; i < slots; ++i) {
        const unsigned char* disk = raw + sequences + 4 + i * 12;
        unsigned char* slot = native + i * sizeof(CapSequenceRecord);
        if (expectCommand) {
            memcpy(slot, disk, sizeof(CapCommand));
            kinds[i] = 1;
            expectCommand = 0;
        } else {
            CapSequenceRecord* record = (CapSequenceRecord*)slot;
            memcpy(record, disk, 8);
            uint32_t text = word(disk + 8);
            ++records;
            if (text == UINT32_MAX) {
                record->textRef.offset = CAP_TEXT_REF_END;
                expectCommand = 1;
            } else {
                if ((text & 1) || text < glyphs || !range(sequences, text, 2)) goto fail;
                size_t end = text;
                while (range(sequences, end, 2) && half(raw + end) != UINT16_MAX) end += 2;
                if (!range(sequences, end, 2)) goto fail;
                if (text < textStart) textStart = text;
                record->textRef.text = (const u16*)(asset->bytes + text);
            }
        }
    }
    if (!expectCommand || records != count || ((textStart - glyphs) & 3)) goto fail;
    for (size_t i = 0; i < commandCount; ++i) {
        size_t ref = word(raw + commands + 4 + i * 4);
        if (!ref) continue;
        size_t first = sequences + 4;
        if (ref < first || ref >= commands || (ref - first) % 12) goto fail;
        size_t index = (ref - first) / 12;
        if (!kinds[index]) goto fail;
        asset->commands->entries[i].command = (CapCommand*)(native + index * sizeof(CapSequenceRecord));
    }
    free(kinds);
    return asset;
fail:
    free(kinds);
    peCapFree(asset);
    return NULL;
}
