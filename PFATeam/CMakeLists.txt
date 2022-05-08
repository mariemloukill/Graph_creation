cmake_minimum_required(VERSION 3.21)
project(PFAProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-11")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -ltbb")
find_package(Boost 1.70 COMPONENTS program_options)
find_package(TBB REQUIRED)

find_package(Boost 1.70 COMPONENTS program_options chrono)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${Boost_INCLUDE_DIRS})
if(Boost_FOUND)
    set(Boost_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})
    set(Boost_LIBRARIES ${Boost_LIBRARIES})
endif()
add_executable(PFAProject main.cpp tester.cpp writer/writer.cpp writer/writer.h memory/cmemory.h memory/MemoryProfiler.cpp memory/MemoryProfiler.h memory/ProfilableAllocator.h graph/graphsplit.h graph/splitcreator.h graph/splitmerger.h utils/types.h utils/utils.h)
add_executable(PFAProjectParallel parallel_main.cpp tester.cpp writer/writer.cpp writer/writer.h memory/cmemory.h memory/MemoryProfiler.cpp memory/MemoryProfiler.h memory/ProfilableAllocator.h graph/splitcreator.h graph/splitmerger.h reader/ParallelReader.h utils/types.h utils/utils.h)
add_executable(PFAProjectCFG main_cfg.cpp tester.cpp writer/writer.cpp writer/writer.h memory/cmemory.h memory/MemoryProfiler.cpp memory/MemoryProfiler.h memory/ProfilableAllocator.h graph/splitcreator.h graph/splitmerger.h reader/ParallelReader.h utils/types.h utils/utils.h)
target_link_libraries(PFAProject PRIVATE TBB::tbb)
target_link_libraries(PFAProjectParallel PRIVATE ${Boost_LIBRARIES} TBB::tbb)
target_link_libraries(PFAProjectCFG ${Boost_LIBRARIES} TBB::tbb)


