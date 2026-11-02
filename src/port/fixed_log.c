#include <stdint.h>

/* SDK cor_04 cln (retail address 0x8004AB60). Both input and result are Q12.
 * Keep its six integer refinement steps: log()/rounding changes surface-class
 * boundaries, and treating the input as an integer adds twelve to log2(x).
 * The SDK's Lzc counts leading sign bits through the GTE LZCS/LZCR pair. */
static int32_t arithmeticRight(int32_t value, unsigned count)
{
    uint32_t shifted = (uint32_t)value >> count;
    if (value < 0 && count != 0) shifted |= UINT32_MAX << (32 - count);
    return (int32_t)shifted;
}

long cln(long x)
{
    static const int32_t increments[6] = {1661, 914, 482, 248, 126, 63};
    const uint32_t bits = (uint32_t)x;
    uint32_t leadingBits = (int32_t)bits < 0 ? ~bits : bits;
    unsigned leading = 0;
    while (leading < 32 && !(leadingBits & UINT32_C(0x80000000))) {
        leadingBits <<= 1;
        ++leading;
    }
    const int shift = 20 - (int)leading;
    int32_t normalized = shift >= 0 ? arithmeticRight((int32_t)bits, (unsigned)shift)
                                   : (int32_t)(bits << (unsigned)-shift);
    int32_t correction = 0;
    for (unsigned step = 1; step <= 6; ++step) {
        int32_t candidate = (int32_t)((uint32_t)normalized + (uint32_t)arithmeticRight(normalized, step));
        if (candidate < 4096) {
            normalized = candidate;
            correction -= increments[step - 1];
        }
    }
    return (int32_t)((uint32_t)correction - 4096U + (uint32_t)normalized + (uint32_t)(shift * 2839));
}
