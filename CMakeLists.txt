cmake_minimum_required(VERSION 3.22)
project(1lab_pas_3_2)
find_package(Threads REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_CXX_STANDARD 14)

add_executable(1lab_pas_3_2 main.cpp color/color.cpp color/color.h)

target_link_libraries(1lab_pas_3_2 PRIVATE Threads::Threads)
