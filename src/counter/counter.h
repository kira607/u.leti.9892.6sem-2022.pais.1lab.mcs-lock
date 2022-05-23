// simple counter

#ifndef INC_1LAB_PAS_3_2_COUNTER_COUNTER_H
#define INC_1LAB_PAS_3_2_COUNTER_COUNTER_H

class Counter
{
public:
    explicit Counter(int initial = 0);
    int get() const;
    int getAndSet();
private:
    int _n;
};

#endif //INC_1LAB_PAS_3_2_COUNTER_COUNTER_H
