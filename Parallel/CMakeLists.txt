cmake_minimum_required(VERSION 3.17)
project(Parallel)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread" )
set(CMAKE_CXX_STANDARD 14)


add_executable(Parallel main.cpp Graph.cpp Graph.h methods.cpp methods.h)