#include "gameplay/actor_render.h"

#include <psyz.h>
#include <libgte.h>
#include <libgte.h>
#include <libgte.h>

#include "common.h"
#include "gte.h"

#include "actor_render.h"
#include "gameplay/hud_sprites.h"
#include "gameplay/model_objects.h"
#include "model_objects.h"

#include "main/gfx.h"
#include "main/tmd.h"

#if defined(PE2_PS5_HOST)
#include <stdint.h>
#include <string.h>

/* Presentation-only companion to the ORIGINAL composition below. No pointer
 * in this bounded cache is dereferenced: live callers provide all snapshots.
 * Reset after the listed-model draw boundary; collisions lose precision,
 * never original geometry. Explicit compositions may also populate this pass.
 */
enum { ACTOR_PGXP_COORD_SLOTS = 512 };
typedef struct {
    const GfxCoord* owner;
    const GfxCoord* parent;
    MATRIX local;
    MATRIX result;
    double rot[3][3];
    double trans[3];
} ActorPgxpCoord;
static ActorPgxpCoord actorPgxpCoords[ACTOR_PGXP_COORD_SLOTS];

static ActorPgxpCoord* actorPgxpSlot(const GfxCoord* coord)
{
    return &actorPgxpCoords[((uintptr_t)coord >> 4) % ACTOR_PGXP_COORD_SLOTS];
}

static int actorPgxpSnapshotMatches(const ActorPgxpCoord* entry, const GfxCoord* coord)
{
    return entry->owner == coord && entry->parent == coord->parent &&
           memcmp(&entry->local, &coord->coord, sizeof(MATRIX)) == 0 &&
           memcmp(&entry->result, &coord->workm, sizeof(MATRIX)) == 0;
}

static void actorPgxpReadInteger(const MATRIX* matrix, double rot[3][3], double trans[3])
{
    for (int i = 0; i < 3; ++i) {
        trans[i] = matrix->t[i];
        for (int j = 0; j < 3; ++j)
            rot[i][j] = matrix->m[i][j] / 4096.0;
    }
}

/* Called only AFTER the integer owner has really rebuilt its result. Parent
 * precision is optional; a cache miss uses its current integer workm. This
 * still recovers this composition's discarded fractions without inventing
 * earlier authored precision. Local matrices remain the game's exact inputs.
 */
void actorRenderRecordPgxpCoord(const GfxCoord* coord, const GfxCoord* parent)
{
    ActorPgxpCoord value = {0};
    double localRot[3][3], localTrans[3];
    actorPgxpReadInteger(&coord->coord, localRot, localTrans);
    if (parent == NULL) {
        memcpy(value.rot, localRot, sizeof(value.rot));
        memcpy(value.trans, localTrans, sizeof(value.trans));
    } else {
        double parentRot[3][3], parentTrans[3];
        const ActorPgxpCoord* cached = actorPgxpSlot(parent);
        if (actorPgxpSnapshotMatches(cached, parent)) {
            memcpy(parentRot, cached->rot, sizeof(parentRot));
            memcpy(parentTrans, cached->trans, sizeof(parentTrans));
        } else {
            actorPgxpReadInteger(&parent->workm, parentRot, parentTrans);
        }
        for (int i = 0; i < 3; ++i) {
            value.trans[i] = parentTrans[i];
            for (int k = 0; k < 3; ++k)
                value.trans[i] += parentRot[i][k] * localTrans[k];
            for (int j = 0; j < 3; ++j)
                for (int k = 0; k < 3; ++k)
                    value.rot[i][j] += parentRot[i][k] * localRot[k][j];
        }
    }
    /* GTE overflow/saturation cannot be reconstructed by an unbounded affine
     * product. Abandon this companion when the authored integer domain or a
     * finite representable result is exceeded. Never touch integer gameplay.
     */
    for (int i = 0; i < 3; ++i) {
        if (!__builtin_isfinite(value.trans[i]) || value.trans[i] < -2147483648.0 || value.trans[i] > 2147483647.0)
            goto invalid;
        for (int j = 0; j < 3; ++j) {
            double fixed = value.rot[i][j] * 4096.0;
            if (!__builtin_isfinite(fixed) || fixed <= -32768.0 || fixed >= 32767.0)
                goto invalid;
        }
    }
    value.owner = coord;
    value.parent = coord->parent;
    value.local = coord->coord;
    value.result = coord->workm;
    *actorPgxpSlot(coord) = value;
    return;
invalid:
    actorPgxpSlot(coord)->owner = NULL;
}

/* Private host bridge; unchanged public/original structs and console API. */
int actorRenderGetPgxpPartMatrix(const GfxCoord* coord, double rot[3][3], double trans[3])
{
    const ActorPgxpCoord* cached = actorPgxpSlot(coord);
    if (!actorPgxpSnapshotMatches(cached, coord))
        return 0;
    memcpy(rot, cached->rot, sizeof(cached->rot));
    memcpy(trans, cached->trans, sizeof(cached->trans));
    return 1;
}
#endif

static inline void _actorRenderRefreshCoord(GfxCoord* coord, s32 stamp, s32 parity, GfxCoord* root);

/// Selects the pass-counter parity stored in bit 31 of each visited coordinate's stamp.
enum { ACTOR_RENDER_COORD_PASS_PARITY_MASK = 1 };

/// Last node explicitly submitted for composition through its full parent chain.
///
/// Initially NULL; updates with an excluded ancestor leave this snapshot alone.
/// No game code reads it. The pointer is borrowed and may outlive its node.
static GfxCoord* _gActorRenderLastFullChainCoord = NULL;

/// Visits a coordinate after its ancestors and refreshes its composed matrix when stale.
///
/// The supplied root is excluded. `gte_RotTransLV` preserves the full signed
/// translation range while the rotation is composed with the GTE.
static inline void _actorRenderRefreshCoord(GfxCoord* coord, s32 stamp, s32 parity, GfxCoord* root)
{
    GfxCoord* parent;

    // Apply GRAPHICS_COORD_STAMP_MASK with shifts to avoid a hoisted mask register.
    parent              = coord->parent;
    coord->composeStamp = (coord->composeStamp << 1) >> 1;
    if (parent == root) {
        if (coord->composeStamp == GRAPHICS_COORD_DIRTY) {
            coord->workm        = coord->coord;
            coord->composeStamp = stamp;
#if defined(PE2_PS5_HOST)
            actorRenderRecordPgxpCoord(coord, NULL);
#endif
        }
    } else {
        if ((parent->composeStamp == GRAPHICS_COORD_DIRTY) || ((parent->composeStamp >> 31) != parity)) {
            actorRenderComposeCoordChain(parent, stamp, parity, root);
        }
        if (coord->composeStamp < (parent->composeStamp & GRAPHICS_COORD_STAMP_MASK)) {
            gte_CompMatrix(&parent->workm, &coord->coord, &coord->workm);
            coord->composeStamp = stamp;
            gte_SetRotMatrix(&parent->workm);
            gte_ldclmv(&coord->coord.m[0][0]);
            gte_rtir();
            gte_stclmv(&coord->workm.m[0][0]);
            gte_ldclmv(&coord->coord.m[0][1]);
            gte_rtir();
            coord->composeStamp = stamp;
            gte_stclmv(&coord->workm.m[0][1]);
            gte_ldclmv(&coord->coord.m[0][2]);
            gte_rtir();
            gte_SetTransVector(parent->workm.t);
            gte_stclmv(&coord->workm.m[0][2]);
            gte_RotTransLV(coord->coord.t, coord->workm.t);
#if defined(PE2_PS5_HOST)
            actorRenderRecordPgxpCoord(coord, parent);
#endif
        }
    }
    if (parity != 0) {
        coord->composeStamp |= GRAPHICS_COORD_VISIT_PARITY_BIT;
    }
}

/// Composes the coordinate-body and model lists, then advances the composition pass.
///
/// Visits every linked body's coordinate and every model's `partCount` nodes,
/// regardless of draw flags, through their complete parent chains. The lists,
/// their borrowed parent nodes and each model's owned coordinate array must
/// stay live and unchanged during the walk. Empty lists still advance the
/// counter. Explicit node compositions before the next list pass use that
/// next pass's stamp and parity; this is a pass boundary, not a frame clock.
static inline void _actorRenderComposeListedCoords(void)
{
    TmdListNode* link;
    GfxCoord*    partCoord;
    s32          rebuildStamp;
    s32          visitParity;
    u32          partIndex;


    rebuildStamp = gActorRenderCoordPassCounter & GRAPHICS_COORD_STAMP_MASK;
    visitParity  = gActorRenderCoordPassCounter & ACTOR_RENDER_COORD_PASS_PARITY_MASK;
    // Both lists share one pass, so common ancestors can reuse their caches.
    for (link = gModelObjectCoordBodyList.next; link != NULL; link = link->next) {
        _actorRenderRefreshCoord(PARENT_OF(link, ModelObjectCoordBody, link)->coord, rebuildStamp, visitParity, NULL);
    }
    for (link = gTmdList.next; link != NULL; link = link->next) {
        partCoord = PARENT_OF(link, TmdObject, link)->coords;
        for (partIndex = 0; partIndex < PARENT_OF(link, TmdObject, link)->partCount; partIndex++) {
            _actorRenderRefreshCoord(partCoord, rebuildStamp, visitParity, NULL);
            partCoord++;
        }
    }
    // Advance only after both lists have used the same rebuild stamp and parity.
    gActorRenderCoordPassCounter += 1;
}

void actorRenderComposeAndDrawFlaggedModels(GsOT* unusedOt)
{
    // Compose both lists before drawing, including models omitted from this pass.
    _actorRenderComposeListedCoords();
    tmdDrawFlaggedModels(PARENT_OF(gTmdList.next, TmdObject, link));
#if defined(PE2_PS5_HOST)
    memset(actorPgxpCoords, 0, sizeof(actorPgxpCoords));
#endif
}

void actorRenderComposeAndDrawActiveModels(GsOT* unusedOt)
{
    // Compose both lists before drawing, including hidden and unbuffered models.
    _actorRenderComposeListedCoords();
    tmdDrawActiveModels(PARENT_OF(gTmdList.next, TmdObject, link));
#if defined(PE2_PS5_HOST)
    memset(actorPgxpCoords, 0, sizeof(actorPgxpCoords));
#endif
}

void actorRenderComposeCoord(GfxCoord* coord)
{
    _gActorRenderLastFullChainCoord = coord;
    actorRenderComposeCoordChain(coord, gActorRenderCoordPassCounter & GRAPHICS_COORD_STAMP_MASK,
                                 gActorRenderCoordPassCounter & ACTOR_RENDER_COORD_PASS_PARITY_MASK, NULL);
}

void actorRenderComposeCoordRelative(GfxCoord* coord, GfxCoord* excludedAncestor)
{
    if (coord->parent == NULL) {
        // Keep the composed cache while rebasing only the detached node's local matrix.
        _gActorRenderLastFullChainCoord = coord;
        actorRenderComposeCoordChain(coord, gActorRenderCoordPassCounter & GRAPHICS_COORD_STAMP_MASK,
                                     gActorRenderCoordPassCounter & ACTOR_RENDER_COORD_PASS_PARITY_MASK, NULL);
        gfxMakeRelativeTransform(&gGfxViewCoord.workm, &coord->workm, &coord->coord);
    } else {
        actorRenderComposeCoordChain(coord, gActorRenderCoordPassCounter & GRAPHICS_COORD_STAMP_MASK,
                                     gActorRenderCoordPassCounter & ACTOR_RENDER_COORD_PASS_PARITY_MASK, excludedAncestor);
    }
}
