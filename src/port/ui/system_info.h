/* Native read-only System details. Uses existing owned state; performs no IO.
 * Existing appearance settings remain rows0..2. */
#ifndef PE2_SYSTEM_INFO_H
#define PE2_SYSTEM_INFO_H
#include "port/memory_card.h"
enum { PE_SYSTEM_ROWS=16, PE_SYSTEM_DETAIL_CHARS=76, PE_SYSTEM_PAGE_CHARS=152 };
static unsigned pe_system_detail_page[PE_SYSTEM_ROWS];
static const char *PeSystemFontName(unsigned context)
{
    static const char *names[]={"Original","Plex","Retro","Atkinson"};
    unsigned n=Psyz_GpuGetFontStyle(context);
    return n<4?names[n]:"Unknown";
}
static const char *PeSystemDetail(int row)
{
    const char *root;
    switch(row){
    case 3:return configDir&&*configDir?configDir:"Preferences directory unavailable; no fallback write path selected.";
    case 4:return configPath[0]?configPath:"Preferences file unavailable; settings cannot be saved here.";
    case 5:root=peMemoryCardOwnedRoot();return root?root:"Memory-card root not initialized or unavailable. No save directory is inferred.";
    case 6:case 7:return discPaths[row-6][0]?discPaths[row-6]:"No disc configured. Use the Discs page to select an image.";
    case 8:return pePs5DiscDiscoveryReason();
    case 9:case 10:return "Selected presentation profile only. Requires above 1x; unsupported text keeps its original glyphs. This does not mean every caption is upgraded.";
    case 11:return PeHdStatus();
    case 12:return PeHdBackgroundStatus();
    case 13:return "Save using the original in-game Save menu. Native slots are card0 and card1 below the owned card root; game-created filenames and save bytes stay unchanged.";
    case 14:return "Native saves are individual files, allocated in 8192-byte blocks (15 per slot). A .mcr is a whole-card image, not one native save file. No automatic import or conversion is provided.";
    case 15:return pePs5StorageReason();
    default:return "";
    }
}
static unsigned PeSystemDetailPages(int row)
{
    size_t n=strlen(PeSystemDetail(row));
    return n?(unsigned)((n+PE_SYSTEM_PAGE_CHARS-1)/PE_SYSTEM_PAGE_CHARS):1;
}
static void PeSystemPageDetail(int row,int direction)
{
    if(row<3||row>=PE_SYSTEM_ROWS)return;
    unsigned count=PeSystemDetailPages(row),n=pe_system_detail_page[row]%count;
    pe_system_detail_page[row]=(n+count+(direction<0?-1:1))%count;
}
static void PeSystemRow(int row,char *label,char *value)
{
    static const char *labels[]={"Preferences directory","Preferences file","Memory-card root",
        "Configured Disc 1","Configured Disc 2","Default disc discovery","Menu font profile",
        "Dialogue font profile","Player texture status","Background status","How to save",
        "Save files and .mcr","Storage policy"};
    snprintf(label,128,"%s",labels[row-3]);
    if(row==9||row==10)snprintf(value,256,"%s",PeSystemFontName(row==9?PSYZ_FONT_MENU:PSYZ_FONT_DIALOGUE));
    else if(row==5)snprintf(value,256,"%s",peMemoryCardOwnedRoot()?"Owned root selected":"Unavailable / not initialized");
    else if(row==3||row==4)snprintf(value,256,"%s",row==3?(configDir?"Selected":"Unavailable"):(configPath[0]?"Selected":"Unavailable"));
    else if(row==6||row==7)snprintf(value,256,"%s",discPaths[row-6][0]?"Configured":"Not configured");
    else snprintf(value,256,"Read details");
}
static void PeSystemPaintDetail(OverlaySurface *surface,float y,float s,int row)
{
    const char *text=PeSystemDetail(row);unsigned pages=PeSystemDetailPages(row);
    unsigned page=pe_system_detail_page[row]%pages;size_t offset=(size_t)page*PE_SYSTEM_PAGE_CHARS;
    char first[PE_SYSTEM_DETAIL_CHARS+1],second[PE_SYSTEM_DETAIL_CHARS+1],heading[128];
    size_t remain=strlen(text)-offset;
    snprintf(first,sizeof first,"%.*s",PE_SYSTEM_DETAIL_CHARS,text+offset);
    snprintf(second,sizeof second,"%.*s",PE_SYSTEM_DETAIL_CHARS,text+offset+(remain>PE_SYSTEM_DETAIL_CHARS?PE_SYSTEM_DETAIL_CHARS:remain));
    snprintf(heading,sizeof heading,"Details %u/%u  |  Left / right: more  |  Read only",page+1,pages);
    DrawText(surface,32*s,y-5*s,12*s,heading,kMuted,ALIGN_LEFT);
    DrawText(surface,32*s,y+13*s,12*s,first,kText,ALIGN_LEFT);
    DrawText(surface,32*s,y+30*s,12*s,second,kText,ALIGN_LEFT);
}
#endif
