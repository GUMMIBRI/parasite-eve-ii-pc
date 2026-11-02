#include "port/cap_asset.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static void put(unsigned char* p, uint32_t v)
{
    for (unsigned i = 0; i < 4; ++i) p[i] = (unsigned char)(v >> (i * 8));
}
static void fixtures(void)
{
    unsigned char raw[128] = { 'C','A','P','2' };
    put(raw + 4, 8); put(raw + 8, 20); put(raw + 12, 32); put(raw + 16, 108);
    raw[22] = 8; raw[23] = 12; /* one glyph */
    raw[26] = raw[27] = raw[30] = raw[31] = 255;
    raw[32] = 4; raw[34] = 12; /* four sequence records in six slots */
    raw[36] = CAP_COMMAND_COUNTER; raw[38] = 2; raw[40] = 1;
    raw[48] = 3; put(raw + 56, 24); put(raw + 68, UINT32_MAX);
    raw[72] = CAP_COMMAND_PLAIN; raw[89] = 7; put(raw + 92, 28); put(raw + 104, UINT32_MAX);
    put(raw + 108, 4); put(raw + 116, 36); put(raw + 124, 72);
    unsigned char saved[sizeof raw]; memcpy(saved, raw, sizeof raw);
    PeCapAsset* asset = peCapDecode(raw, sizeof raw);
    CHECK(asset != NULL && memcmp(saved, raw, sizeof raw) == 0);
    CapFile* file = peCapAssetFile(asset);
    CapCommandRef* commands = file->commands.table->entries;
    CHECK(file->commands.table->count == 4 && commands[0].command == NULL && commands[2].command == NULL);
    CHECK(commands[1].command->opcode == CAP_COMMAND_COUNTER && commands[1].command->counter == 1);
    CHECK(commands[1].command == &file->sequences.table->firstCommand);
    CapSequenceRecord* line = _capSequenceRecordAt(commands[1].sequence, 1);
    CHECK(line->control.text.title == 3 && line->textRef.text[1] == 65535);
    CHECK(_capSequenceRecordAt(commands[1].sequence, 2)->textRef.offset == CAP_TEXT_REF_END);
    CHECK(_capSequenceRecordAt(commands[3].sequence, 1)->key == 7);
    CHECK(file->glyphs.cells[0].width == 8 && file->glyphs.cells[0].height == 12);
    commands[1].command->counter++;
    CHECK(raw[40] == 1); /* live native counters do not change serialized offsets/data */
    memset(raw, 0, sizeof raw); /* the view owns its text and glyph bytes */
    CHECK(line->textRef.text[1] == 65535 && file->glyphs.cells[0].height == 12);
    peCapFree(asset);
    memcpy(raw, saved, sizeof raw);
    for (size_t length = 0; length < sizeof raw; ++length) CHECK(peCapDecode(raw, length) == NULL);
    put(raw + 116, 48); CHECK(peCapDecode(raw, sizeof raw) == NULL); /* command points at text slot */
    memcpy(raw, saved, sizeof raw); raw[34] = 16; CHECK(peCapDecode(raw, sizeof raw) == NULL);
    memcpy(raw, saved, sizeof raw); raw[32] = 5; CHECK(peCapDecode(raw, sizeof raw) == NULL);
    memcpy(raw, saved, sizeof raw); put(raw + 56, 25); CHECK(peCapDecode(raw, sizeof raw) == NULL);
    memcpy(raw, saved, sizeof raw); memset(raw + 24, 0, 8); CHECK(peCapDecode(raw, sizeof raw) == NULL);
    puts("CAP native slots, counters, ownership and malformed input OK");
}
int main(int argc, char** argv)
{
    fixtures();
    for (int i = 1; i < argc; ++i) {
        FILE* input = fopen(argv[i], "rb"); CHECK(input != NULL);
        CHECK(fseek(input, 0, SEEK_END) == 0); long length = ftell(input); CHECK(length > 0);
        rewind(input); unsigned char* bytes = malloc((size_t)length); CHECK(bytes != NULL);
        CHECK(fread(bytes, 1, length, input) == (size_t)length); fclose(input);
        PeCapAsset* asset = peCapDecode(bytes, length);
        if (!asset) { fprintf(stderr, "decode failed: %s\n", argv[i]); return 1; }
        peCapFree(asset); free(bytes);
    }
    if (argc > 1) printf("CAP retail files decoded: %d\n", argc - 1);
    return 0;
}
