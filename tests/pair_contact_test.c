/* Exercise the production sphere/capsule writer and reciprocal replacement.
 * Include the TU to reach its private pair callback without adding a game API. */
#include "../src/gameplay/world_collision.c"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
_Alignas(void*) u8 gHostScratchpad[0x400];
void Psyz_PadsOverride(int p, char* f, int n) { (void)p; (void)f; (void)n; }
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static void identity(MATRIX* m) { memset(m, 0, sizeof *m); m->m[0][0] = m->m[1][1] = m->m[2][2] = 4096; }
int main(void)
{
    _Static_assert(sizeof(WorldCollisionContactResponse) == 8, "response remains eight bytes");
    _Static_assert(sizeof(WorldCollisionContact) == 24, "contact stride remains twenty-four bytes");
    WorldCollisionBody* spheres = calloc(2, sizeof *spheres);
    CHECK(spheres != NULL);
    if (sizeof(void*) > 4) CHECK((uintptr_t)spheres > UINT32_MAX);
    GfxCoord coords[3] = {0};
    WorldCollisionContact contacts[2][2] = {0}, capsuleContact = {.flags = WORLD_COLLISION_CONTACT_LAST};
    WorldCollisionCapsule shape = {.ends = {{0, 0, -100, 0}, {0, 0, 100, 0}}, .end0Radius = 30, .end1Radius = 30, .contacts = &capsuleContact};
    WorldCollisionBody capsule = {.coord = &coords[2], .context.capsule = &shape, .flags = WORLD_COLLISION_BODY_CAPSULE | WORLD_COLLISION_BODY_SINGLE_CONTACT | 0x30, .key = WORLD_COLLISION_CONTACT_ATTACK | 1};
    *SCRATCH_STACK_CURSOR_SLOT = (void*)SCRATCH_STACK_CURSOR_SLOT;
    for (int i = 0; i < 3; ++i) identity(&coords[i].workm);
    for (int i = 0; i < 2; ++i) {
        contacts[i][1].flags = WORLD_COLLISION_CONTACT_LAST;
        coords[i].workm.t[0] = 10 + 10 * i;
        spheres[i] = (WorldCollisionBody){.coord = &coords[i], .context.contacts = contacts[i], .radius = 20, .flags = WORLD_COLLISION_BODY_SPHERE, .key = WORLD_COLLISION_CONTACT_ENEMY_BODY | (i + 1)};
    }
    CHECK(_worldCollisionCollideSphereCapsulePair(&spheres[0], &capsule, 0) == 1);
    CHECK(capsuleContact.response.body == &spheres[0]);
    CHECK(capsuleContact.flags == (WORLD_COLLISION_CONTACT_LAST | WORLD_COLLISION_CONTACT_OCCUPIED | 0x30));
    CHECK(contacts[0][0].key.value == capsule.key && (contacts[0][0].flags & WORLD_COLLISION_CONTACT_OCCUPIED));
    CHECK(_worldCollisionCollideSphereCapsulePair(&spheres[1], &capsule, 0) == 1);
    CHECK(!(contacts[0][0].flags & WORLD_COLLISION_CONTACT_OCCUPIED));
    CHECK(capsuleContact.response.body == &spheres[1] && capsuleContact.key.value == spheres[1].key);
    CHECK(contacts[1][0].flags & WORLD_COLLISION_CONTACT_OCCUPIED);
    CHECK(_worldCollisionCollideSphereCapsulePair(&spheres[1], &capsule, 0) == 1);
    CHECK(!(contacts[1][0].flags & WORLD_COLLISION_CONTACT_OCCUPIED));
    CHECK(contacts[1][1].flags == (WORLD_COLLISION_CONTACT_LAST | WORLD_COLLISION_CONTACT_OCCUPIED));
    CHECK(capsuleContact.response.body == &spheres[1]);
    CHECK(*SCRATCH_STACK_CURSOR_SLOT == (void*)SCRATCH_STACK_CURSOR_SLOT);
    free(spheres);
    puts("sphere/capsule contacts: full native pointer, reciprocal replacement, repeated hit and stable layout OK");
    return 0;
}
