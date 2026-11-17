/* MPL-2.0. Native-only PE2 controls; original game owns transitions. */
#ifndef PE_QOL_CONTROLS_H
#define PE_QOL_CONTROLS_H
enum { PE_QOL_SKIP=1, PE_QOL_PAUSE_TOGGLE=2, PE_QOL_RETURN_TITLE_CONFIRMED=4,
       PE_QOL_EXIT_GAME_CONFIRMED=8,
       PE_QOL_HALT_BIT=16, PE_QOL_HALT_MASK=1<<PE_QOL_HALT_BIT };
#if defined(PE2_PS5_HOST)
/* Host UI confirms loss of unsaved progress BEFORE requesting return-title.
 * Calls are thread-safe. Requests are one-shot, never deferred through locks. */
void peQolRequest(unsigned action);
void peQolSetSpeedHeld(int held,unsigned factor);
void peQolSetUiBlocked(int blocked);
void peQolReset(void);
/* Game main loop owns these calls; never call them from host event handlers. */
unsigned peQolPoll(unsigned allowedActions,int speedAllowed);
int peQolTakeSkip(void);
#else
#define peQolReset() ((void)0)
#define peQolPoll(a,b) 0u
#define peQolTakeSkip() 0
#endif
#endif
