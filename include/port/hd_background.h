/* MPL-2.0 */
#ifndef PE_HD_BACKGROUND_H
#define PE_HD_BACKGROUND_H
#if defined(PE2_PS5_HOST)
void peHdBackgroundRetire(void);
void peHdBackgroundBegin(void);
void peHdBackgroundEnd(void);
void peHdBackgroundRegister(const void *workspace,int contiguous);
void peHdBackgroundLoad(int x,int y,int w,int h,void *pixels);
#else
#define peHdBackgroundBegin() ((void)0)
#define peHdBackgroundEnd() ((void)0)
#define peHdBackgroundRetire() ((void)0)
#define peHdBackgroundRegister(workspace,contiguous) ((void)0)
#endif
#endif
