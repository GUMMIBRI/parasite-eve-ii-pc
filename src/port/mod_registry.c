/* SPDX-License-Identifier: MPL-2.0
 * Original bounded PE2 grouping of real assist providers. No game/card writes,
 * PE1 IDs/offsets/content or per-frame gameplay-state overwrites. */
#include "port/mod_registry.h"
#include <string.h>

static unsigned char remembered[PE_MOD_ASSIST_LIMIT];
static int enabled,suspended,master_seen;

static int schema(void)
{
    unsigned count=PeAssistsCount();
    if(!count||count>PE_MOD_ASSIST_LIMIT)return 0;
    for(unsigned i=0;i<count;i++){
        const PeAssistOption *a=PeAssistsOption(i);
        if(!a||a->id!=i||!a->key||!a->key[0]||!a->label||!a->description||
           a->minimum!=0||a->maximum!=1||!strcmp(a->key,"assist_group_enabled"))return 0;
        for(unsigned j=0;j<i;j++)if(!strcmp(a->key,PeAssistsOption(j)->key))return 0;
    }
    return 1;
}
unsigned PeModAssistCount(void){return schema()?PeAssistsCount():0;}
const PeAssistOption *PeModAssistOption(unsigned index)
{
    return index<PeModAssistCount()?PeAssistsOption(index):NULL;
}
static void apply(void)
{
    /* A new provider is included through its real descriptor/count, never a
     * copied constant3. Existing gameplay Get stays the actual effective flag. */
    unsigned count=PeModAssistCount();
    for(unsigned i=0;i<count;i++)
        PeAssistsSet(i,enabled&&!suspended&&remembered[i]);
}
void PeModBeginLoad(void)
{
    memset(remembered,0,sizeof remembered);enabled=suspended=master_seen=0;
    apply();
}
int PeModParse(const char *key,long value)
{
    if(!key)return -1;
    if(!strcmp(key,"assist_group_enabled")){
        /* Presence of even an invalid explicit master must not trigger legacy
         * inference. Invalid input fails closed rather than reviving old On. */
        master_seen=1;
        if(value<0||value>1){enabled=0;return 0;}
        enabled=(int)value;return 1;
    }
    unsigned count=PeModAssistCount();
    for(unsigned i=0;i<count;i++)if(!strcmp(key,PeAssistsOption(i)->key)){
        if(value<0||value>1)return 0;
        remembered[i]=(unsigned char)value;return 1;
    }
    return -1;
}
void PeModLoaded(void)
{
    if(!master_seen){
        enabled=0;
        for(unsigned i=0;i<PeModAssistCount();i++)if(remembered[i]){enabled=1;break;}
    }
    suspended=0;apply();
}
void PeModWrite(FILE *file)
{
    if(!file)return;
    fprintf(file,"assist_group_enabled=%d\n",!!enabled);
    for(unsigned i=0;i<PeModAssistCount();i++)
        fprintf(file,"%s=%u\n",PeAssistsOption(i)->key,(unsigned)remembered[i]);
    /* Session suspension is intentionally not a persistent preference. */
}
int PeModAssistRemembered(unsigned id)
{
    return id<PeModAssistCount()?remembered[id]:0;
}
int PeModAssistSet(unsigned id,int value)
{
    const PeAssistOption *a=PeModAssistOption(id);
    if(!a||!a->available||value<0||value>1)return 0;
    remembered[id]=(unsigned char)value;apply();return 1;
}
int PeModAssistsEnabled(void){return !!enabled;}
void PeModAssistsSetEnabled(int value)
{
    if(value<0||value>1)return;
    enabled=value;suspended=0;master_seen=1;apply();
}
int PeModAssistsSuspended(void){return !!suspended;}
void PeModAssistsSetSuspended(int value)
{
    if(value<0||value>1||!enabled)return;
    suspended=value;apply();
}
void PeModAssistsReset(void)
{
    memset(remembered,0,sizeof remembered);enabled=suspended=0;master_seen=1;apply();
}
const char *PeModAssistStatus(unsigned id)
{
    const PeAssistOption *a=PeModAssistOption(id);
    if(!a||!a->available)return "Unavailable";
    if(!remembered[id])return "Off";
    if(!enabled)return "Remembered On (group Off)";
    if(suspended)return "Remembered On (suspended)";
    return PeAssistsStatus(id);
}
const char *PeModAssistsStatus(void)
{
    if(!schema())return "Unavailable (provider limit/schema)";
    return !enabled?"Off (choices remembered)":suspended?"On (session suspended)":"On";
}
