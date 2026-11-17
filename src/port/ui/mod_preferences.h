/* SPDX-License-Identifier: MPL-2.0
 * Thin actual-provider rows inside the existing focus-gated Assists page. */
#ifndef PE2_MOD_PREFERENCES_H
#define PE2_MOD_PREFERENCES_H
#include "port/mod_registry.h"
static int PeModRows(void){return PE_MOD_ASSIST_PREFIX_ROWS+(int)PeModAssistCount();}
static void PeModRow(int row,char label[128],char value[256])
{
    if(row==0){snprintf(label,128,"Playtest assists");snprintf(value,256,"%s",PeModAssistsStatus());return;}
    if(row==1){snprintf(label,128,"Suspend for this session");snprintf(value,256,"%s",
        !PeModAssistsEnabled()?"Group Off":PeModAssistsSuspended()?"Suspended":"Active");return;}
    if(row==2){snprintf(label,128,"Restore assist defaults");snprintf(value,256,"Choose...");return;}
    const PeAssistOption *a=row>=PE_MOD_ASSIST_PREFIX_ROWS?PeModAssistOption((unsigned)(row-PE_MOD_ASSIST_PREFIX_ROWS)):NULL;
    snprintf(label,128,"%s",a?a->label:"Unavailable");
    snprintf(value,256,"%s",a?PeModAssistStatus(a->id):"Unavailable");
}
static const char *PeModHelp(int row)
{
    if(row==0)return "Master switch for actual playtest assists. Off remembers choices; presentation, controls and game saves stay separate.";
    if(row==1)return "Temporarily disable the group without changing saved choices. Enable the group first. Suspension resets on restart.";
    if(row==2)return "Enter / South: turn the group Off and clear remembered assist choices. Other settings and game saves stay unchanged.";
    const PeAssistOption *a=row>=PE_MOD_ASSIST_PREFIX_ROWS?PeModAssistOption((unsigned)(row-PE_MOD_ASSIST_PREFIX_ROWS)):NULL;
    return a?a->description:"Only implemented assist providers appear here.";
}
static void PeModChange(int row,int activate)
{
    if(row==0){PeModAssistsSetEnabled(!PeModAssistsEnabled());return;}
    if(row==1){PeModAssistsSetSuspended(!PeModAssistsSuspended());return;}
    if(row==2){if(activate)PeModAssistsReset();return;}
    if(row<PE_MOD_ASSIST_PREFIX_ROWS)return;
    const PeAssistOption *a=PeModAssistOption((unsigned)(row-PE_MOD_ASSIST_PREFIX_ROWS));
    if(a)PeModAssistSet(a->id,!PeModAssistRemembered(a->id));
}
#endif
