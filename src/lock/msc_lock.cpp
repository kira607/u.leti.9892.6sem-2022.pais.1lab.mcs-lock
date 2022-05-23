# include "msc_lock.h"

void MscLock::lock(QNode *p)
{
    p->next.store(nullptr);
    p->locked.store(true);

    QNode *prev = tail.exchange(p, std::memory_order_acq_rel);

    if (prev) 
    {
        prev->next.store(p, std::memory_order_release);
        while (p->locked.load(std::memory_order_acquire)){};  // spin
    }
}

void MscLock::unlock(QNode *p)
{
    QNode *successor = p->next.load(std::memory_order_acquire);
    if (!successor)
    {
        auto e = p;
        if (tail.compare_exchange_strong(e, nullptr, std::memory_order_acq_rel))
        {
            return;
        }

        do 
        {
            successor = p->next.load(std::memory_order_acquire);
        } while (successor == nullptr);
    }

    successor->wait.store(false, std::memory_order_release);
}