/* rooms/mist/shooting_gallery/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "rooms/rooms_shared_8018055c.h"

#ifndef PE_DECODE_JukeboxTrack
#define PE_DECODE_JukeboxTrack
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_JukeboxTrack(JukeboxTrack* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->sequenceId = v; }
    /* name: pointer, set by the array's fixups */
}

#endif
static JukeboxTrack _gMistShootingGalleryJukeboxTrainingReplayTracks[3];
static void peDecodeArr_gMistShootingGalleryJukeboxTrainingReplayTracks(void* base, const unsigned char* src, size_t n)
{
    JukeboxTrack* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_JukeboxTrack(&dst[k], src + k * 8);
    dst[0].name = (void*)&_gMistShootingGalleryJukeboxRow1CrazyKingLabel;
    dst[1].name = (void*)&_gMistShootingGalleryJukeboxRow2EagerForBloodLabel;
    dst[2].name = (void*)&_gMistShootingGalleryJukeboxRow3HeavenSentKillerLabel;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryJukeboxTrainingReplayTracks", _gMistShootingGalleryJukeboxTrainingReplayTracks, peDecodeArr_gMistShootingGalleryJukeboxTrainingReplayTracks);
#ifndef PE_DECODE_JukeboxTrack
#define PE_DECODE_JukeboxTrack
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_JukeboxTrack(JukeboxTrack* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->sequenceId = v; }
    /* name: pointer, set by the array's fixups */
}

#endif
static JukeboxTrack _gMistShootingGalleryJukeboxTrainingBountyTracks[3];
static void peDecodeArr_gMistShootingGalleryJukeboxTrainingBountyTracks(void* base, const unsigned char* src, size_t n)
{
    JukeboxTrack* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_JukeboxTrack(&dst[k], src + k * 8);
    dst[0].name = (void*)&_gMistShootingGalleryJukeboxRow1CrazyKingLabel;
    dst[1].name = (void*)&_gMistShootingGalleryJukeboxRow2PickUpTheGauntletLabel;
    dst[2].name = (void*)&_gMistShootingGalleryJukeboxRow3CrawlingWasteEmperorLabel;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryJukeboxTrainingBountyTracks", _gMistShootingGalleryJukeboxTrainingBountyTracks, peDecodeArr_gMistShootingGalleryJukeboxTrainingBountyTracks);
#ifndef PE_DECODE_JukeboxTrack
#define PE_DECODE_JukeboxTrack
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_JukeboxTrack(JukeboxTrack* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->sequenceId = v; }
    /* name: pointer, set by the array's fixups */
}

#endif
static JukeboxTrack _gMistShootingGalleryJukeboxTrainingScavengerTracks[3];
static void peDecodeArr_gMistShootingGalleryJukeboxTrainingScavengerTracks(void* base, const unsigned char* src, size_t n)
{
    JukeboxTrack* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_JukeboxTrack(&dst[k], src + k * 8);
    dst[0].name = (void*)&_gMistShootingGalleryJukeboxRow1CrazyKingLabel;
    dst[1].name = (void*)&_gMistShootingGalleryJukeboxRow2QuadrumanousLeaderLabel;
    dst[2].name = (void*)&_gMistShootingGalleryJukeboxRow3HuntersMoonLabel;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryJukeboxTrainingScavengerTracks", _gMistShootingGalleryJukeboxTrainingScavengerTracks, peDecodeArr_gMistShootingGalleryJukeboxTrainingScavengerTracks);
#ifndef PE_DECODE_JukeboxTrack
#define PE_DECODE_JukeboxTrack
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_JukeboxTrack(JukeboxTrack* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->sequenceId = v; }
    /* name: pointer, set by the array's fixups */
}

#endif
static JukeboxTrack _gMistShootingGalleryJukeboxTrainingNightmareTracks[3];
static void peDecodeArr_gMistShootingGalleryJukeboxTrainingNightmareTracks(void* base, const unsigned char* src, size_t n)
{
    JukeboxTrack* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_JukeboxTrack(&dst[k], src + k * 8);
    dst[0].name = (void*)&_gMistShootingGalleryJukeboxRow1YellowRainLabel;
    dst[1].name = (void*)&_gMistShootingGalleryJukeboxRow2RebelForcesLabel;
    dst[2].name = (void*)&_gMistShootingGalleryJukeboxRow3GenicReactorLabel;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryJukeboxTrainingNightmareTracks", _gMistShootingGalleryJukeboxTrainingNightmareTracks, peDecodeArr_gMistShootingGalleryJukeboxTrainingNightmareTracks);
#ifndef PE_DECODE_JukeboxTrack
#define PE_DECODE_JukeboxTrack
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_JukeboxTrack(JukeboxTrack* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->sequenceId = v; }
    /* name: pointer, set by the array's fixups */
}

#endif
static JukeboxTrack _gMistShootingGalleryJukeboxTrainingUnclearedTracks[3];
static void peDecodeArr_gMistShootingGalleryJukeboxTrainingUnclearedTracks(void* base, const unsigned char* src, size_t n)
{
    JukeboxTrack* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_JukeboxTrack(&dst[k], src + k * 8);
    dst[0].name = (void*)&_gMistShootingGalleryJukeboxRow1CrazyKingLabel;
    dst[1].name = (void*)&_gMistShootingGalleryJukeboxRow2AmbushLabel;
    dst[2].name = (void*)&_gMistShootingGalleryJukeboxRow3PickUpTheGauntletLabel;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryJukeboxTrainingUnclearedTracks", _gMistShootingGalleryJukeboxTrainingUnclearedTracks, peDecodeArr_gMistShootingGalleryJukeboxTrainingUnclearedTracks);
#ifndef PE_DECODE_JukeboxTrack
#define PE_DECODE_JukeboxTrack
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_JukeboxTrack(JukeboxTrack* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->sequenceId = v; }
    /* name: pointer, set by the array's fixups */
}

#endif
static JukeboxTrack _gMistShootingGalleryJukeboxRegularReplayTracks[4];
static void peDecodeArr_gMistShootingGalleryJukeboxRegularReplayTracks(void* base, const unsigned char* src, size_t n)
{
    JukeboxTrack* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_JukeboxTrack(&dst[k], src + k * 8);
    dst[0].name = (void*)&_gMistShootingGalleryJukeboxRow1GhostTownLabel;
    dst[1].name = (void*)&_gMistShootingGalleryJukeboxRow2RockAndFireLabel;
    dst[2].name = (void*)&_gMistShootingGalleryJukeboxRow3RequiemLabel;
    dst[3].name = (void*)&_gMistShootingGalleryJukeboxRow4DarkVoiceOfTheHeartLabel;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryJukeboxRegularReplayTracks", _gMistShootingGalleryJukeboxRegularReplayTracks, peDecodeArr_gMistShootingGalleryJukeboxRegularReplayTracks);
#ifndef PE_DECODE_JukeboxTrack
#define PE_DECODE_JukeboxTrack
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_JukeboxTrack(JukeboxTrack* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->sequenceId = v; }
    /* name: pointer, set by the array's fixups */
}

#endif
static JukeboxTrack _gMistShootingGalleryJukeboxRegularBountyTracks[4];
static void peDecodeArr_gMistShootingGalleryJukeboxRegularBountyTracks(void* base, const unsigned char* src, size_t n)
{
    JukeboxTrack* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_JukeboxTrack(&dst[k], src + k * 8);
    dst[0].name = (void*)&_gMistShootingGalleryJukeboxRow1LAMazeLabel;
    dst[1].name = (void*)&_gMistShootingGalleryJukeboxRow2LightningOperationLabel;
    dst[2].name = (void*)&_gMistShootingGalleryJukeboxRow3WildHuntLabel;
    dst[3].name = (void*)&_gMistShootingGalleryJukeboxRow4SnooperLabel;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryJukeboxRegularBountyTracks", _gMistShootingGalleryJukeboxRegularBountyTracks, peDecodeArr_gMistShootingGalleryJukeboxRegularBountyTracks);
#ifndef PE_DECODE_JukeboxTrack
#define PE_DECODE_JukeboxTrack
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_JukeboxTrack(JukeboxTrack* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->sequenceId = v; }
    /* name: pointer, set by the array's fixups */
}

#endif
static JukeboxTrack _gMistShootingGalleryJukeboxRegularScavengerTracks[4];
static void peDecodeArr_gMistShootingGalleryJukeboxRegularScavengerTracks(void* base, const unsigned char* src, size_t n)
{
    JukeboxTrack* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_JukeboxTrack(&dst[k], src + k * 8);
    dst[0].name = (void*)&_gMistShootingGalleryJukeboxRow1CurseYourFateLabel;
    dst[1].name = (void*)&_gMistShootingGalleryJukeboxRow2WishwashLabel;
    dst[2].name = (void*)&_gMistShootingGalleryJukeboxRow3MentalAgonyLabel;
    dst[3].name = (void*)&_gMistShootingGalleryJukeboxRow4GenicReactorLabel;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryJukeboxRegularScavengerTracks", _gMistShootingGalleryJukeboxRegularScavengerTracks, peDecodeArr_gMistShootingGalleryJukeboxRegularScavengerTracks);
#ifndef PE_DECODE_JukeboxTrack
#define PE_DECODE_JukeboxTrack
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_JukeboxTrack(JukeboxTrack* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->sequenceId = v; }
    /* name: pointer, set by the array's fixups */
}

#endif
static JukeboxTrack _gMistShootingGalleryJukeboxRegularNightmareTracks[4];
static void peDecodeArr_gMistShootingGalleryJukeboxRegularNightmareTracks(void* base, const unsigned char* src, size_t n)
{
    JukeboxTrack* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_JukeboxTrack(&dst[k], src + k * 8);
    dst[0].name = (void*)&_gMistShootingGalleryJukeboxRow1ManMadeNatureLabel;
    dst[1].name = (void*)&_gMistShootingGalleryJukeboxRow2GazingIntoTheVoidLabel;
    dst[2].name = (void*)&_gMistShootingGalleryJukeboxRow3FoolsParadiseLabel;
    dst[3].name = (void*)&_gMistShootingGalleryJukeboxRow4KillingFieldLabel;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryJukeboxRegularNightmareTracks", _gMistShootingGalleryJukeboxRegularNightmareTracks, peDecodeArr_gMistShootingGalleryJukeboxRegularNightmareTracks);
#ifndef PE_DECODE_JukeboxTrack
#define PE_DECODE_JukeboxTrack
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_JukeboxTrack(JukeboxTrack* dst, const unsigned char* src)
{
    { int32_t v; memcpy(&v, src + 0, 4); dst->sequenceId = v; }
    /* name: pointer, set by the array's fixups */
}

#endif
static JukeboxTrack _gMistShootingGalleryJukeboxRegularUnclearedTracks[4];
static void peDecodeArr_gMistShootingGalleryJukeboxRegularUnclearedTracks(void* base, const unsigned char* src, size_t n)
{
    JukeboxTrack* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_JukeboxTrack(&dst[k], src + k * 8);
    dst[0].name = (void*)&_gMistShootingGalleryJukeboxRow1TowerRendezvousLabel;
    dst[1].name = (void*)&_gMistShootingGalleryJukeboxRow2TheVagrantsLabel;
    dst[2].name = (void*)&_gMistShootingGalleryJukeboxRow3OutOfPhase2Label;
    dst[3].name = (void*)&_gMistShootingGalleryJukeboxRow4LazingAwayTheMorningLabel;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gMistShootingGalleryJukeboxRegularUnclearedTracks", _gMistShootingGalleryJukeboxRegularUnclearedTracks, peDecodeArr_gMistShootingGalleryJukeboxRegularUnclearedTracks);
