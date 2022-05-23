#ifndef INC_1LAB_PAS_3_2_LOCK_MCS_LOCK_H
#define INC_1LAB_PAS_3_2_LOCK_MCS_LOCK_H

#include <atomic>

struct QNode
{
    std::atomic<QNode *> next;
    std::atomic<bool> locked;
};

class MscLock
{
public:
    void lock(QNode *p);
    void unlock(QNode *p);
private:
    std::atomic<QNode *> tail;
};

#endif //INC_1LAB_PAS_3_2_LOCK_MCS_LOCK_H
