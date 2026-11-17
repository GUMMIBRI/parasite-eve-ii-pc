/* MPL-2.0. Native PE2 QoL host preferences; separate from retail pad bindings. */
#ifndef PE_QOL_PREFERENCES_H
#define PE_QOL_PREFERENCES_H
#include "port/qol_controls.h"
static int qolKey=-1,qolButton=-1,qolFactor=2,qolKeyHeld,qolKeyBlocked,qolPadReleaseRequired;
static unsigned qolConfirm;
static int qolYes;
static unsigned qolPendingAction;
typedef struct { SDL_JoystickID id;int held,blocked; } QolPadHold;
static QolPadHold qolPads[16];
static int QolReservedKey(int key) {return key==SDL_SCANCODE_ESCAPE||key<=SDL_SCANCODE_UNKNOWN||key>=SDL_SCANCODE_COUNT;}
static int QolReservedButton(int b) {return b==SDL_GAMEPAD_BUTTON_START||b==SDL_GAMEPAD_BUTTON_LEFT_STICK||b==SDL_GAMEPAD_BUTTON_RIGHT_STICK||b<0||b>=SDL_GAMEPAD_BUTTON_COUNT;}
static void QolPublishHeld(void) {
 int held=qolKeyHeld;for(unsigned i=0;i<16;i++)held|=qolPads[i].held;
 peQolSetSpeedHeld(held,(unsigned)qolFactor);
}
/* Keep down controls inhibited across modal/focus/remap until their own release.
 * Queries only the live input backend; no synthetic events/buttons. */
static void QolClearHold(void) {
 QolPadHold previous[16];memcpy(previous,qolPads,sizeof(previous));
 qolKeyBlocked|=qolKeyHeld;qolKeyHeld=0;memset(qolPads,0,sizeof(qolPads));
 const bool *keys=SDL_GetKeyboardState(NULL);
 qolKeyBlocked|=qolKey>=0&&keys&&keys[qolKey];
 int count=0;SDL_JoystickID *ids=SDL_GetGamepads(&count);
 for(int i=0;ids&&i<count&&i<16;i++) {
  SDL_Gamepad *pad=SDL_GetGamepadFromID(ids[i]);
  qolPads[i].id=ids[i];
  qolPads[i].blocked=qolPadReleaseRequired||(qolButton>=0&&pad&&SDL_GetGamepadButton(pad,(SDL_GamepadButton)qolButton));
  for(unsigned j=0;j<16;j++)if(previous[j].id==ids[i])qolPads[i].blocked|=previous[j].held||previous[j].blocked;
 }
 SDL_free(ids);peQolSetSpeedHeld(0,(unsigned)qolFactor);Psyz_VideoSetSpeed(1);
}
static void QolSave(FILE *f) {
 fprintf(f,"qol_speed_key=%d\nqol_speed_button=%d\nqol_speed_factor=%d\n",qolKey,qolButton,qolFactor);
}
static int QolLoad(const char *name,long value) {
 if(!strcmp(name,"qol_speed_key")) {if(value==-1||(value>0&&value<SDL_SCANCODE_COUNT&&!QolReservedKey((int)value)))qolKey=(int)value;return 1;}
 if(!strcmp(name,"qol_speed_button")) {if(value==-1||(value>=0&&value<SDL_GAMEPAD_BUTTON_COUNT&&!QolReservedButton((int)value)))qolButton=(int)value;return 1;}
 if(!strcmp(name,"qol_speed_factor")) {if(value>=2&&value<=4)qolFactor=(int)value;return 1;}
 return 0;
}
static bool QolSpeedEvent(const SDL_Event *e,int blocked) {
 if(e->type==SDL_EVENT_WINDOW_FOCUS_LOST||e->type==SDL_EVENT_GAMEPAD_REMOVED) {QolClearHold();qolKeyBlocked=1;qolPadReleaseRequired=1;for(unsigned i=0;i<16;i++)qolPads[i].blocked=1;return false;}
 if(e->type==SDL_EVENT_KEY_DOWN||e->type==SDL_EVENT_KEY_UP) {
  if(qolKey<0||(int)e->key.scancode!=qolKey)return false;
  if(e->type==SDL_EVENT_KEY_UP){qolKeyHeld=0;qolKeyBlocked=0;}
  else if(!e->key.repeat) {if(blocked)qolKeyBlocked=1;qolKeyHeld=!blocked&&!qolKeyBlocked;}
  QolPublishHeld();return !blocked;
 }
 if(e->type==SDL_EVENT_GAMEPAD_BUTTON_DOWN||e->type==SDL_EVENT_GAMEPAD_BUTTON_UP) {
  if(qolButton<0||e->gbutton.button!=qolButton)return false;
  unsigned slot;for(slot=0;slot<16;slot++)if(qolPads[slot].id==e->gbutton.which)break;
  if(slot==16)for(slot=0;slot<16;slot++)if(!qolPads[slot].id){qolPads[slot].id=e->gbutton.which;qolPads[slot].blocked=qolPadReleaseRequired;break;}
  if(slot<16) {
   if(e->type==SDL_EVENT_GAMEPAD_BUTTON_UP){qolPads[slot].held=0;qolPads[slot].blocked=0;}
   else {if(blocked)qolPads[slot].blocked=1;qolPads[slot].held=!blocked&&!qolPads[slot].blocked;}
   QolPublishHeld();
  }
  return !blocked;
 }
 return false;
}
static void QolPaintConfirm(OverlaySurface *surface,float s) {
 FillRoundRect(surface,0,0,680*s,surface->h-1,16*s,kPanel);
 const int exitGame=qolConfirm==PE_QOL_EXIT_GAME_CONFIRMED;
 DrawText(surface,32*s,70*s,25*s,exitGame?"Exit Game?":"Return to Title?",kText,ALIGN_LEFT);
 DrawText(surface,32*s,120*s,17*s,"Unsaved progress will be lost.",kMuted,ALIGN_LEFT);
 DrawText(surface,180*s,220*s,22*s,"Cancel",!qolYes?kAccent:kMuted,ALIGN_CENTRE);
 DrawText(surface,500*s,220*s,22*s,exitGame?"Yes, exit":"Yes, return",qolYes?kAccent:kMuted,ALIGN_CENTRE);
 DrawText(surface,32*s,290*s,14*s,"Left / Right: choose   Enter / South: confirm",kMuted,ALIGN_LEFT);
 DrawText(surface,32*s,320*s,14*s,"Esc / East / Start: cancel",kMuted,ALIGN_LEFT);
 surface->pixels[((size_t)surface->h*surface->w-1)*4+3]=255;
}
#endif
