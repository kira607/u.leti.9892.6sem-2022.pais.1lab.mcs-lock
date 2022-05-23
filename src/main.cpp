#include <iostream>
#include <thread>
#include <chrono>
#include <map>
#include "color/color.h"
#include "counter/counter.h"


bool dbg = false;


int get_threads_number()
{
    return int(std::thread::hardware_concurrency());
}

void job(Counter& c)
{
    if (dbg) std::cout << "Thread #" << std::this_thread::get_id() << ": hello from job\n";
    while(c.get() < 40000){
        c.getAndSet();
    }
    // std::this_thread::sleep_for(std::chrono::seconds(1));
}

void run_threads()
{
    int threads_number = get_threads_number();
    std::thread threads[threads_number];
    Counter c(0);
    for (int i = 0; i < threads_number; ++i)
    {
        threads[i] = std::thread(job, std::ref(c));
        if (dbg) std::cout << "Created thread #" << i + 1 << '/' << threads[i].get_id() << std::endl;
    }

    for (int i = 0; i < threads_number; ++i)
    {
        if (dbg) std::cout << "Trying to join #" << i + 1 << '/' << threads[i].get_id() << std::endl;
        if (threads[i].joinable())
        {
            if (dbg) std::cout << "Joining thread #" << i + 1 << '/' << threads[i].get_id() << std::endl;
            threads[i].join();
        }
        else
        {
            if (dbg) std::cout << "Not joinable: #" << i + 1 << '/' << threads[i].get_id() << std::endl;
        }
    }
}

double run_test(const int& number_of_threads)
{
    auto start = std::chrono::high_resolution_clock::now();
    run_threads();
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    return elapsed.count();
}

int main()
{
    int threads_number = get_threads_number();
    dbg = false;
    if (dbg) std::cout << "This computer has " << Color::kBlue << threads_number << Color::kNone << " threads\n";
    std::map<int, double> results;
    for(int i = 1; i < threads_number + 1; ++i)
    {
        std::cout << "Running test with " << i << " number of threads (";
        double t = run_test(i);
        std::cout << t << ")\n";
        results[i] = t;
    }
    for(auto pair : results){
        std::cout << "Threads num (" << pair.first << ") time: " << pair.second << '\n';
    }
    return 0;
}
