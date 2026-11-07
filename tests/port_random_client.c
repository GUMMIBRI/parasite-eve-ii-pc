#include "port/random.h"
int gameRandomDraw(void) { return rand(); }
void gameRandomSeed(unsigned int seed) { srand(seed); }
