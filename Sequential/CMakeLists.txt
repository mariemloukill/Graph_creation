cmake_minimum_required(VERSION 3.17)
project(Sequential)

set(CMAKE_CXX_STANDARD 14)

add_executable(Sequential main.cpp methods.cpp methods.h metrics.cpp metrics.h Sequential_Graph.cpp Sequential_Graph.h Split_Sequential_Graph.cpp Split_Sequential_Graph.h)