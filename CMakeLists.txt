cmake_minimum_required(VERSION 3.15)
project(1lab_pas_3_2)
find_package(Threads REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_CXX_STANDARD 14)

add_executable(
    1lab_pas_3_2
        src/main.cpp

        src/color/color.cpp
        src/color/color.h

        src/counter/counter.cpp
        src/counter/counter.h
)

target_link_libraries(1lab_pas_3_2 PRIVATE Threads::Threads)
