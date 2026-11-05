#ifndef PE2_PS5_PATHS_H
#define PE2_PS5_PATHS_H
/* PS5 build only. Process-owned strings; explicit options take precedence. */
const char* pePs5ConfigDirectory(void);
const char* pePs5CardDirectory(void);
const char* pePs5FindDisc(int number, const char* companion);
#endif
