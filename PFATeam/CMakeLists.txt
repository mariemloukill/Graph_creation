cmake_minimum_required(VERSION 3.21)
project(PFAProject)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost 1.70)
include_directories(${CMAKE_SOURCE_DIR})
if(Boost_FOUND)
    set(Boost_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})
    set(Boost_LIBRARIES ${Boost_LIBRARIES})
endif()
add_executable(PFAProject main.cpp tester.cpp writer/writer.cpp writer/writer.h memory/cmemory.h memory/MemoryProfiler.cpp memory/MemoryProfiler.h memory/ProfilableAllocator.h graph/parallel_graph.h)
add_executable(PFAProjectParallel parallel_main.cpp tester.cpp writer/writer.cpp writer/writer.h memory/cmemory.h memory/MemoryProfiler.cpp memory/MemoryProfiler.h memory/ProfilableAllocator.h graph/parallel_graph.h)

