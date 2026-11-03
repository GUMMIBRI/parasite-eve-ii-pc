#ifndef PORT_MEMORY_CARD_H
#define PORT_MEMORY_CARD_H

#include <stdint.h>

/* The game reads PS1 directory records, not PsyZ's host filesystem DIRENTRY. */
typedef struct {
    char name[20];
    int32_t attr;
    int32_t size;
    uint32_t next;
    int32_t head;
    char system[4];
} PeMemoryCardDirectoryEntry;

/* One host pad-poll pulse, independent of wall-clock replay speed. */
void peMemoryCardAdvanceIo(void);

long peMemoryCardGetDirentry(long channel, const char* pattern,
                            PeMemoryCardDirectoryEntry* entries, long* count,
                            long offset, long maximum);

#endif
