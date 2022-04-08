//
// Created by ramizouari on 05/04/2022.
//

#include "MemoryProfiler.h"
#include <iostream>
#include "cmemory.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "ProfilableAllocator.h"


using namespace PFA;
void StandardMemoryProfiler::run()
{
    if(writeHeader)
        out << R"(Time,Current Memory, Max Memory)" << std::endl;
    constexpr int MAX_TIME_SIZE=30;
    char time_representation[MAX_TIME_SIZE];
    std::fill_n(time_representation, MAX_TIME_SIZE, '\0');
    while(!endProfiler){
        auto t1=std::chrono::high_resolution_clock::now();
        out << boost::posix_time::microsec_clock::local_time() << ", " << GlobalAllocator::allocated_memory << ", " << GlobalAllocator::max_memory << std::endl;
        auto t2=std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(interval-(t2-t1));

    }
}

void ExteriorMemoryProfiler::run()
{
    out << R"(Time,Current Memory, Max Memory)" << std::endl;
    constexpr int MAX_TIME_SIZE=30;
    char time_representation[MAX_TIME_SIZE];
    std::fill_n(time_representation, MAX_TIME_SIZE, '\0');
    while(!endProfiler){
        auto t1=std::chrono::high_resolution_clock::now();
        if(!endProfiler) {
            double currentMemory = getCurrentRSS() / 1024.0 / 1024.0;
            double maxMemory = getPeakRSS() / 1024. /1024.;
            out << boost::posix_time::microsec_clock::local_time() << ", " << currentMemory << ", " << maxMemory << std::endl;
        }
        auto t2=std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(interval-(t2-t1));

    }
}

MemoryProfiler::MemoryProfiler(std::ostream &out,std::chrono::milliseconds interval,bool writeHeader):out(out),
std::thread(&MemoryProfiler::run,this),interval(interval),writeHeader(writeHeader){}


MemoryProfiler::MemoryProfiler(std::chrono::milliseconds interval,bool writeHeader):interval(interval),
std::thread(&MemoryProfiler::run, this),out(std::cout),writeHeader(writeHeader)
{
}

