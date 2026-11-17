/* MPL-2.0. Authored PE2 adapter; policy reviewed against PE1 Build17.
 * No PE1 state IDs, event shortcuts or synthetic game button presses. */
#include "port/qol_controls.h"
#if defined(PE2_PS5_HOST)
#include <stdatomic.h>
#include <psyz/video.h>
#include <SDL3/SDL_log.h>
static atomic_uint requests, heldSpeed, uiBlocked;
static unsigned frameSkip;
static atomic_uint confirmedWait;
static unsigned appliedSpeed=1;
static void setSpeed(unsigned speed) {
 if(appliedSpeed!=speed||Psyz_VideoGetSpeed()!=speed) {
  if(Psyz_VideoSetSpeed(speed)==0)appliedSpeed=speed;
 }
}
void peQolRequest(unsigned action) {
 if(action==PE_QOL_SKIP||action==PE_QOL_PAUSE_TOGGLE||action==PE_QOL_RETURN_TITLE_CONFIRMED||action==PE_QOL_EXIT_GAME_CONFIRMED)
  { atomic_fetch_or(&requests,action); if(action & (PE_QOL_RETURN_TITLE_CONFIRMED|PE_QOL_EXIT_GAME_CONFIRMED)) atomic_store(&confirmedWait,120); }
}
void peQolSetSpeedHeld(int held,unsigned factor) {
 /* Invalid preferences fail closed; no sticky acceleration on malformed UI. */
 atomic_store(&heldSpeed,held&&factor>=2&&factor<=4&&!atomic_load(&uiBlocked)?factor:0);
}
void peQolSetUiBlocked(int blocked) {
 atomic_store(&uiBlocked,!!blocked);
 if(blocked){atomic_store(&heldSpeed,0);atomic_store(&requests,0);atomic_store(&confirmedWait,0);}
}
void peQolReset(void) {
 atomic_store(&requests,0);atomic_store(&heldSpeed,0);frameSkip=0;atomic_store(&confirmedWait,0);setSpeed(1);
}
unsigned peQolPoll(unsigned allowedActions,int speedAllowed) {
 unsigned pending=atomic_load(&requests), action, retained, speed=atomic_load(&heldSpeed);
 frameSkip=0;
 if(atomic_load(&uiBlocked)) {allowedActions=0;speed=0;}
 do {
  action=pending & allowedActions;
  /* Confirmed destructive actions wait until the game loop is safe. Skip and
   * pause inputs are transient and must not fire in a later scene. */
  retained=pending & (PE_QOL_RETURN_TITLE_CONFIRMED|PE_QOL_EXIT_GAME_CONFIRMED) & ~allowedActions;
  if(retained && atomic_load(&confirmedWait)==1)retained=0;
 } while(!atomic_compare_exchange_weak(&requests,&pending,retained));
 if(retained && atomic_load(&confirmedWait)) atomic_fetch_sub(&confirmedWait,1);
 if((pending & (PE_QOL_RETURN_TITLE_CONFIRMED|PE_QOL_EXIT_GAME_CONFIRMED)) && !action && !retained) {
  SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,"PE2 pause action cancelled: game remained busy");
  atomic_store(&confirmedWait,0);
 }
 if(action & (PE_QOL_RETURN_TITLE_CONFIRMED|PE_QOL_EXIT_GAME_CONFIRMED))atomic_store(&confirmedWait,0);
 if(!speedAllowed||(action&(PE_QOL_PAUSE_TOGGLE|PE_QOL_RETURN_TITLE_CONFIRMED|PE_QOL_EXIT_GAME_CONFIRMED))) {speed=0;atomic_store(&heldSpeed,0);}
 setSpeed(speed?speed:1);
 if(action&PE_QOL_EXIT_GAME_CONFIRMED)return PE_QOL_EXIT_GAME_CONFIRMED;
 if(action&PE_QOL_RETURN_TITLE_CONFIRMED)return PE_QOL_RETURN_TITLE_CONFIRMED;
 frameSkip=!!(action&PE_QOL_SKIP);
 return action&PE_QOL_PAUSE_TOGGLE;
}
int peQolTakeSkip(void) {unsigned skip=frameSkip;frameSkip=0;return !!skip;}
#endif
