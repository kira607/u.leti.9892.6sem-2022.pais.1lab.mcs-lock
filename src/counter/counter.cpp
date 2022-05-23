#include "counter.h"

Counter::Counter(int initial): _n{initial} {}

int Counter::get() const
{
    return _n;
}

int Counter::getAndSet()
{
    _n += 1;
    return _n - 1;
}