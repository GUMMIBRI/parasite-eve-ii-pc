#include <assert.h>
#include <limits.h>
#include "main/random.h"

static int nextDraw;
static int draws;

int rand(void)
{
    ++draws;
    return nextDraw;
}

int main(void)
{
    const int highBits[] = { 0, 0x40000000, INT_MAX & ~0x7FFF };
    for (unsigned h = 0; h < sizeof(highBits) / sizeof(highBits[0]); ++h) {
        for (int low = 0; low < 32768; ++low) {
            nextDraw = highBits[h] | low;
            int before = draws;
            int sample = randomSdkDraw15();
            assert(draws == before + 1);
            assert(sample == low);
            for (int count = 1; count <= 32; ++count) {
                int index = (sample * count) >> 15;
                assert(index >= 0 && index < count);
            }
        }
    }
    return 0;
}
