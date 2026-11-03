/* rooms/mist/parking/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "gameplay/evs.h"
#include "gameplay/item_menu.h"
#include "stages/akropolis/rooms/mist_parking.h"

#ifndef PE_DECODE_EvsCommand
#define PE_DECODE_EvsCommand
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_EvsCommand(EvsCommand* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->opcode = v; }
    { uint32_t v; memcpy(&v, src + 4, 4); dst->operand0.value = v; }
    { uint32_t v; memcpy(&v, src + 8, 4); dst->operand1.value = v; }
    { uint32_t v; memcpy(&v, src + 12, 4); dst->operand2.value = v; }
    { uint32_t v; memcpy(&v, src + 16, 4); dst->operand3.value = v; }
    { uint32_t v; memcpy(&v, src + 20, 4); dst->operand4.value = v; }
}

#endif
EvsCommand gMistParkingArrivalConversationScript[155];
static void peDecodeArr_gMistParkingArrivalConversationScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[1].operand0.storage = (void*)&_mistParkingStartPlayerHeadAim;
    dst[3].operand3.storage = &gMistParkingPlayerConversationBankCopy;
    dst[4].operand3.storage = &_gMistParkingPlayerArrivalAndDepartureTransform;
    dst[6].operand3.storage = &_gMistParkingPierceArrivalStartTransform;
    dst[8].operand3.storage = &_gMistParkingJodieShopTransform;
    dst[9].operand3.storage = &_gMistParkingPierceShowBillboardCommand;
    dst[10].operand3.storage = &_gMistParkingJodieConversationRestAnimation;
    dst[14].operand0.storage = (void*)&_mistParkingSpawnCutsceneModel;
    dst[15].operand3.storage = &_gMistParkingPlayerCutsceneModelCueAnimation;
    dst[18].operand0.storage = (void*)&_mistParkingReleaseCutsceneModel;
    dst[19].operand3.storage = &_gMistParkingPlayerArrivalApproachTransform;
    dst[20].operand3.storage = &_gMistParkingPlayerArrivalClip52Request;
    dst[22].operand3.storage = &_gMistParkingPierceArrivalTalkTransform;
    dst[22].operand4.storage = &_gMistParkingPierceArrivalTalkWalkClips;
    dst[25].operand3.storage = &_gMistParkingPlayerArrivalClip53Request;
    dst[29].operand3.storage = &_gMistParkingPlayerArrivalClip54Request;
    dst[30].operand3.storage = &_gMistParkingPierceArrivalClip28Request;
    dst[31].operand3.storage = &_gMistParkingPierceArrivalTalkTransform;
    dst[36].operand3.storage = &_gMistParkingPlayerArrivalClip55Request;
    dst[40].operand3.storage = &_gMistParkingPierceArrivalClip27Request;
    dst[42].operand3.storage = &_gMistParkingPierceArrivalClip34Request;
    dst[44].operand3.storage = &_gMistParkingPlayerArrivalClip56Request;
    dst[49].operand3.storage = &_gMistParkingPlayerArrivalTalkTransform;
    dst[50].operand3.storage = &_gMistParkingPlayerArrivalTalkResetAnimation;
    dst[51].operand3.storage = &_gMistParkingPierceArrivalClip17Request;
    dst[56].operand3.storage = &_gMistParkingPlayerArrivalTalkTransform;
    dst[57].operand3.storage = &_gMistParkingPierceArrivalClip18Request;
    dst[59].operand3.storage = &_gMistParkingPlayerArrivalClip57Request;
    dst[60].operand3.storage = &_gMistParkingPierceAimHeadCommand;
    dst[66].operand3.storage = &_gMistParkingPierceHideBillboardCommand;
    dst[70].operand3.storage = &_gMistParkingPlayerTalkAnimation;
    dst[71].operand3.storage = &_gMistParkingPierceArrivalClip20Request;
    dst[73].operand3.storage = &_gMistParkingPlayerArrivalTalkResetAnimation;
    dst[74].operand3.storage = &_gMistParkingPierceConversationRestAnimation;
    dst[76].operand3.storage = &_gMistParkingPlayerArrivalClip66Request;
    dst[77].operand3.storage = &_gMistParkingPierceArrivalClip27Request;
    dst[79].operand3.storage = &_gMistParkingPlayerArrivalCueAnimation50;
    dst[81].operand3.storage = &_gMistParkingPlayerArrivalClip67Request;
    dst[82].operand3.storage = &_gMistParkingPierceArrivalClip29Request;
    dst[84].operand3.storage = &_gMistParkingPlayerTalkAnimation;
    dst[85].operand3.storage = &_gMistParkingPierceArrivalClip31Request;
    dst[88].operand3.storage = &_gMistParkingPlayerArrivalClip66Request;
    dst[90].operand3.storage = &_gMistParkingPierceArrivalClip27Request;
    dst[93].operand3.storage = &_gMistParkingPlayerArrivalClip60Request;
    dst[95].operand3.storage = &_gMistParkingPierceConversationRestAnimation;
    dst[97].operand3.storage = &_gMistParkingPlayerArrivalClip61Request;
    dst[99].operand3.storage = &_gMistParkingPierceArrivalClip34Request;
    dst[101].operand3.storage = &_gMistParkingPlayerArrivalClip67Request;
    dst[103].operand3.storage = &_gMistParkingPlayerArrivalClosingTransform;
    dst[104].operand3.storage = &_gMistParkingPlayerTalkAnimation;
    dst[105].operand3.storage = &_gMistParkingPierceArrivalClip19Request;
    dst[107].operand3.storage = &_gMistParkingPlayerArrivalTalkResetAnimation;
    dst[109].operand3.storage = &_gMistParkingPlayerArrivalClip67Request;
    dst[112].operand3.storage = &_gMistParkingPierceArrivalClosingTransform;
    dst[113].operand3.storage = &_gMistParkingPierceConversationRestAnimation;
    dst[115].operand3.storage = &_gMistParkingPierceArrivalClosingAnimation;
    dst[117].operand3.storage = &_gMistParkingPierceConversationRestAnimation;
    dst[120].operand3.storage = &_gMistParkingPlayerArrivalTalkTransform;
    dst[121].operand3.storage = &_gMistParkingPlayerDepartureReplyAnimation;
    dst[122].operand3.storage = &_gMistParkingPierceArrivalTalkTransform;
    dst[124].operand3.storage = &_gMistParkingPlayerArrivalClip71Request;
    dst[126].operand3.storage = &_gMistParkingPlayerConversationResetAnimation;
    dst[127].operand3.storage = &_gMistParkingPierceArrivalClosingAnimation;
    dst[129].operand3.storage = &_gMistParkingPlayerConversationResetAnimation;
    dst[131].operand3.storage = &_gMistParkingPlayerArrivalClip67Request;
    dst[133].operand3.storage = &_gMistParkingPierceConversationRestAnimation;
    dst[135].operand3.storage = &_gMistParkingPlayerArrivalClip63Request;
    dst[137].operand0.storage = (void*)&mistParkingControlPlayerHeadAim;
    dst[143].operand0.storage = (void*)&mistParkingControlPlayerHeadAim;
    dst[144].operand0.storage = (void*)&mistParkingSetPierceCollisionPatchLowered;
    dst[145].operand3.storage = &_gMistParkingPiercePostArrivalTransform;
    dst[145].operand4.storage = &_gMistParkingPiercePostArrivalWalkClips;
    dst[146].operand3.storage = &_gMistParkingPierceReleaseHeadCommand;
    dst[153].operand0.storage = (void*)&mistParkingSetConversationProgress;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/gMistParkingArrivalConversationScript", gMistParkingArrivalConversationScript, peDecodeArr_gMistParkingArrivalConversationScript);
#ifndef PE_DECODE_EvsCommand
#define PE_DECODE_EvsCommand
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_EvsCommand(EvsCommand* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->opcode = v; }
    { uint32_t v; memcpy(&v, src + 4, 4); dst->operand0.value = v; }
    { uint32_t v; memcpy(&v, src + 8, 4); dst->operand1.value = v; }
    { uint32_t v; memcpy(&v, src + 12, 4); dst->operand2.value = v; }
    { uint32_t v; memcpy(&v, src + 16, 4); dst->operand3.value = v; }
    { uint32_t v; memcpy(&v, src + 20, 4); dst->operand4.value = v; }
}

#endif
EvsCommand gMistParkingArrivalSkipScript[23];
static void peDecodeArr_gMistParkingArrivalSkipScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[4].operand0.storage = (void*)&_mistParkingReleaseCutsceneModel;
    dst[5].operand0.storage = (void*)&mistParkingControlPlayerHeadAim;
    dst[6].operand0.storage = (void*)&mistParkingSetPierceCollisionPatchLowered;
    dst[8].operand3.storage = &_gMistParkingPlayerArrivalTalkTransform;
    dst[11].operand3.storage = &_gMistParkingPierceArrivalTalkTransform;
    dst[12].operand3.storage = &_gMistParkingPierceHideBillboardCommand;
    dst[14].operand3.storage = &_gMistParkingPiercePostArrivalTransform;
    dst[14].operand4.storage = &_gMistParkingPiercePostArrivalWalkClips;
    dst[15].operand3.storage = &_gMistParkingPierceReleaseHeadCommand;
    dst[21].operand0.storage = (void*)&mistParkingSetConversationProgress;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/gMistParkingArrivalSkipScript", gMistParkingArrivalSkipScript, peDecodeArr_gMistParkingArrivalSkipScript);
#ifndef PE_DECODE_EvsCommand
#define PE_DECODE_EvsCommand
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_EvsCommand(EvsCommand* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->opcode = v; }
    { uint32_t v; memcpy(&v, src + 4, 4); dst->operand0.value = v; }
    { uint32_t v; memcpy(&v, src + 8, 4); dst->operand1.value = v; }
    { uint32_t v; memcpy(&v, src + 12, 4); dst->operand2.value = v; }
    { uint32_t v; memcpy(&v, src + 16, 4); dst->operand3.value = v; }
    { uint32_t v; memcpy(&v, src + 20, 4); dst->operand4.value = v; }
}

#endif
EvsCommand gMistParkingArrivalRoomEntryScript[8];
static void peDecodeArr_gMistParkingArrivalRoomEntryScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[1].operand3.storage = &_gMistParkingPierceArrivalTalkTransform;
    dst[2].operand3.storage = &_gMistParkingPierceHideBillboardCommand;
    dst[3].operand3.storage = &_gMistParkingPiercePostArrivalTransform;
    dst[3].operand4.storage = &_gMistParkingPiercePostArrivalWalkClips;
    dst[5].operand3.storage = &_gMistParkingJodieShopTransform;
    dst[6].operand3.storage = &_gMistParkingJodieConversationRestAnimation;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/gMistParkingArrivalRoomEntryScript", gMistParkingArrivalRoomEntryScript, peDecodeArr_gMistParkingArrivalRoomEntryScript);
#ifndef PE_DECODE_EvsCommand
#define PE_DECODE_EvsCommand
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_EvsCommand(EvsCommand* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->opcode = v; }
    { uint32_t v; memcpy(&v, src + 4, 4); dst->operand0.value = v; }
    { uint32_t v; memcpy(&v, src + 8, 4); dst->operand1.value = v; }
    { uint32_t v; memcpy(&v, src + 12, 4); dst->operand2.value = v; }
    { uint32_t v; memcpy(&v, src + 16, 4); dst->operand3.value = v; }
    { uint32_t v; memcpy(&v, src + 20, 4); dst->operand4.value = v; }
}

#endif
EvsCommand gMistParkingFirstFollowupScript[10];
static void peDecodeArr_gMistParkingFirstFollowupScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand0.storage = (void*)&_mistParkingStartPlayerHeadAim;
    dst[1].operand3.storage = &gMistParkingPlayerConversationBankCopy;
    dst[2].operand0.storage = (void*)&_mistParkingStartPackedDialogue;
    dst[3].operand3.storage = &_gMistParkingPlayerTalkAnimation;
    dst[4].operand3.storage = &_gMistParkingPierceFollowupTalkAnimation;
    dst[6].operand0.storage = (void*)&mistParkingControlPlayerHeadAim;
    dst[8].operand3.storage = &_gMistParkingPierceConversationRestAnimation;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/gMistParkingFirstFollowupScript", gMistParkingFirstFollowupScript, peDecodeArr_gMistParkingFirstFollowupScript);
#ifndef PE_DECODE_EvsCommand
#define PE_DECODE_EvsCommand
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_EvsCommand(EvsCommand* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->opcode = v; }
    { uint32_t v; memcpy(&v, src + 4, 4); dst->operand0.value = v; }
    { uint32_t v; memcpy(&v, src + 8, 4); dst->operand1.value = v; }
    { uint32_t v; memcpy(&v, src + 12, 4); dst->operand2.value = v; }
    { uint32_t v; memcpy(&v, src + 16, 4); dst->operand3.value = v; }
    { uint32_t v; memcpy(&v, src + 20, 4); dst->operand4.value = v; }
}

#endif
EvsCommand gMistParkingSecondFollowupScript[10];
static void peDecodeArr_gMistParkingSecondFollowupScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand0.storage = (void*)&_mistParkingStartPlayerHeadAim;
    dst[1].operand3.storage = &gMistParkingPlayerConversationBankCopy;
    dst[2].operand0.storage = (void*)&_mistParkingStartPackedDialogue;
    dst[3].operand3.storage = &_gMistParkingPlayerTalkAnimation;
    dst[4].operand3.storage = &_gMistParkingPierceFollowupTalkAnimation;
    dst[6].operand0.storage = (void*)&mistParkingControlPlayerHeadAim;
    dst[8].operand3.storage = &_gMistParkingPierceConversationRestAnimation;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/gMistParkingSecondFollowupScript", gMistParkingSecondFollowupScript, peDecodeArr_gMistParkingSecondFollowupScript);
#ifndef PE_DECODE_EvsCommand
#define PE_DECODE_EvsCommand
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_EvsCommand(EvsCommand* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->opcode = v; }
    { uint32_t v; memcpy(&v, src + 4, 4); dst->operand0.value = v; }
    { uint32_t v; memcpy(&v, src + 8, 4); dst->operand1.value = v; }
    { uint32_t v; memcpy(&v, src + 12, 4); dst->operand2.value = v; }
    { uint32_t v; memcpy(&v, src + 16, 4); dst->operand3.value = v; }
    { uint32_t v; memcpy(&v, src + 20, 4); dst->operand4.value = v; }
}

#endif
static EvsCommand _gMistParkingUnusedThirdFollowupScript[10];
static void peDecodeArr_gMistParkingUnusedThirdFollowupScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand0.storage = (void*)&_mistParkingStartPlayerHeadAim;
    dst[1].operand3.storage = &gMistParkingPlayerConversationBankCopy;
    dst[2].operand0.storage = (void*)&_mistParkingStartPackedDialogue;
    dst[3].operand3.storage = &_gMistParkingPlayerTalkAnimation;
    dst[4].operand3.storage = &_gMistParkingPierceFollowupTalkAnimation;
    dst[6].operand0.storage = (void*)&mistParkingControlPlayerHeadAim;
    dst[8].operand3.storage = &_gMistParkingPierceConversationRestAnimation;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingUnusedThirdFollowupScript", _gMistParkingUnusedThirdFollowupScript, peDecodeArr_gMistParkingUnusedThirdFollowupScript);
#ifndef PE_DECODE_EvsCommand
#define PE_DECODE_EvsCommand
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_EvsCommand(EvsCommand* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->opcode = v; }
    { uint32_t v; memcpy(&v, src + 4, 4); dst->operand0.value = v; }
    { uint32_t v; memcpy(&v, src + 8, 4); dst->operand1.value = v; }
    { uint32_t v; memcpy(&v, src + 12, 4); dst->operand2.value = v; }
    { uint32_t v; memcpy(&v, src + 16, 4); dst->operand3.value = v; }
    { uint32_t v; memcpy(&v, src + 20, 4); dst->operand4.value = v; }
}

#endif
static EvsCommand _gMistParkingDeparturePromptScript[13];
static void peDecodeArr_gMistParkingDeparturePromptScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand0.storage = (void*)&_mistParkingStartPlayerHeadAim;
    dst[1].operand3.storage = &gMistParkingPlayerConversationBankCopy;
    dst[2].operand3.storage = &_gMistParkingPierceAimHeadCommand;
    dst[3].operand0.storage = (void*)&mistParkingSelectDialogueResource;
    dst[7].operand3.storage = &_gMistParkingPlayerDeparturePromptTransform;
    dst[8].operand3.storage = &_gMistParkingPlayerTalkAnimation;
    dst[9].operand3.storage = &_gMistParkingPierceDeparturePromptAnimation;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingDeparturePromptScript", _gMistParkingDeparturePromptScript, peDecodeArr_gMistParkingDeparturePromptScript);
#ifndef PE_DECODE_EvsCommand
#define PE_DECODE_EvsCommand
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_EvsCommand(EvsCommand* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->opcode = v; }
    { uint32_t v; memcpy(&v, src + 4, 4); dst->operand0.value = v; }
    { uint32_t v; memcpy(&v, src + 8, 4); dst->operand1.value = v; }
    { uint32_t v; memcpy(&v, src + 12, 4); dst->operand2.value = v; }
    { uint32_t v; memcpy(&v, src + 16, 4); dst->operand3.value = v; }
    { uint32_t v; memcpy(&v, src + 20, 4); dst->operand4.value = v; }
}

#endif
static EvsCommand _gMistParkingStayReplyScript[13];
static void peDecodeArr_gMistParkingStayReplyScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &gMistParkingPlayerConversationBankCopy;
    dst[1].operand0.storage = (void*)&_mistParkingStartPackedDialogue;
    dst[2].operand3.storage = &_gMistParkingPlayerStayOrGalleryReplyAnimation;
    dst[4].operand3.storage = &_gMistParkingPierceDepartureReplyAnimation;
    dst[6].operand0.storage = (void*)&mistParkingControlPlayerHeadAim;
    dst[7].operand3.storage = &_gMistParkingPlayerStayOrGalleryReplyAnimation;
    dst[8].operand3.storage = &_gMistParkingPierceReleaseHeadCommand;
    dst[10].operand0.storage = (void*)&mistParkingSelectDialogueResource;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingStayReplyScript", _gMistParkingStayReplyScript, peDecodeArr_gMistParkingStayReplyScript);
#ifndef PE_DECODE_EvsCommand
#define PE_DECODE_EvsCommand
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_EvsCommand(EvsCommand* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->opcode = v; }
    { uint32_t v; memcpy(&v, src + 4, 4); dst->operand0.value = v; }
    { uint32_t v; memcpy(&v, src + 8, 4); dst->operand1.value = v; }
    { uint32_t v; memcpy(&v, src + 12, 4); dst->operand2.value = v; }
    { uint32_t v; memcpy(&v, src + 16, 4); dst->operand3.value = v; }
    { uint32_t v; memcpy(&v, src + 20, 4); dst->operand4.value = v; }
}

#endif
static EvsCommand _gMistParkingDryfieldDepartureScript[24];
static void peDecodeArr_gMistParkingDryfieldDepartureScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &gMistParkingPlayerConversationBankCopy;
    dst[1].operand0.storage = (void*)&_mistParkingStartPackedDialogue;
    dst[2].operand3.storage = &_gMistParkingPlayerDepartureReplyAnimation;
    dst[4].operand3.storage = &_gMistParkingPierceDepartureReplyAnimation;
    dst[6].operand0.storage = (void*)&mistParkingControlPlayerHeadAim;
    dst[7].operand3.storage = &_gMistParkingPlayerArrivalAndDepartureTransform;
    dst[8].operand3.storage = &_gMistParkingPierceDryfieldDepartureTarget;
    dst[9].operand3.storage = &_gMistParkingPierceReleaseHeadCommand;
    dst[14].operand0.storage = (void*)&mistParkingQueueDelayedDisplayModeExit;
    dst[18].operand0.storage = (void*)&mistParkingSelectDialogueResource;
    dst[20].operand0.storage = (void*)&_mistParkingStartDepartureMovie;
    dst[22].operand0.storage = (void*)&_mistParkingQueueDryfieldDeparture;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingDryfieldDepartureScript", _gMistParkingDryfieldDepartureScript, peDecodeArr_gMistParkingDryfieldDepartureScript);
#ifndef PE_DECODE_EvsCommand
#define PE_DECODE_EvsCommand
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_EvsCommand(EvsCommand* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->opcode = v; }
    { uint32_t v; memcpy(&v, src + 4, 4); dst->operand0.value = v; }
    { uint32_t v; memcpy(&v, src + 8, 4); dst->operand1.value = v; }
    { uint32_t v; memcpy(&v, src + 12, 4); dst->operand2.value = v; }
    { uint32_t v; memcpy(&v, src + 16, 4); dst->operand3.value = v; }
    { uint32_t v; memcpy(&v, src + 20, 4); dst->operand4.value = v; }
}

#endif
static EvsCommand _gMistParkingShootingGalleryDepartureScript[16];
static void peDecodeArr_gMistParkingShootingGalleryDepartureScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &gMistParkingPlayerConversationBankCopy;
    dst[1].operand0.storage = (void*)&_mistParkingStartPackedDialogue;
    dst[2].operand3.storage = &_gMistParkingPlayerStayOrGalleryReplyAnimation;
    dst[3].operand3.storage = &_gMistParkingPierceConversationRestAnimation;
    dst[5].operand3.storage = &_gMistParkingPierceDepartureReplyAnimation;
    dst[9].operand0.storage = (void*)&mistParkingControlPlayerHeadAim;
    dst[11].operand0.storage = (void*)&mistParkingQueueDelayedDisplayModeExit;
    dst[13].operand0.storage = (void*)&_mistParkingReloadAkropolisArea;
    dst[14].operand0.storage = (void*)&mistParkingSelectDialogueResource;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingShootingGalleryDepartureScript", _gMistParkingShootingGalleryDepartureScript, peDecodeArr_gMistParkingShootingGalleryDepartureScript);
#ifndef PE_DECODE_EvsCommand
#define PE_DECODE_EvsCommand
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_EvsCommand(EvsCommand* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->opcode = v; }
    { uint32_t v; memcpy(&v, src + 4, 4); dst->operand0.value = v; }
    { uint32_t v; memcpy(&v, src + 8, 4); dst->operand1.value = v; }
    { uint32_t v; memcpy(&v, src + 12, 4); dst->operand2.value = v; }
    { uint32_t v; memcpy(&v, src + 16, 4); dst->operand3.value = v; }
    { uint32_t v; memcpy(&v, src + 20, 4); dst->operand4.value = v; }
}

#endif
static EvsCommand _gMistParkingJodieTalkPoseScript[7];
static void peDecodeArr_gMistParkingJodieTalkPoseScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &gMistParkingPlayerConversationBankCopy;
    dst[1].operand3.storage = &_gMistParkingPlayerConversationResetAnimation;
    dst[2].operand3.storage = &_gMistParkingJodieTalkOpeningAnimation;
    dst[4].operand3.storage = &_gMistParkingJodieTalkGreetingAnimation;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingJodieTalkPoseScript", _gMistParkingJodieTalkPoseScript, peDecodeArr_gMistParkingJodieTalkPoseScript);
#ifndef PE_DECODE_EvsCommand
#define PE_DECODE_EvsCommand
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_EvsCommand(EvsCommand* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->opcode = v; }
    { uint32_t v; memcpy(&v, src + 4, 4); dst->operand0.value = v; }
    { uint32_t v; memcpy(&v, src + 8, 4); dst->operand1.value = v; }
    { uint32_t v; memcpy(&v, src + 12, 4); dst->operand2.value = v; }
    { uint32_t v; memcpy(&v, src + 16, 4); dst->operand3.value = v; }
    { uint32_t v; memcpy(&v, src + 20, 4); dst->operand4.value = v; }
}

#endif
static EvsCommand _gMistParkingJodieShopSessionScript[10];
static void peDecodeArr_gMistParkingJodieShopSessionScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &gMistParkingPlayerConversationBankCopy;
    dst[1].operand0.storage = (void*)&shopOpenSession;
    dst[3].operand3.storage = &_gMistParkingPlayerConversationResetAnimation;
    dst[4].operand3.storage = &_gMistParkingJodieShopReplyAnimation;
    dst[6].operand3.storage = &_gMistParkingJodieShopReplyClosingAnimation;
    dst[8].operand3.storage = &_gMistParkingJodieConversationRestAnimation;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingJodieShopSessionScript", _gMistParkingJodieShopSessionScript, peDecodeArr_gMistParkingJodieShopSessionScript);
#ifndef PE_DECODE_EvsCommand
#define PE_DECODE_EvsCommand
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_EvsCommand(EvsCommand* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->opcode = v; }
    { uint32_t v; memcpy(&v, src + 4, 4); dst->operand0.value = v; }
    { uint32_t v; memcpy(&v, src + 8, 4); dst->operand1.value = v; }
    { uint32_t v; memcpy(&v, src + 12, 4); dst->operand2.value = v; }
    { uint32_t v; memcpy(&v, src + 16, 4); dst->operand3.value = v; }
    { uint32_t v; memcpy(&v, src + 20, 4); dst->operand4.value = v; }
}

#endif
static EvsCommand _gMistParkingJodieShopDeclineScript[8];
static void peDecodeArr_gMistParkingJodieShopDeclineScript(void* base, const unsigned char* src, size_t n)
{
    EvsCommand* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_EvsCommand(&dst[k], src + k * 24);
    dst[0].operand3.storage = &gMistParkingPlayerConversationBankCopy;
    dst[1].operand3.storage = &_gMistParkingPlayerConversationResetAnimation;
    dst[2].operand3.storage = &_gMistParkingJodieShopReplyAnimation;
    dst[4].operand3.storage = &_gMistParkingJodieShopReplyClosingAnimation;
    dst[6].operand3.storage = &_gMistParkingJodieConversationRestAnimation;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_parking/_gMistParkingJodieShopDeclineScript", _gMistParkingJodieShopDeclineScript, peDecodeArr_gMistParkingJodieShopDeclineScript);
