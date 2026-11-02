#include "gameplay/message.h"
#include "gameplay/evs.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static s32 pointers(Task* task, s32 message, const int* input, int* output)
{
    (void)task; (void)message; *output = *input + 4; return 23;
}
static s32 numbers(Task* task, s32 message, s32 first, s32 second)
{
    (void)task; (void)message; return first - second;
}
static s32 mixed(Task* task, s32 message, const int* input, s32 offset)
{
    (void)task; (void)message; return *input + offset;
}
static s32 mixedSecond(Task* task, s32 message, s32 offset, const int* input)
{
    (void)task; (void)message; return *input + offset;
}
static int* callbackResult;
static void callbackPointer(void* pointer) { callbackResult = pointer; }
int main(void)
{
    int input = 17, output = 0;
    Task receiver = {0};
    TaskMessageEntry entries[] = {
        { 1, (TaskMessageHandler)pointers }, { 2, (TaskMessageHandler)numbers },
        { 3, (TaskMessageHandler)mixed }, { 4, (TaskMessageHandler)mixedSecond }, { TASK_MESSAGE_TABLE_END, NULL }
    };
    receiver.msgTable = entries;
    /* EVS reads the message view of a union initialized with a pointer. */
    EvsOperand first = { .storage = &input }, second = { .storage = &output };
    CHECK(taskMessageDispatch(&receiver, 1, first.message.value, second.message.value) == 23);
    CHECK(output == 21);
    output = 0;
    CHECK(TASK_MESSAGE_DISPATCH_POINTERS(&receiver, 1, &input, &output) == 23 && output == 21);
    CHECK(TASK_MESSAGE_DISPATCH_POINTER(&receiver, 3, &input, -5) == 12);
    CHECK(TASK_MESSAGE_DISPATCH_SECOND_POINTER(&receiver, 4, -6, &input) == 11);
    CHECK(taskMessageDispatch(&receiver, 2, -7, 4) == -11);
    CHECK(taskMessageDispatch(&receiver, 99, 0, 0) == 0);
    receiver.msgTable = NULL;
    CHECK(taskMessageDispatch(&receiver, 1, 0, 0) == 0);
    EvsOperand callback = { .callbackPointer = callbackPointer };
    callback.callback(first.message.value);
    CHECK(callbackResult == &input);
    printf("task messages and EVS preserve native pointers (%zu-bit)\n", sizeof(void*) * 8);
    return 0;
}
