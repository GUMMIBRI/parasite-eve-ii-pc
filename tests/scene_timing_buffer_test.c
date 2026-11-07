#include "main/fs.h"
#include "main/stream_types.h"
#include "main/session.h"
#include "main/mc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHECK(x) do {if(!(x)){fprintf(stderr,"line %d: %s\n",__LINE__,#x);exit(1);}} while(0)
CdCmdQueue gCdCmdQueue;
static GameSession session;
GameSession* gGameSession=&session;
McSaveData gMcSaveData[MEMORY_CARD_SAVE_COUNT];
u8 *gFsActorBuffer0Base,*gFsActorBuffer1Base,*gFsActorBuffer2Base;
s32 gAkropolisStageMovieWorkspaceBytesByArea[21],gMapDryfieldMovieWorkspaceBytesByArea[32],gMapNeoArkMovieWorkspaceBytesByArea[21];
static u32 allocation[512];
void* memMalloc(size_t size,bool aux) {CHECK(aux && size==sizeof allocation);memset(allocation,0xa5,sizeof allocation);return allocation;}
s16 streamFindMovieSlot(const GameLocationKey* key,s32 sub,s32 required) {(void)key;(void)sub;(void)required;return -1;}
void DecDCTvlcBuild(u_short* table) {(void)table;abort();}
int main(void)
{
    static u32 actor[3][STREAM_VLC_TABLE_BYTES/sizeof(u32)+512];StreamSlot stream={0};
    gFsActorBuffer0Base=(u8*)actor[0];gFsActorBuffer1Base=(u8*)actor[1];gFsActorBuffer2Base=(u8*)actor[2];session.location.stage=1;
    for(int kind=1;kind<=4;kind++)for(int shared=0;shared<2;shared++) {
        memset(&gCdCmdQueue,0,sizeof gCdCmdQueue);memset(actor,0xa5,sizeof actor);
        stream.control.scene.timingBufferKind=kind;stream.data.scene.timingBufferBytes=sizeof allocation;
        stream.data.scene.vlcBufferKind=shared && kind>=2?kind-1:0;
        gCdCmdQueue.sceneBuffersNeeded=1;gCdCmdQueue.sceneVlcTableMode=STREAM_SCENE_VLC_IMAGE_BUFFER;gCdCmdQueue.sceneStream=&stream;
        cdCmdReservePlaybackBuffers();
        CHECK(gCdCmdQueue.timingCursor==gCdCmdQueue.timingBuffer);
        CHECK(gCdCmdQueue.timingCursor[0]==CD_COMMAND_TIMING_END);
        CHECK(gCdCmdQueue.timingCursor[1]==0xa5a5a5a5u);
        if(shared && kind>=2)CHECK(actor[kind-2][0]==0xa5a5a5a5u); /* VLC prefix untouched. */
        /* Decoder payload replaces the bootstrap sentinel normally. */
        u32 payload[]={120,240,0};memcpy(gCdCmdQueue.timingBuffer,payload,sizeof payload);
        CHECK(gCdCmdQueue.timingCursor[0]==120 && gCdCmdQueue.timingCursor[2]==0);
    }
    puts("Scene timing: poisoned allocated/borrowed buffers start terminated; VLC prefix and payload preserved");return 0;
}
