/* SPDX-License-Identifier: CC0-1.0
 * Raw early-CRT records: no libc, errno, allocation or TLS before _init_env.
 * Main-thread stage/failure APIs; SDL callback has only stack-local formatting.
 */
#include <stddef.h>
#include <fcntl.h>
#include <stdatomic.h>
#include <SDL3/SDL_log.h>
#include <errno.h>
#ifndef PE2_NATIVE_BUILD_TAG
#define PE2_NATIVE_BUILD_TAG "Test17"
#endif
extern int sceKernelOpen(const char*, int, unsigned);
extern long sceKernelWrite(int, const void*, size_t);
extern int sceKernelFsync(int);
extern int sceKernelClose(int);
extern void ps5_fp_ieee(void);
_Static_assert(ATOMIC_INT_LOCK_FREE == 2, "early logging requires lock-free unsigned/int");
static atomic_int logFd = ATOMIC_VAR_INIT(-1);
static atomic_uint routineBytes = ATOMIC_VAR_INIT(0), failureBytes = ATOMIC_VAR_INIT(0);
static atomic_uint dropped = ATOMIC_VAR_INIT(0);
static int attempted, fpInitialized; /* CRT/main thread only */
static char lastStage[256], lastFailure[256], failureDetail[768];
static int failureStatus, hadFailure;
struct Record { char text[2048]; size_t used; };
static void add(struct Record *r, const char *s, size_t limit)
{
    if (!s) s = "(null)";
    for (size_t i=0; i<limit && s[i] && r->used+2<sizeof r->text; ++i) {
        char c=s[i]; r->text[r->used++]=(c=='\n'||c=='\r')?' ':c;
    }
}
static void number(struct Record *r, int value)
{
    char b[10]; unsigned n=(unsigned)value, k=0;
    if(value<0) { add(r,"-",1); n=0u-n; }
    do { b[k++]=(char)('0'+n%10); n/=10; } while(n);
    while(k && r->used+2<sizeof r->text) r->text[r->used++]=b[--k];
}
static void copy(char *dst, size_t cap, const char *src)
{
    size_t n=0; if(!src) src="(null)";
    while(n+1<cap && src[n]) { dst[n]=src[n]; ++n; } dst[n]=0;
}
static void begin(struct Record *r, const char *kind)
{
    r->used=0; add(r,"[PE2 ",5); add(r,PE2_NATIVE_BUILD_TAG,80);
    add(r,"] ",2); add(r,kind,40); add(r,": ",2);
}
static int reserve(atomic_uint *counter, unsigned limit, unsigned bytes)
{
    unsigned used=atomic_load_explicit(counter,memory_order_relaxed);
    /* Bounded contention: dropping an SDL record cannot stall another thread. */
    for(unsigned tries=0; tries<32; ++tries) {
        if(used>limit || bytes>limit-used) return 0;
        if(atomic_compare_exchange_weak_explicit(counter,&used,used+bytes,
              memory_order_relaxed,memory_order_relaxed)) return 1;
    }
    return 0;
}
static void emit(struct Record *r, int important)
{
    r->text[r->used++]='\n';
    if(!reserve(important?&failureBytes:&routineBytes, important?65536u:262144u,(unsigned)r->used)) {
        atomic_fetch_add_explicit(&dropped,1,memory_order_relaxed); return;
    }
    /* One bounded O_APPEND write per record: no shared formatter or interleaved
     * partial-write retry. Short/error writes remain explicitly best effort. */
    (void)sceKernelWrite(1,r->text,r->used);
    int fd=atomic_load_explicit(&logFd,memory_order_acquire);
    if(fd>=0) {
        long n=sceKernelWrite(fd,r->text,r->used);
        if(n!=(long)r->used) atomic_fetch_add_explicit(&dropped,1,memory_order_relaxed);
        (void)sceKernelFsync(fd);
    }
}
void pe_application_stage(const char *message)
{
    if(!fpInitialized) { fpInitialized=1; ps5_fp_ieee(); }
    if(!attempted) {
        attempted=1;
        int parent=sceKernelOpen("/mnt",O_RDONLY|O_NONBLOCK|O_DIRECTORY|O_NOFOLLOW,0);
        if(parent>=0 && sceKernelClose(parent)>=0) {
            int mount=sceKernelOpen("/mnt/usb0",O_RDONLY|O_NONBLOCK|O_DIRECTORY|O_NOFOLLOW,0);
            if(mount>=0 && sceKernelClose(mount)>=0) {
                int fd=sceKernelOpen("/mnt/usb0/parasite-eve-ii-startup.log",
                    O_WRONLY|O_APPEND|O_CREAT|O_NOFOLLOW,0666);
                atomic_store_explicit(&logFd,fd,memory_order_release);
            }
        }
    }
    copy(lastStage,sizeof lastStage,message);
    struct Record r; begin(&r,"stage"); add(&r,message,1400); emit(&r,0);
}
void pe_application_failure(const char *stage, int status, const char *detail)
{
    /* Ordinary main-thread errors only; deliberately NOT a signal handler. */
    copy(lastFailure,sizeof lastFailure,stage); copy(failureDetail,sizeof failureDetail,detail);
    failureStatus=status; hadFailure=1;
    struct Record r; begin(&r,"failure"); add(&r,stage,255); add(&r," status=",8);
    number(&r,status); add(&r," detail=",8); add(&r,detail,1000);
    add(&r," last-stage=",12); add(&r,lastStage,255); emit(&r,1);
}
void catchReturnFromMain(int status)
{
    /* Strong replacement for public app_crt.cpp's weak C hook. No change to
     * status, atexit/loader teardown or libc exit. A missing return record alone
     * is not proof of a fault (USB loss/termination can also interrupt logging). */
    struct Record r; begin(&r,"clean-main-return"); add(&r,"status=",7); number(&r,status);
    add(&r," last-stage=",12); add(&r,lastStage,255);
    if(hadFailure) {
        add(&r," failure-stage=",15); add(&r,lastFailure,255);
        add(&r," failure-status=",16); number(&r,failureStatus);
        add(&r," detail=",8); add(&r,failureDetail,767);
    } else add(&r," no-recorded-startup-failure",27);
    add(&r," dropped-records=",17);
    unsigned lost=atomic_load_explicit(&dropped,memory_order_relaxed);
    number(&r,lost>2147483647u?2147483647:(int)lost); emit(&r,1);
}
static void SDLCALL logOutput(void *unused,int category,SDL_LogPriority priority,const char *message)
{
    (void)unused;
    int saved=errno; struct Record r; begin(&r,"SDL"); add(&r,"category=",9);
    number(&r,category); add(&r," priority=",10); number(&r,(int)priority);
    add(&r," ",1); add(&r,message,1700);
    emit(&r,0); errno=saved;
}
void pe_ps5_install_logging(void)
{
    SDL_SetLogOutputFunction(logOutput,NULL);
    pe_application_stage("main entered; native SDL log callback installed");
}
