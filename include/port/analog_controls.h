/* MPL-2.0. Native PE2 input policy; original actor movement remains authoritative. */
#ifndef PE2_ANALOG_CONTROLS_H
#define PE2_ANALOG_CONTROLS_H
struct Task;
int peAnalogControlsMode(void);
void peAnalogControlsSetMode(int direct);
/* Default-off run preference; held original run button becomes walk. */
int peAlwaysRun(void);
void peAlwaysRunSet(int enabled);
unsigned peAnalogRunThreshold(void);
void peAnalogSetRunThreshold(unsigned percent);
/* Read-only access to the existing logical input suppression owner. */
unsigned peAnalogInputSuppressionMask(void);
/* Called once at the real normal-player input seam; never polls or moves time. */
void peAnalogUpdateNormalInput(struct Task *task);
/* Installs only the sampled input yaw, before the original facing matrix update. */
int peAnalogApplyNormalFacing(struct Task *task);
#endif
