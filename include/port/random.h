#ifndef PORT_RANDOM_H
#define PORT_RANDOM_H
/* Game code expects the PS1 BIOS sequence, not the host C library's random
 * state/range. Include host declarations before mapping game calls; SDL and
 * other libraries are compiled without this forced compatibility header. */
#include <stdlib.h>
#include <psyz/system.h>
#define rand Psyz_Rand
#define srand Psyz_Srand
#endif
