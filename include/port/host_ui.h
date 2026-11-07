#ifndef PE2_HOST_UI_H
#define PE2_HOST_UI_H
/* 1: start game, 0: host UI finished/cancelled, -1: invalid arguments/image. */
int peHostStartup(int argc, char** argv, const char** disc);
int peHostSwapDisc(int requiredDisc);
/* Logs an error and, when no terminal shows the log, also shows it in a message window naming the log file. */
void peHostReportError(const char* format, ...)
#if defined(__GNUC__) || defined(__clang__)
    __attribute__((format(printf, 1, 2)))
#endif
    ;
#endif
