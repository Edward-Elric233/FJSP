cmake_minimum_required(VERSION 3.20)
project(FJSP)

set(CMAKE_CXX_STANDARD 14)

include_directories(lib)

add_executable(FJSP src/main.cpp src/Occupy.cpp src/Occupy.h src/z3_env.h src/Machine.cpp src/Machine.h src/Order.cpp src/Order.h src/Job.cpp src/Job.h src/work.cpp src/work.h src/data.h src/z3_env.cpp src/data.cpp)

target_link_libraries(FJSP z3)
