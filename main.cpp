#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include "color/color.h"


using namespace std::chrono_literals;


void print()
{
    // std::this_thread::sleep_for(1s);
    int i = 0;
    while (i < 1000000000){
        i--;
        ++i;
        i++;
    }
    std::cout << "Thread #" << std::this_thread::get_id() << ": hello from print\n";
}


int main()
{
    int threads_number = int(std::thread::hardware_concurrency());
    std::cout << "This computer has " << Color::kBlue << threads_number << Color::kNone << " threads\n";
    auto threads = std::vector<std::thread>(threads_number);

    for (int i = 0; i < threads_number; ++i)
    {
        std::thread t = std::thread(print);
        std::cout << "Created thread #" << i + 1 << '/' << t.get_id() << std::endl;
        threads.push_back(std::move(t));
    }
    for (int i = 0; i < threads_number; ++i)
    {
        std::thread t = std::move(threads.at(i));
        std::cout << "Trying to join #" << i + 1 << '/' << t.get_id() << std::endl;
        if (t.joinable())
        {
            std::cout << "Joining thread #" << i + 1 << '/' << t.get_id() << std::endl;
            t.join();
        }
        else std::cout << "Not joinable: #" << i + 1 << '/' << t.get_id() << std::endl;
    }
    return 0;
}
