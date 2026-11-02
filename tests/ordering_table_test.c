#include <libgs.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
void Psyz_PadsOverride(int port, char* frame, int length) { (void)port; (void)frame; (void)length; }
int main(void)
{
    ResetGraph(0);
    struct { uint64_t before; GsOT_TAG bank[2][64]; uint64_t after; } storage;
    memset(&storage, 0xa5, sizeof storage);
    GsOT tables[2] = {0};
    for (int b=0; b<2; ++b) {
        tables[b].length = 6;
        tables[b].org = storage.bank[b];
        GsClearOt(0, 0, &tables[b]);
        CHECK(tables[b].tag == &storage.bank[b][63]);
        for (int i=63; i>0; --i) {
            CHECK(getlen(&storage.bank[b][i]) == 0);
            CHECK(getaddr(&storage.bank[b][i]) == (u_long)&storage.bank[b][i-1]);
        }
        /* The game explicitly terminates bucket zero. Higher buckets, such as
         * caption text in bucket two, must remain reachable from the draw root. */
        setaddr(&storage.bank[b][0], 0xffffff); setlen(&storage.bank[b][0], 0);
        TILE tile = {0}; setTile(&tile); addPrim(&storage.bank[b][2], &tile);
        OT_TYPE* cursor = (OT_TYPE*)tables[b].tag;
        int found=0, steps=0;
        while ((u_long)cursor != 0xffffff) {
            CHECK(++steps <= 65);
            if (cursor == (OT_TYPE*)&tile) found++;
            cursor = (OT_TYPE*)getaddr(cursor);
        }
        CHECK(found == 1 && steps == 65);
    }
    CHECK(storage.before == UINT64_C(0xa5a5a5a5a5a5a5a5));
    CHECK(storage.after == UINT64_C(0xa5a5a5a5a5a5a5a5));
    puts("modal OT banks, reverse links and reachable caption bucket OK");
    return 0;
}
