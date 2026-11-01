/*
 * Portable replacements for the handwritten TMD stream walk
 * (hasm/Tmd_DispatchStream.s, hasm/tmdSkipStreamRecord.s) and the handler id
 * registry that stands in for the 32-bit code addresses stored in streams.
 */
#include "tmd.h"
#include "main/tmd_types.h"

enum { MAX_HANDLERS = 256 };

typedef u32* (*TmdHandler)(TmdStreamWorkspace*, s32, u32*);

static TmdHandler sHandlers[MAX_HANDLERS];
static u32        sHandlerCount;

u32 tmdHandlerToId(void* handler)
{
    for (u32 i = 0; i < sHandlerCount; i++) {
        if ((void*)sHandlers[i] == handler) {
            return i + 1;
        }
    }
    if (sHandlerCount == MAX_HANDLERS) {
        return 0;
    }
    sHandlers[sHandlerCount] = (TmdHandler)handler;
    return ++sHandlerCount;
}

void* tmdHandlerFromId(u32 id)
{
    return (id != 0 && id <= sHandlerCount) ? (void*)sHandlers[id - 1] : (void*)0;
}

u32* tmdSkipStreamRecord(TmdStreamWorkspace* ws, s32 flags, u32* stream)
{
    (void)flags;
    return stream + (u32)ws->elemStride * (u32)ws->elemCount;
}

/* Record: { opcode, handler, count << 16 | stride }, then count * stride words.
 * Stops at TMD_STREAM_GROUP_END (not consumed) and returns that cursor. */
u32* Tmd_DispatchStream(TmdStreamWorkspace* ws, s32 flags, u32* stream)
{
    ws->dispatchObjectFlags = flags;
    while (stream[0] != (u32)-2) {
        u32 opcode     = stream[0];
        u32 id         = stream[1];
        u32 dimensions = stream[2];
        TmdHandler handler = (TmdHandler)tmdHandlerFromId(id);

        ws->opcode     = opcode;
        ws->elemCount  = (s32)(dimensions >> 16);
        ws->elemStride = (s32)(dimensions & 0xFFFF);
        stream += 3;
        stream = handler(ws, ws->dispatchObjectFlags, stream);
    }
    return stream;
}
