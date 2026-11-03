#ifdef NDEBUG
#undef NDEBUG
#endif
#include "main/task.h"
#include "../src/main/task.h"
#include "main/display_types.h"
#include "main/mem.h"
#include "gameplay/model_objects.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DisplayState gDisplayState;
static unsigned freed;
void taskNoopCallback(Task* unused) { (void)unused; }

/* Model the host allocator's cleared retired task storage. Sanitized runs also
 * catch any read after free; ordinary runs reproduce the observed NULL link. */
void memFree(void* allocation)
{
    assert(allocation);
    memset(allocation, 0, sizeof(Task));
    free(allocation);
    ++freed;
}
void modelObjectUnlinkTmd(TmdListNode* node) { (void)node; abort(); }
void modelObjectFreeTmd(TmdObject* model) { (void)model; abort(); }
void modelObjectUnlinkCoordBody(TmdListNode* node) { (void)node; abort(); }
void modelObjectFreeCoordBody(ModelObjectCoordBody* body) { (void)body; abort(); }

static void retire_child(Task* task)
{
    assert(task->parent == NULL);
    taskKill(task);
}

static Task* make_task(void)
{
    Task* task = calloc(1, sizeof(*task));
    assert(task);
    task->callback = taskNoopCallback;
    task->exitCallback = retire_child;
    task->nextSibling = task;
    /* Execution lists are linear, with a bare head and a tail backlink. */
    task->node.prev = gTaskDefaultList.prev;
    gTaskDefaultList.prev->next = task;
    gTaskDefaultList.prev = &task->node;
    return task;
}

static void run(unsigned children, int nested, int immediate)
{
    memset(&gDisplayState, 0, sizeof(gDisplayState));
    gDisplayState.immediateTaskFree = immediate;
    gTaskDefaultList.next = NULL;
    gTaskDefaultList.prev = &gTaskDefaultList;
    freed = 0;
    Task* parent = make_task();
    Task* first = make_task();
    parent->firstChild = first;
    first->parent = parent;
    if (children == 2) {
        Task* second = make_task();
        second->parent = parent;
        first->nextSibling = second;
        second->nextSibling = first;
    }
    if (nested) {
        Task* grandchild = make_task();
        first->firstChild = grandchild;
        grandchild->parent = first;
    }
    taskKill(parent);
    unsigned expected = 1 + children + nested;
    if (!immediate) {
        assert(freed == 0);
        taskExecList(&gTaskDefaultList);
    }
    assert(freed == expected);
    assert(gTaskDefaultList.next == NULL);
    assert(gTaskDefaultList.prev == &gTaskDefaultList);
}

int main(void)
{
    run(1, 0, 1);
    run(2, 0, 1);
    run(2, 1, 1);
    run(2, 1, 0);
    puts("Task child teardown: immediate, sibling ring, nested and deferred OK");
}
