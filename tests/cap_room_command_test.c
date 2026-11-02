#include "gameplay/captions.h"
#include "gameplay/cap.h"
#include "gameplay/message.h"
#include "main/session.h"
#include "port/cap_asset.h"
#include <stdio.h>
#include <stdlib.h>

#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
CapCommandRef* gCapCommandEntries;
static Task room;
static int messages, sequences;
static s32 expectedCommand;
Task* gameGetTaskSlot(s32 slot) { CHECK(slot == GAME_TASK_SLOT_ROOM); return &room; }
s32 taskMessageDispatch(Task* receiver, s32 id, TaskMessageWord first, TaskMessageWord second)
{
    CHECK(receiver == &room && id == ROOM_MESSAGE_COMMAND);
    CHECK(first == expectedCommand && second == 0);
    ++messages;
    return 0;
}
s32 gameFlagGetNibble(s32 flag) { (void)flag; return 0; }
void gameFlagSetNibble(s32 flag, s32 value) { (void)flag; (void)value; }
s32 areaGetCurrentObjectState(s32 object) { (void)object; return 0; }
s16 capStartSequenceSlot(s16 command, s16 mode, s16 variant)
{
    CHECK(command == 1 && mode == CAP_PLAYBACK_CLEAR_IF_UNSTARTED && variant == 0);
    ++sequences;
    return 0;
}
int main(int argc, char** argv)
{
    CHECK(argc == 2);
    FILE* input = fopen(argv[1], "rb"); CHECK(input);
    CHECK(fseek(input, 0, SEEK_END) == 0);
    long size = ftell(input); CHECK(size > 0); rewind(input);
    unsigned char* raw = malloc((size_t)size); CHECK(raw);
    CHECK(fread(raw, 1, (size_t)size, input) == (size_t)size); fclose(input);
    PeCapAsset* asset = peCapDecode(raw, (size_t)size); CHECK(asset);
    free(raw);
    gCapCommandEntries = peCapAssetFile(asset)->commands.table->entries;
    CHECK(gCapCommandEntries[0].command == NULL);
    expectedCommand = 0;
    capRunCommand(0, CAP_PLAYBACK_CLEAR_IF_UNSTARTED);
    CHECK(messages == 1 && sequences == 0);
    capRunCommand(1, CAP_PLAYBACK_CLEAR_IF_UNSTARTED);
    CHECK(messages == 1 && sequences == 1);
    /* An ordinary explicit room command takes the same dispatch path. */
    CapCommand command = { .opcode = CAP_COMMAND_ROOM };
    CapCommandRef refs[3] = {0}; refs[2].command = &command;
    gCapCommandEntries = refs; expectedCommand = 2;
    capRunCommand(2, CAP_PLAYBACK_CLEAR_IF_UNSTARTED);
    CHECK(messages == 2 && sequences == 1);
    peCapFree(asset);
    puts("Retail Sanctuary CAP 0 dispatches to the room; text and explicit room commands OK");
    return 0;
}
