/* Exercise the actual SDK status reader, including naturally ended samples. */
#include "../third_party/psyz/decomp/src/libspu/libspu_private.h"
#include <stdio.h>
#include <stdlib.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
void Psyz_PadsOverride(int p, char* f, int n) { (void)p; (void)f; (void)n; }
int main(void)
{
    char status[24];
    /* Set the register snapshot without starting an asynchronous audio device. */
    _spu_keystat = (1 << 1) | (1 << 3) | (1 << 22);
    for (int i = 0; i < 24; ++i) _spu_RXX->rxx.voice[i].volumex = 0;
    _spu_RXX->rxx.voice[2].volumex = 123;
    _spu_RXX->rxx.voice[3].volumex = 123;
    SpuGetAllKeysStatus(status);
    CHECK(status[0] == SPU_OFF);
    CHECK(status[1] == SPU_ON_ENV_OFF);
    CHECK(status[2] == SPU_OFF_ENV_ON);
    CHECK(status[3] == SPU_ON);
    CHECK(status[22] == SPU_ON_ENV_OFF);
    puts("SPU key status: off, on, release tail and naturally ended sample match SDK constants");
    return 0;
}
