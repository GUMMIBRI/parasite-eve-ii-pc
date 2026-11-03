#ifdef NDEBUG
#undef NDEBUG
#endif
#include "port/memory_card.h"
#include <libmcrd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <unistd.h>

static void completed(long command, long result)
{
    long actualCommand = -99, actualResult = -99;
    assert(MemCardSync(1, &actualCommand, &actualResult) == 0);
    peMemoryCardAdvanceIo();
    assert(MemCardSync(1, &actualCommand, &actualResult) == 1);
    assert(actualCommand == command && actualResult == result);
    assert(MemCardSync(1, &actualCommand, &actualResult) == -1);
    assert(actualCommand == command && actualResult == result);
}

int main(void)
{
    char root[] = "/tmp/pe2-memory-card-XXXXXX";
    assert(mkdtemp(root));
    assert(setenv("PE2_MEMORY_CARD_DIR", root, 1) == 0);
    MemCardInit(0);
    assert(MemCardAccept(0) == 0);
    MemCardStart();
    assert(MemCardAccept(0) == 1);
    assert(MemCardAccept(0) == 0); /* one outstanding completion */
    assert(MemCardCreateFile(0, "SAVE01", 1) == -1);
    completed(McFuncAccept, McErrNewCard);
    assert(MemCardAccept(0) == 1);
    completed(McFuncAccept, McErrNone);
    assert(MemCardExist(0x20) == 1);
    completed(McFuncExist, McErrCardNotExist);

    /* Retail save UI leaves a completed Exist result unread when changing
     * from a presence-polled question to directory enumeration/file opening. */
    assert(MemCardExist(0) == 1);
    assert(MemCardOpen(0, "SAVE01", O_RDONLY) == -1);
    peMemoryCardAdvanceIo();
    PeMemoryCardDirectoryEntry empty[15];
    long emptyCount = -1;
    assert(peMemoryCardGetDirentry(0, "*", empty, &emptyCount, 0, 15) == McErrNone);
    assert(emptyCount == 0);
    assert(MemCardOpen(0, "SAVE01", O_RDONLY) == McErrFileNotExist);
    assert(MemCardCreateFile(0, "../escape", 1) == McErrCardInvalid);
    assert(MemCardCreateFile(0, "SAVE01", 0) == McErrCardInvalid);
    assert(MemCardCreateFile(0, "SAVE01", 1) == McErrNone);
    assert(MemCardCreateFile(0, "SAVE01", 1) == McErrAlreadyExist);
    unsigned long data[512 / sizeof(unsigned long)], restored[sizeof(data) / sizeof(data[0])];
    memset(data, 0xA5, sizeof(data));
    assert(MemCardWriteFile(0, "SAVE01", data, 0, sizeof(data)) == 1);
    completed(McFuncWriteFile, McErrNone);
    assert(MemCardOpen(0, "SAVE01", O_WRONLY) == McErrNone);
    assert(MemCardReadData(restored, 0, sizeof(restored)) == 0);
    assert(MemCardWriteData(data, 1, 128) == 0);
    assert(MemCardWriteData(data, 0, 127) == 0);
    assert(MemCardWriteFile(0, "SAVE01", data, 0, sizeof(data)) == 0);
    memset(data, 0x5A, sizeof(data));
    assert(MemCardWriteData(data, 512, sizeof(data)) == 1);
    completed(McFuncWriteData, McErrNone);
    assert(MemCardWriteData(data, 8192, 128) == 1);
    completed(McFuncWriteData, McErrCardInvalid);
    /* Force a partial host write, even when tests run as root. The previous
     * save and its already-written sectors must survive a failed replacement. */
    struct rlimit originalLimit, shortLimit;
    assert(getrlimit(RLIMIT_FSIZE, &originalLimit) == 0);
    shortLimit = originalLimit;
    shortLimit.rlim_cur = 128;
    void (*previousSignal)(int) = signal(SIGXFSZ, SIG_IGN);
    assert(previousSignal != SIG_ERR);
    assert(setrlimit(RLIMIT_FSIZE, &shortLimit) == 0);
    assert(MemCardWriteData(data, 0, sizeof(data)) == 1);
    completed(McFuncWriteData, McErrCardInvalid);
    assert(setrlimit(RLIMIT_FSIZE, &originalLimit) == 0);
    assert(signal(SIGXFSZ, previousSignal) != SIG_ERR);
    MemCardClose();

    /* A fresh library instance must recover bytes from disk, not cached RAM. */
    MemCardInit(0);
    MemCardStart();
    assert(MemCardOpen(0, "SAVE01", O_RDONLY) == McErrNone);
    assert(MemCardWriteData(data, 0, sizeof(data)) == 0);
    assert(MemCardReadData(restored, 512, sizeof(restored)) == 1);
    completed(McFuncReadData, McErrNone);
    assert(memcmp(data, restored, sizeof(data)) == 0);
    assert(MemCardReadData(restored, 0, sizeof(restored)) == 1);
    completed(McFuncReadData, McErrNone);
    for (size_t i = 0; i < sizeof(restored); ++i) assert(((unsigned char*)restored)[i] == 0xA5);
    memset(restored, 0xCC, sizeof(restored));
    assert(MemCardReadData(restored, 8192, 128) == 1);
    completed(McFuncReadData, McErrCardInvalid);
    for (size_t i = 0; i < sizeof(restored); ++i) assert(((unsigned char*)restored)[i] == 0xCC);
    MemCardClose();

    assert(MemCardCreateFile(0, "OTHER", 2) == McErrNone);
    assert(MemCardCreateFile(0, "SAVE02", 1) == McErrNone);
    PeMemoryCardDirectoryEntry entries[15];
    _Static_assert(sizeof(entries[0]) == 40, "retail card directory ABI");
    long count = -1;
    assert(peMemoryCardGetDirentry(0, "*", entries, &count, 0, 15) == McErrNone);
    assert(count == 3);
    assert(!strcmp(entries[0].name, "OTHER") && entries[0].size == 16384 && entries[0].head == 64);
    assert(!strcmp(entries[1].name, "SAVE01") && entries[1].size == 8192 && entries[1].head == 192);
    assert(!strcmp(entries[2].name, "SAVE02") && entries[2].head == 256);
    assert(peMemoryCardGetDirentry(0, "SAVE??", entries, &count, 1, 1) == McErrNone);
    assert(count == 1 && !strcmp(entries[0].name, "SAVE02") && entries[0].head == 256);
    assert(peMemoryCardGetDirentry(0x10, "*", entries, &count, 0, 15) == McErrNone && count == 0);
    assert(MemCardCreateFile(0, "FILL", 11) == McErrNone);
    assert(MemCardCreateFile(0, "OVER", 1) == McErrBlockFull);
    assert(MemCardCreateFile(0x10, "SAVE01", 1) == McErrNone);

    /* Formatting one card must leave the other card untouched. */
    assert(MemCardFormat(0) == McErrNone);
    assert(peMemoryCardGetDirentry(0, "*", entries, &count, 0, 15) == McErrNone && count == 0);
    assert(MemCardOpen(0x10, "SAVE01", O_RDONLY) == McErrNone);
    assert(MemCardReadData(restored, 0, 128) == 1);
    completed(McFuncReadData, McErrNone);
    for (int i = 0; i < 128; ++i) assert(((unsigned char*)restored)[i] == 0);
    MemCardClose();
    assert(MemCardFormat(0x10) == McErrNone);

    /* Retail product filenames occupy all 20 directory bytes, without NUL. */
    char retailName[] = "BASLUS-01042ABCDEFGH";
    assert(strlen(retailName) == 20);
    assert(MemCardCreateFile(0, retailName, 1) == McErrNone);
    assert(peMemoryCardGetDirentry(0, "BASLUS-01042*", entries, &count, 0, 15) == McErrNone && count == 1);
    assert(memcmp(entries[0].name, retailName, 20) == 0);
    assert(MemCardOpen(0, entries[0].name, O_RDONLY) == McErrNone);
    MemCardClose();
    assert(MemCardFormat(0) == McErrNone);

    char path[1024];
    snprintf(path, sizeof(path), "%s/card0", root); assert(rmdir(path) == 0);
    snprintf(path, sizeof(path), "%s/card1", root); assert(rmdir(path) == 0);
    /* An inaccessible storage path must surface an error, never fake success. */
    snprintf(path, sizeof(path), "%s/not-a-directory", root);
    FILE* file = fopen(path, "wb"); assert(file); assert(fclose(file) == 0);
    assert(setenv("PE2_MEMORY_CARD_DIR", path, 1) == 0);
    MemCardInit(0); MemCardStart();
    assert(MemCardAccept(0) == 1);
    completed(McFuncAccept, McErrCardInvalid);
    assert(unlink(path) == 0);
    assert(rmdir(root) == 0);
    puts("Memory-card persistence, bounds, directory ABI, capacity and isolation OK");
    return 0;
}
