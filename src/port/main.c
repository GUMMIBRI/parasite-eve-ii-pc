#include <psyz.h>
#include <libgpu.h>
#include <libetc.h>

/* Placeholder entry point: proves the PsyZ toolchain links. Replaced by the
 * port's boot code (mounting the disc images, then the original startup). */
int main(void) {
    ResetGraph(0);
    return 0;
}
