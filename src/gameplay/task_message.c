#include "gameplay/message.h"

s32 taskMessageDispatch(Task* receiver, s32 messageId, TaskMessageWord firstArg, TaskMessageWord secondArg)
{
    const TaskMessageEntry* entry;

    if (receiver->msgTable == NULL) {
        return 0;
    }
    entry = receiver->msgTable;

    // Match the ID before testing the reserved end marker.
    if (entry->messageId != messageId) {
        do {
            if (entry->messageId == TASK_MESSAGE_TABLE_END) {
                return 0;
            }
            entry++;
        } while (entry->messageId != messageId);
    }
    return entry->handler(receiver, messageId, firstArg, secondArg);
}
