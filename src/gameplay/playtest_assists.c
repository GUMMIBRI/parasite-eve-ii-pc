/* MPL-2.0. Original PE2-specific playtest implementation. No PE1 offsets, retail data,
 * event completion stubs, inventory grants or per-frame save overwrites. */
#include "port/playtest_assists.h"
#include <string.h>
#ifdef PE2_PS5_HOST
#define ASSIST_AVAILABLE 1
#else
#define ASSIST_AVAILABLE 0
#endif
static const PeAssistOption assist_options[PE_ASSIST_COUNT]={
 {PE_ASSIST_CONTACT_HP,"assist_contact_hp","Protect contact HP","Ordinary player enemy-contact hits only; scripts, hazards, poison and ability HP costs stay original.",0,1,ASSIST_AVAILABLE},
 {PE_ASSIST_PE_COST,"assist_pe_cost","No PE cost","Keep eligibility and casting; skip positive ability MP costs. Enemy MP drain and Berserker HP costs stay original.",0,1,ASSIST_AVAILABLE},
 {PE_ASSIST_LOADED_AMMO,"assist_loaded_ammo","Freeze loaded ammo","Only positive supported existing loads; no empty clips/items granted. Matching carried-unit cost is also kept.",0,1,ASSIST_AVAILABLE},
 {PE_ASSIST_ALIVE_HP,"assist_alive_hp","Refill HP while alive","Refill during owned normal player updates. No revival, lethal-hit immunity, items or scripted-state changes.",0,1,ASSIST_AVAILABLE}
};
static unsigned char assist_flags[PE_ASSIST_COUNT]; /* ALL defaultOff */
static PeAssistContact enemy_contact;
static int enemy_contact_live;
unsigned PeAssistsCount(void){return PE_ASSIST_COUNT;}
const PeAssistOption *PeAssistsOption(unsigned id){return id<PE_ASSIST_COUNT?assist_options+id:0;}
int PeAssistsGet(unsigned id){return id<PE_ASSIST_COUNT&&assist_options[id].available?assist_flags[id]:0;}
int PeAssistsSet(unsigned id,int enabled){
 if(id>=PE_ASSIST_COUNT||enabled<0||enabled>1||!assist_options[id].available)return 0;
 assist_flags[id]=(unsigned char)enabled;
 if(id==PE_ASSIST_CONTACT_HP){enemy_contact_live=0;memset(&enemy_contact,0,sizeof enemy_contact);}
 return 1;
}
const char *PeAssistsStatus(unsigned id){
 if(id>=PE_ASSIST_COUNT||!assist_options[id].available)return "Unavailable";
 if(!PeAssistsGet(id))return "Off";
 return id==PE_ASSIST_CONTACT_HP?"On (ordinary immediate enemy contacts)":
  id==PE_ASSIST_PE_COST?"On (eligibility unchanged)":
  id==PE_ASSIST_ALIVE_HP?"On (alive normal player updates only)":"On (positive supported loaded ammo only)";
}
int PeAssistsParse(const char *key,long value){
 if(!key)return -1;
 for(unsigned id=0;id<PE_ASSIST_COUNT;++id)if(!strcmp(key,assist_options[id].key))
  return value>=0&&value<=1?PeAssistsSet(id,(int)value):0;
 return -1;
}
int PeAssistAbilityCost(int cost){return PeAssistsGet(PE_ASSIST_PE_COST)&&cost>0?0:cost;}
void PeAssistRecordEnemyContact(const PeAssistContact *c){
 enemy_contact_live=0;
 if(!c||!PeAssistsGet(PE_ASSIST_CONTACT_HP)||!c->livePlayer||!c->ordinarySession||
    !c->task||!c->actor||!c->model||!c->session||c->damage<=0||c->currentHp<=0)return;
 enemy_contact=*c;enemy_contact_live=1;
}
void PeAssistForgetEnemyContact(uintptr_t task,uintptr_t actor){
 if(enemy_contact_live&&enemy_contact.task==task&&enemy_contact.actor==actor)enemy_contact_live=0;
}
int PeAssistProtectEnemyContact(const PeAssistContact *c){
 if(!c||!enemy_contact_live||c->task!=enemy_contact.task||c->actor!=enemy_contact.actor)return 0;
 enemy_contact_live=0; /* Every matching consumption attempt retires receipt. */
 return PeAssistsGet(PE_ASSIST_CONTACT_HP)&&c->livePlayer&&c->ordinarySession&&c->currentHp>0&&
  c->model==enemy_contact.model&&c->session==enemy_contact.session&&c->damage>0&&
  c->damage==enemy_contact.damage&&c->reaction==enemy_contact.reaction&&
  c->hitRegion==enemy_contact.hitRegion&&(uint32_t)(c->frame-enemy_contact.frame)<=1;
}
#undef ASSIST_AVAILABLE

int PeAssistAliveHpTarget(int hp,int maximum,int originalMaximum,int liveOwner,int ordinarySession){
 if(!PeAssistsGet(PE_ASSIST_ALIVE_HP)||!liveOwner||!ordinarySession||
    hp<=0||maximum<=0||originalMaximum<=0||maximum>originalMaximum||hp>=maximum)return hp;
 return maximum;
}
