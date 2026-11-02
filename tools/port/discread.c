#include "port/disc_assets.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv)
{
    if (argc < 5) { fprintf(stderr, "usage: discread cue stage folder file\n"); return 2; }
    PeDisc* d = peDiscOpen(argv[1]);
    if (!d) { fprintf(stderr, "cannot open\n"); return 1; }
    size_t n;
    uint8_t* p = peDiscReadPackage(d, atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), &n);
    if (!p) { fprintf(stderr, "not found\n"); return 3; }
    fwrite(p, 1, n, stdout);
    return 0;
}
