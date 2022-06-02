cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME 1lab_pas_3_2)
project(${PROJECT_NAME})
find_package(Threads REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
