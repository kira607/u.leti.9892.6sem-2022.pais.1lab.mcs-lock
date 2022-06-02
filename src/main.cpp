#include <iostream>
#include <thread>
#include <chrono>
#include <map>
#include <vector>
#include <atomic>
#include <algorithm>
#include <functional>

#define LOG(msg) {std::cout << msg;} while(0)

#define DBG

#ifdef DBG
#define DEBUG(msg) {LOG(msg);} while(0)
#else
#define DEBUG(msg) {} while(0)
#endif


int getThreadsNumber()
{
    return static_cast<int>(std::thread::hardware_concurrency());
}


template<typename Clock>
class Timer {
public:
    Timer() : _start_time(Clock::now()) {}
    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
    int elapsed_ms()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - _start_time).count();
    }
private:
    std::chrono::time_point<Clock> _start_time;
};


class McsLock {
public:
    McsLock(const McsLock&) = delete;
    McsLock& operator=(const McsLock&) = delete;
    McsLock(): _tail(nullptr) {}

    class ScopedLock
    {
    public:
        ScopedLock(const ScopedLock&) = delete;
        ScopedLock& operator=(const ScopedLock&) = delete;
        ScopedLock(McsLock &lock) : _lock(lock), _next(nullptr), _owned(false)
        {
            ScopedLock *tail = _lock._tail.exchange(this);
            if (tail != nullptr)
            {
                tail->_next = this;
                while (!_owned) {} /* spin */
            }
        }
        ~ScopedLock()
        {
            ScopedLock *tail = this;
            if (!_lock._tail.compare_exchange_strong(tail, nullptr))
            {
                while (_next == nullptr) {} /* spin */
                _next->_owned = true;
            }
        }
    private:
        McsLock &_lock;
        ScopedLock * volatile _next;
        volatile bool _owned;
    };
private:
    std::atomic<ScopedLock *> _tail;
};


template<class mutex, class lock_object>
class TestLock
{
public:
    explicit TestLock(
        const std::string &name,
        int spins = 1 << 15,
        int start = 0,
        int end = 0,
        std::function<void(mutex *m, int *val, std::size_t n)> job = TestLock::spinner
    )
    {
        _job = job;
        _name = name;
        _spins = spins > 0 ? spins : -spins;
        if(1 <= start && start <= getThreadsNumber()) _start = start; else _start = 1;
        if(_start <= end && end <= getThreadsNumber()) _end = end; else _end = getThreadsNumber();
    }
    std::map<int, int> run()
    {
        std::map<int, int> results;
        for (int i = _start; i <= _end; ++i)
        {
            DEBUG(_name << ": Running test with " << i << " number of threads (");
            int t = _testLock(i);
            DEBUG("took: " << t << "ms)\n");
            results[i] = t;
        }
        return results;
    }
    static void spinner(mutex *m, int *val, std::size_t n)
    {
        for (std::size_t i = 0; i < n; ++i)
        {
            lock_object lk(*m);
            (*val)++;
        }
    }

private:
    std::string _name;
    std::function<void(mutex *m, int *val, std::size_t n)> _job = TestLock::spinner;
    int _spins, _start, _end;

    int _testLock(std::size_t threads_number) {
        std::vector<std::thread> threads;
        mutex m;
        int i = 0;

        Timer<std::chrono::high_resolution_clock> t;
        DEBUG("spins: " << _spins << "; ");
        for(int thread_num = 0; thread_num < threads_number; ++thread_num)
        {
            threads.emplace_back(_job, &m, &i, _spins);
        }

        std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
        return t.elapsed_ms();
    }
};


int main()
{
    DEBUG("This computer has " << getThreadsNumber() << " threads\n");
    std::vector<int> times{1<<12, 1<<15, 1<<17, 1<<19};
    for(auto t : times)
    {
        std::cout << t << std::endl;
        TestLock<McsLock, McsLock::ScopedLock> tl("McsLock", t);
        auto results = tl.run();
    }
    return 0;
}
