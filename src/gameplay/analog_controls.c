/* MPL-2.0. Original PE2 direct-stick adapter. The PE1 field input policy supplied
 * radial run-threshold behavior; no PE1 actor/state layout is imported. */
#ifdef PE2_PS5_HOST
#include "port/analog_controls.h"
#include <psyz.h>
/* The decomp common header owns the game assertion macro in host game TUs. */
#undef STATIC_ASSERT
#include "common.h"
#include "gameplay/area_entry.h"
#include "gameplay/attachments.h"
#include "gameplay/player_actor.h"
#include "main/display.h"
#include "main/game_debug.h"
#include "main/gfx.h"
#include "main/mc.h"
#include "main/pad.h"
#include "main/session.h"
#include "main/wipsys.h"
#include "../main/pad.h"
#include <libgte.h>
#include <string.h>

enum { ANALOG_DIRECTIONS = PAD_BUTTON_UP|PAD_BUTTON_DOWN|PAD_BUTTON_LEFT|PAD_BUTTON_RIGHT,
       ANALOG_RAW_RADIUS = 127, ANALOG_DEAD_ZONE = 25 };
static int analog_direct = 1;
static int always_run;
static unsigned analog_run_percent = 85;
static const Task *analog_owner;
static unsigned analog_location;
static unsigned char analog_warp;
static int analog_armed, analog_reference_valid, analog_pending;
static SVECTOR analog_right, analog_down;
static s16 analog_yaw;

static void PeAnalogRelease(void)
{
    analog_reference_valid = analog_pending = analog_armed = 0;
}

int peAnalogControlsMode(void) { return analog_direct; }
void peAnalogControlsSetMode(int direct)
{
    if (analog_direct != !!direct) PeAnalogRelease();
    analog_direct = !!direct;
}
int peAlwaysRun(void) { return always_run; }
void peAlwaysRunSet(int enabled) { always_run = !!enabled; }
unsigned peAnalogRunThreshold(void) { return analog_run_percent; }
void peAnalogSetRunThreshold(unsigned percent)
{
    if (percent >= 50 && percent <= 100) analog_run_percent = percent;
}

static int PeAnalogEligible(const Task *task)
{
    if (!task || task != gPlayerActorTasks[PLAYER_ACTOR_TASK_PLAYER] ||
        !task->work || !task->extra.tmd || !task->extra.tmd->coords ||
        !gGameSession || !gGameDebugState) return 0;
    const GameActor *actor = task->work;
    return actor->mode == GAME_ACTOR_MODE_NORMAL && actor->state == 0 &&
        !(peAnalogInputSuppressionMask() & (ANALOG_DIRECTIONS|PAD_BUTTON_CROSS)) &&
        (unsigned)gMcSaveData[MEMORY_CARD_SAVE_LIVE].state.buttonLayout <= MEMORY_CARD_OPTION_BUTTON_LAYOUT_C &&
        gGameSession->location.stage >= 1 && gGameSession->location.stage <= 5 &&
        gGameSession->location.area && gGameSession->location.roomState && gGameSession->location.view &&
        !actor->movementInputDisabled && !gPadStates[0].inputBlockPolls &&
        !gGameSession->eventState && !gGameSession->cutsceneHold && !gGameSession->uiOpen &&
        gGameSession->viewReady && !gGameSession->viewDirty && !gGameSession->deathVariant &&
        gDisplayState.demoScene == DISPLAY_DEMO_NONE && gDisplayState.pendingMode == DISPLAY_MODE_NONE &&
        gGameDebugState->inputOverrideMode == 0 && gPlayerStatus.hp > 0 &&
        !(gPlayerStatus.statusFlags & PLAYER_STATUS_CONFUSION);
}

static int PeAnalogCameraBasis(void)
{
    /* gGfxViewRotCoord is the actual world-to-view rotation. Invert its XZ
     * projection; normalize each basis to remove camera pitch foreshortening.
     * Flat/horizon cameras use the inverse camera depth direction instead. */
    const MATRIX *view = &gGfxViewRotCoord.coord;
    int a=view->m[0][0], b=view->m[0][2], c=view->m[1][0], d=view->m[1][2];
    if (a < -8192 || a > 8192 || b < -8192 || b > 8192 ||
        c < -8192 || c > 8192 || d < -8192 || d > 8192 ||
        view->m[2][0] < -8192 || view->m[2][0] > 8192 ||
        view->m[2][2] < -8192 || view->m[2][2] > 8192) return 0;
    long long determinant=(long long)a*d-(long long)b*c;
    SVECTOR right={0}, down={0};
    if (determinant > 16384 || determinant < -16384) {
        int sign=determinant < 0 ? -1 : 1;
        if (a == -32768 || b == -32768 || c == -32768 || d == -32768) return 0;
        right.vx=(s16)(d*sign); right.vz=(s16)(-c*sign);
        down.vx=(s16)(-b*sign); down.vz=(s16)(a*sign);
    } else {
        if (view->m[2][0] == -32768 || view->m[2][2] == -32768) return 0;
        right.vx=(s16)a; right.vz=(s16)b;
        down.vx=(s16)-view->m[2][0]; down.vz=(s16)-view->m[2][2];
    }
    if ((!right.vx && !right.vz) || (!down.vx && !down.vz)) return 0;
    VectorNormalSS(&right,&analog_right);
    VectorNormalSS(&down,&analog_down);
    analog_reference_valid=1;
    return 1;
}

static void PeAnalogPublishActorInput(GameActor *actor, u16 directions, int modifier)
{
    actor->padHeld=(actor->padHeld & ~(ANALOG_DIRECTIONS|PAD_BUTTON_CROSS)) |
        directions | (modifier ? PAD_BUTTON_CROSS : 0);
    actor->padPressed=actor->padHeld & ~actor->previousPadHeld;
    actor->padReleased=actor->previousPadHeld & ~actor->padHeld;
    actor->runButtonHeld=modifier != 0;
    actor->movementSign=(directions & PAD_BUTTON_DOWN) ? -1 : (directions & PAD_BUTTON_UP) ? 1 : 0;
    actor->turnSign=(directions & PAD_BUTTON_LEFT) ? -1 : (directions & PAD_BUTTON_RIGHT) ? 1 : 0;
}

void peAnalogUpdateNormalInput(Task *task)
{
    if (!task || task != gPlayerActorTasks[PLAYER_ACTOR_TASK_PLAYER]) return;
    analog_pending=0;
    if (!PeAnalogEligible(task)) { PeAnalogRelease(); return; }
    GameActor *actor=task->work;
    int walk_default=gMcSaveData[MEMORY_CARD_SAVE_LIVE].state.moveMode == MEMORY_CARD_OPTION_MOVEMENT_WALK;
    int run_policy=always_run && !(actor->padHeld & PAD_BUTTON_SQUARE) &&
        gAttachmentState.effectPhase == ATTACHMENT_EFFECT_IDLE;
    if (run_policy && actor->movementSign == 1) {
        /* Only logical run input changes. Original locomotion still owns run
         * eligibility, clips, collisions, backwards walk and movement rates. */
        int held_walk=(actor->padHeld & PAD_BUTTON_CROSS) != 0;
        int modifier=walk_default ? !held_walk : held_walk;
        actor->padHeld=(actor->padHeld & ~PAD_BUTTON_CROSS) | (modifier ? PAD_BUTTON_CROSS : 0);
        actor->padPressed=actor->padHeld & ~actor->previousPadHeld;
        actor->padReleased=actor->previousPadHeld & ~actor->padHeld;
        actor->runButtonHeld=modifier;
    }
    if (!analog_direct) { PeAnalogRelease(); return; }
    const PadRawPort *raw=&gPadRawPorts[0];
    /* Read the real registered receive buffer, after the existing pad override.
     * A disconnected/digital/replayed frame never supplies invented axes. */
    if (raw->status || raw->controllerId != PAD_INPUT_FORMAT_ANALOG) {
        PeAnalogRelease(); return;
    }
    unsigned location=(unsigned)gGameSession->location.stage<<24 |
        (unsigned)gGameSession->location.area<<16 |
        (unsigned)gGameSession->location.roomState<<8 | gGameSession->location.variant;
    if (analog_owner != task || analog_location != location || analog_warp != gGameSession->location.warp) {
        PeAnalogRelease();
        analog_owner=task; analog_location=location; analog_warp=gGameSession->location.warp;
    }
    u16 physical=(u16)~((unsigned)raw->buttonsHigh<<8 | raw->buttonsLow);
    int physical_modifier=(physical & (gMcSaveData[MEMORY_CARD_SAVE_LIVE].state.buttonLayout == MEMORY_CARD_OPTION_BUTTON_LAYOUT_B ? PAD_BUTTON_SQUARE : PAD_BUTTON_CIRCLE)) != 0;
    int digital_modifier=run_policy && (physical & PAD_BUTTON_UP) && !(physical & PAD_BUTTON_DOWN)
        ? (walk_default ? !physical_modifier : physical_modifier) : physical_modifier;
    if (physical & ANALOG_DIRECTIONS) {
        /* Physical D-pad/keyboard wins over the stick, retaining tank controls. */
        analog_reference_valid=0; analog_armed=1;
        PeAnalogPublishActorInput(actor,physical & ANALOG_DIRECTIONS,digital_modifier);
        return;
    }
    int x=(int)raw->stickAxes[PAD_STICK_LEFT_X]-128;
    int y=(int)raw->stickAxes[PAD_STICK_LEFT_Y]-128;
    if (x < -ANALOG_RAW_RADIUS) x=-ANALOG_RAW_RADIUS;
    if (y < -ANALOG_RAW_RADIUS) y=-ANALOG_RAW_RADIUS;
    unsigned radius2=(unsigned)(x*x+y*y);
    if (radius2 <= ANALOG_DEAD_ZONE*ANALOG_DEAD_ZONE) {
        analog_reference_valid=0; analog_armed=1;
        PeAnalogPublishActorInput(actor,0,physical_modifier);
        return;
    }
    if (!analog_armed) {
        /* A room, task, script or menu unlock requires a neutral stick first. */
        PeAnalogPublishActorInput(actor,0,physical_modifier);
        return;
    }
    if (!analog_reference_valid && !PeAnalogCameraBasis()) return;
    int world_x=analog_right.vx*x+analog_down.vx*y;
    int world_z=analog_right.vz*x+analog_down.vz*y;
    if (!world_x && !world_z) { PeAnalogPublishActorInput(actor,0,physical_modifier); return; }
    analog_yaw=(s16)(ratan2(world_x,world_z) & 4095);
    int run=radius2*10000u >= 127u*127u*analog_run_percent*analog_run_percent;
    /* With Always run off, retain the original radial/saved-option policy. */
    if (run_policy) run=!physical_modifier;
    else if (physical_modifier) run=walk_default;
    int logical_modifier=walk_default ? run : !run;
    PeAnalogPublishActorInput(actor,PAD_BUTTON_UP,logical_modifier);
    analog_pending=1;
}

int peAnalogApplyNormalFacing(Task *task)
{
    if (task != analog_owner || !analog_pending) return 0;
    analog_pending=0;
    if (!PeAnalogEligible(task)) { PeAnalogRelease(); return 0; }
    GameActor *actor=task->work;
    if (actor->movementSign != 1) return 0;
    actor->rotation.vy=analog_yaw;
    return 1;
}
#endif
