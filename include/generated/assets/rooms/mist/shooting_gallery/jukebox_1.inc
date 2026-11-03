/* rooms/mist/shooting_gallery/package: written from its room instance by tools/buildsteps/gen_room_inc.py. */

#include "rooms/rooms_shared_8018055c.h"

#ifndef PE_DECODE_JukeboxTrackLists
#define PE_DECODE_JukeboxTrackLists
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static void peDecode_JukeboxTrackLists(JukeboxTrackLists* dst, const unsigned char* src)
{
    /* lists[0]: pointer, set by the array's fixups */
    /* lists[1]: pointer, set by the array's fixups */
    /* lists[2]: pointer, set by the array's fixups */
    /* lists[3]: pointer, set by the array's fixups */
    /* lists[4]: pointer, set by the array's fixups */
    /* lists[5]: pointer, set by the array's fixups */
    /* lists[6]: pointer, set by the array's fixups */
    /* lists[7]: pointer, set by the array's fixups */
    /* lists[8]: pointer, set by the array's fixups */
    /* lists[9]: pointer, set by the array's fixups */
}

#endif
static JukeboxTrackLists _gJukeboxTrackLists;
static void peDecodeArr_gJukeboxTrackLists(void* base, const unsigned char* src, size_t n)
{
    JukeboxTrackLists* dst = base;
    for (size_t k = 0; k < n; k++) peDecode_JukeboxTrackLists(&dst[k], src + k * 40);
    dst[0].lists[0] = _gMistShootingGalleryJukeboxTrainingReplayTracks;
    dst[0].lists[1] = _gMistShootingGalleryJukeboxTrainingBountyTracks;
    dst[0].lists[2] = _gMistShootingGalleryJukeboxTrainingScavengerTracks;
    dst[0].lists[3] = _gMistShootingGalleryJukeboxTrainingNightmareTracks;
    dst[0].lists[4] = _gMistShootingGalleryJukeboxTrainingUnclearedTracks;
    dst[0].lists[5] = _gMistShootingGalleryJukeboxRegularReplayTracks;
    dst[0].lists[6] = _gMistShootingGalleryJukeboxRegularBountyTracks;
    dst[0].lists[7] = _gMistShootingGalleryJukeboxRegularScavengerTracks;
    dst[0].lists[8] = _gMistShootingGalleryJukeboxRegularNightmareTracks;
    dst[0].lists[9] = _gMistShootingGalleryJukeboxRegularUnclearedTracks;
}
#include "port/asset_bind.h"
PE_ASSET_BIND_DECODE("room/mist_shooting_gallery/_gJukeboxTrackLists", _gJukeboxTrackLists, peDecodeArr_gJukeboxTrackLists);
