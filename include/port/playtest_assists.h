/* MPL-2.0. Source-owned optional PE2 playtest assists. No game-save layout/offset ABI. */
#ifndef PE2_PLAYTEST_ASSISTS_H
#define PE2_PLAYTEST_ASSISTS_H
#include <stdint.h>
enum { PE_ASSIST_CONTACT_HP=0,PE_ASSIST_PE_COST=1,PE_ASSIST_LOADED_AMMO=2,PE_ASSIST_ALIVE_HP=3,PE_ASSIST_COUNT=4 };
typedef struct {
    unsigned id;
    const char *key,*label,*description;
    int minimum,maximum,available;
} PeAssistOption;
unsigned PeAssistsCount(void);
const PeAssistOption *PeAssistsOption(unsigned id);
int PeAssistsGet(unsigned id);
int PeAssistsSet(unsigned id,int enabled);
const char *PeAssistsStatus(unsigned id);
/*1 accepted,0 recognized invalid,-1 unknown. No files or card fields written. */
int PeAssistsParse(const char *key,long value);
/* Use ONLY at actual ability MP-cost deduction, never enemy MP-drain helpers. */
int PeAssistAbilityCost(int originalCost);
/* Pure target selection for the actual normal player status tick. No pointer
 * retained or HP written here; dead/unknown owners and invalid maxima unchanged. */
int PeAssistAliveHpTarget(int currentHp,int maximumHp,int originalMaximum,
                         int liveOwner,int ordinarySession);
/* A one-shot original category4 contact receipt. Identities are copied numeric
 * values, never retained pointers later dereferenced. No HP is written here. */
typedef struct {
    uintptr_t task,actor,model,session;
    uint32_t frame;
    int damage,reaction,hitRegion,livePlayer,ordinarySession,currentHp;
} PeAssistContact;
void PeAssistRecordEnemyContact(const PeAssistContact *contact);
void PeAssistForgetEnemyContact(uintptr_t task,uintptr_t actor);
int PeAssistProtectEnemyContact(const PeAssistContact *current);
#endif
