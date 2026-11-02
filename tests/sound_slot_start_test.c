/* A second queued start must see the first entry before its interpreter tick. */
#include "../src/main/sndscript.c"
#include <stdio.h>
#include <stdlib.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
void Psyz_PadsOverride(int p,char* f,int n){(void)p;(void)f;(void)n;}
void spuKeyOff(u32 v){(void)v; abort();}
void spuClearVoiceCallback(u32 v){(void)v; abort();}
s32 spuReleaseVoiceSlot(u32 v){(void)v; abort();}
int main(void)
{
    SndScriptEntryControls first={0}, second={0}; SndBankSlot bank={0};
    first.priority=10; first.maxInstances=2;
    second.priority=20; second.maxInstances=2;
    _sndScriptStartSlot(0,0,0,0x51000001,&bank,&first);
    CHECK(_gSndScriptInstances[0].entryControls == &first);
    _SndScriptSlotPick pick;
    _sndScriptScanSlotCandidates(&pick,second.priority,0x51000002,second.flags);
    CHECK(pick.idleSlot >= 1 && pick.groupCount == 0);
    /* Reusing a slot must replace the previous bank's borrowed controls. */
    _sndScriptStartSlot(0,0,0,0x51000002,&bank,&second);
    CHECK(_gSndScriptInstances[0].entryControls == &second);
    CHECK(_gSndScriptInstances[0].cursor == (u8*)&second);
    puts("Sound slots: queued starts publish controls immediately and replace old bank references");
    return 0;
}
