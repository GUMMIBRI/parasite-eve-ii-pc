/* SPDX-License-Identifier: MPL-2.0
 * PE2's implemented playtest group only; not a host for invented gameplay mods. */
#ifndef PE2_MOD_REGISTRY_H
#define PE2_MOD_REGISTRY_H
#include <stdio.h>
#include "port/playtest_assists.h"
enum { PE_MOD_ASSIST_LIMIT=16,PE_MOD_ASSIST_PREFIX_ROWS=3 };
/* Parse stages preferences. Loaded commits ONCE after every config key, so an
 * old option line after the new master key cannot accidentally reactivate it. */
void PeModBeginLoad(void);
int PeModParse(const char *key,long value); /*1 accepted,0 invalid,-1 unknown */
void PeModLoaded(void);
void PeModWrite(FILE *file);
unsigned PeModAssistCount(void);
const PeAssistOption *PeModAssistOption(unsigned index);
int PeModAssistRemembered(unsigned id);
int PeModAssistSet(unsigned id,int enabled);
int PeModAssistsEnabled(void);
void PeModAssistsSetEnabled(int enabled);
int PeModAssistsSuspended(void);
void PeModAssistsSetSuspended(int suspended);
void PeModAssistsReset(void);
const char *PeModAssistStatus(unsigned id);
const char *PeModAssistsStatus(void);
#endif
