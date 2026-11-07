#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <psyz/system.h>
void Psyz_PadsOverride(int port,char* frame,int length) { (void)port;(void)frame;(void)length; }
int gameRandomDraw(void);
void gameRandomSeed(unsigned int seed);
int main(void)
{
    const unsigned seeds[]={0,1,0x80000000u,0xffffffffu};
    for(unsigned seed=0;seed<sizeof seeds/sizeof seeds[0];seed++) {
        uint32_t expected=seeds[seed];
        gameRandomSeed(expected);
        for(unsigned draw=0;draw<1024;draw++) {
            /* Unrelated host draws/reseeds must never consume game state. */
            srand(draw+17);
            for(unsigned host=0;host<13;host++)(void)rand();
            assert(Psyz_RandState()==expected);
            expected=expected*UINT32_C(0x41c64e6d)+UINT32_C(0x3039);
            int actual=gameRandomDraw();
            assert(actual==(int)((expected>>16)&0x7fff));
            assert(Psyz_RandState()==expected);
        }
    }
    srand(1234);
    int expectedHost=rand();
    srand(1234);
    gameRandomSeed(5678);
    for(unsigned draw=0;draw<128;draw++)(void)gameRandomDraw();
    assert(rand()==expectedHost);
    return 0;
}
