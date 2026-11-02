#include <libspu.h>

void SpuLSetVoiceAttr(int num, SpuLVoiceAttr* argList)
{
    for (int i = 0; i < num; ++i) {
        int voice = argList[i].voiceNum;
        if (voice < 0 || voice >= 24) continue;
        SpuVoiceAttr attr = argList[i].attr;
        attr.voice = (u_long)1 << voice;
        SpuSetVoiceAttr(&attr);
    }
}
