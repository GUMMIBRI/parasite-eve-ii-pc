/* MPL-2.0. Actual SDL gamepad bindings; native PS1 bit identity stays0..15. */
#ifndef PE_GAMEPAD_BINDINGS_UI_H
#define PE_GAMEPAD_BINDINGS_UI_H
static const char *const pe_pad_names[16]={"L2","R2","L1","R1","Triangle","Circle","Cross","Square","Select","L3","R3","Start","Up","Right","Down","Left"};
static int pe_pad_defaults[16],pe_pad_loaded[16],pe_pad_seen,pe_pad_invalid,pe_pad_ready;
typedef struct {SDL_JoystickID id;unsigned armed;} PePadTriggerCapture;
static PePadTriggerCapture pe_pad_triggers[16];
static const char *PePadBitName(unsigned bit){return bit<16?pe_pad_names[bit]:"Unknown";}
static int PePadLocked(unsigned bit){return bit==9||bit==10||bit==11;}
static int PePadReservedPhysical(int binding){return binding==SDL_GAMEPAD_BUTTON_LEFT_STICK||binding==SDL_GAMEPAD_BUTTON_RIGHT_STICK||binding==SDL_GAMEPAD_BUTTON_START;}
static void PePadInitDefaults(void){
 if(pe_pad_ready)return;
 for(unsigned i=0;i<16;i++)pe_pad_loaded[i]=pe_pad_defaults[i]=Psyz_GetGamepadBinding_SDL3(i);
 pe_pad_ready=1;
}
static void PePadBeginLoad(void){
 PePadInitDefaults();pe_pad_seen=pe_pad_invalid=0;
 for(unsigned i=0;i<16;i++)pe_pad_loaded[i]=pe_pad_defaults[i];
}
static const char *PePadBindingName(int binding){
 if(binding<0)return "Unbound";
 if(binding==SDL_GAMEPAD_BUTTON_COUNT)return "Left trigger";
 if(binding==SDL_GAMEPAD_BUTTON_COUNT+1)return "Right trigger";
 const char *name=SDL_GetGamepadStringForButton((SDL_GamepadButton)binding);return name?name:"Unknown";
}
static int PePadValidate(const int map[16],int speedCheck){
 for(unsigned i=0;i<16;i++){
  int value=map[i];if(value< -1||value>SDL_GAMEPAD_BUTTON_COUNT+1)return 0;
  if(PePadLocked(i)?value!=pe_pad_defaults[i]:PePadReservedPhysical(value))return 0;
  if(speedCheck&&value>=0&&value==qolButton)return 0;
  for(unsigned j=0;j<i;j++)if(value>=0&&value==map[j])return 0;
 }
 return 1;
}
static int PePadApply(const int map[16],int speedCheck){
 if(!PePadValidate(map,speedCheck))return 0;
 int previous[16];for(unsigned i=0;i<16;i++)previous[i]=Psyz_GetGamepadBinding_SDL3(i);
 for(unsigned i=0;i<16;i++)if(Psyz_SetGamepadBinding_SDL3(i,map[i])){
  for(unsigned j=0;j<16;j++)Psyz_SetGamepadBinding_SDL3(j,previous[j]);return 0;
 }
 QolClearHold();Psyz_ResetGamepadHeld_SDL3();return 1;
}
static void PePadWrite(FILE *file){for(unsigned i=0;i<16;i++)fprintf(file,"pad%u=%d\n",i,Psyz_GetGamepadBinding_SDL3(i));}
static int PePadReadField(const char *name,long value){
 if(strncmp(name,"pad",3))return 0;
 char *end;long bit=strtol(name+3,&end,10);if(end==name+3||*end||bit<0||bit>=16)return 0;
 pe_pad_seen=1;
 if(value< -1||value>SDL_GAMEPAD_BUTTON_COUNT+1)pe_pad_invalid=1;else pe_pad_loaded[bit]=(int)value;
 return 1;
}
static void PePadApplyLoaded(void){
 if(pe_pad_seen&&(pe_pad_invalid||!PePadApply(pe_pad_loaded,0))){
  snprintf(statusText,sizeof statusText,"Invalid saved controller profile; original controller defaults retained.");
  fprintf(stderr,"[controls] %s\n",statusText);
 }
}
static void PePadCaptureBegin(void){
 memset(pe_pad_triggers,0,sizeof pe_pad_triggers);
 int count=0;SDL_JoystickID *ids=SDL_GetGamepads(&count);
 for(int i=0;ids&&i<count&&i<16;i++){
  SDL_Gamepad *pad=SDL_GetGamepadFromID(ids[i]);pe_pad_triggers[i].id=ids[i];
  if(pad){if(SDL_GetGamepadAxis(pad,SDL_GAMEPAD_AXIS_LEFT_TRIGGER)<=8000)pe_pad_triggers[i].armed|=1;
   if(SDL_GetGamepadAxis(pad,SDL_GAMEPAD_AXIS_RIGHT_TRIGGER)<=8000)pe_pad_triggers[i].armed|=2;}
 }
 SDL_free(ids);QolClearHold();Psyz_ResetGamepadHeld_SDL3();s_overlayState.capture=1;
 snprintf(statusText,sizeof statusText,"Press a button/trigger. Esc or Start cancels. Delete clears.");
}
static void PePadActivate(int row,int activate){
 if(!activate)return;
 if(row==40){
  if(PePadApply(pe_pad_defaults,1))snprintf(statusText,sizeof statusText,"Original controller defaults restored; keyboard and stick settings kept.");
  else snprintf(statusText,sizeof statusText,"Restore conflicts with speed hold; unbind that controller hold first.");
 }else if(PePadLocked((unsigned)(row-24)))snprintf(statusText,sizeof statusText,"Start and stick clicks are reserved for the Settings shortcut.");
 else PePadCaptureBegin();
}
static int PePadCommit(int binding){
 unsigned target=(unsigned)(s_overlayState.row-24);int map[16];
 if(target>=16||PePadLocked(target))return 0;
 for(unsigned i=0;i<16;i++)map[i]=Psyz_GetGamepadBinding_SDL3(i);
 if(binding>=0&&(PePadReservedPhysical(binding)||binding==qolButton)){
  snprintf(statusText,sizeof statusText,"That control is reserved for Settings or speed hold.");return 0;
 }
 if(binding>=0)for(unsigned i=0;i<16;i++)if(i!=target&&map[i]==binding){
  if(map[target]<0||PePadLocked(i)){snprintf(statusText,sizeof statusText,"Already used by %s; clear or change that row first.",PePadBitName(i));return 0;}
  map[i]=map[target];
 }
 map[target]=binding;
 if(!PePadApply(map,0)){snprintf(statusText,sizeof statusText,"Controller change was rejected; previous bindings kept.");return 0;}
 s_overlayState.capture=0;s_overlayState.dirty=1;
 snprintf(statusText,sizeof statusText,"Controller %s: %s",PePadBitName(target),PePadBindingName(binding));return 1;
}
static void PePadLifecycleEvent(const SDL_Event *event){
 if(event->type==SDL_EVENT_WINDOW_FOCUS_LOST||event->type==SDL_EVENT_WINDOW_FOCUS_GAINED||event->type==SDL_EVENT_GAMEPAD_REMOVED)Psyz_ResetGamepadHeld_SDL3();
}
static int PePadControlEvent(const SDL_Event *event){
 if(s_overlayState.page!=1||s_overlayState.row<24||s_overlayState.row>=40)return 0;
 if(event->type==SDL_EVENT_WINDOW_FOCUS_LOST||event->type==SDL_EVENT_GAMEPAD_REMOVED){
  if(s_overlayState.capture){s_overlayState.capture=0;s_overlayState.dirty=1;snprintf(statusText,sizeof statusText,"Binding cancelled after focus/controller loss.");}return 0;
 }
 if(event->type==SDL_EVENT_KEY_DOWN&&!event->key.repeat){
  if(event->key.scancode==SDL_SCANCODE_DELETE||event->key.scancode==SDL_SCANCODE_BACKSPACE){PePadCommit(-1);return 1;}
  if(s_overlayState.capture){if(event->key.scancode==SDL_SCANCODE_ESCAPE){s_overlayState.capture=0;s_overlayState.dirty=1;}return 1;}
 }
 if(event->type==SDL_EVENT_GAMEPAD_BUTTON_DOWN){
  int binding=event->gbutton.button;
  if(!s_overlayState.capture&&binding==SDL_GAMEPAD_BUTTON_WEST){PePadCommit(-1);return 1;}
  if(s_overlayState.capture){
   if(binding==SDL_GAMEPAD_BUTTON_START){s_overlayState.capture=0;s_overlayState.dirty=1;return 1;}
   if(PePadReservedPhysical(binding)){
    SDL_Gamepad *pad=SDL_GetGamepadFromID(event->gbutton.which);
    if(pad&&SDL_GetGamepadButton(pad,SDL_GAMEPAD_BUTTON_LEFT_STICK)&&SDL_GetGamepadButton(pad,SDL_GAMEPAD_BUTTON_RIGHT_STICK))s_overlayState.capture=0;
    snprintf(statusText,sizeof statusText,"Stick clicks and Start remain reserved for Settings.");s_overlayState.dirty=1;return 1;
   }
   PePadCommit(binding);return 1;
  }
 }
 if(s_overlayState.capture&&event->type==SDL_EVENT_GAMEPAD_AXIS_MOTION){
  int trigger=event->gaxis.axis==SDL_GAMEPAD_AXIS_LEFT_TRIGGER?0:event->gaxis.axis==SDL_GAMEPAD_AXIS_RIGHT_TRIGGER?1:-1;
  if(trigger<0)return 1;
  unsigned slot;for(slot=0;slot<16;slot++)if(pe_pad_triggers[slot].id==event->gaxis.which)break;
  if(slot==16)for(slot=0;slot<16;slot++)if(!pe_pad_triggers[slot].id){pe_pad_triggers[slot].id=event->gaxis.which;break;}
  if(slot<16){unsigned mask=1u<<trigger;
   if(event->gaxis.value<=8000)pe_pad_triggers[slot].armed|=mask;
   else if(event->gaxis.value>16000&&(pe_pad_triggers[slot].armed&mask)){pe_pad_triggers[slot].armed&=~mask;PePadCommit(SDL_GAMEPAD_BUTTON_COUNT+trigger);}
  }
  return 1;
 }
 return 0;
}
#endif
