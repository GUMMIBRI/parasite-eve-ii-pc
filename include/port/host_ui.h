#ifndef PE2_HOST_UI_H
#define PE2_HOST_UI_H
/* 1: start game, 0: host UI finished/cancelled, -1: invalid arguments/image. */
int peHostStartup(int argc, char** argv, const char** disc);
int peHostSwapDisc(int requiredDisc);
#endif
