//
// Created by ramizouari on 05/04/2022.
//

#ifndef PFAPROJECT_MEMORYPROFILER_H
#define PFAPROJECT_MEMORYPROFILER_H
#include <thread>
#include <atomic>

namespace PFA {
    class MemoryProfiler : public std::thread {
        void run();
        std::atomic<bool> endProfiler = false;
        std::ostream& out;
        std::chrono::milliseconds interval;
    public:
        MemoryProfiler(std::ostream &out,std::chrono::milliseconds interval=std::chrono::milliseconds(1000));
        MemoryProfiler(std::chrono::milliseconds interval=std::chrono::milliseconds(1000));
    };
}


#endif //PFAPROJECT_MEMORYPROFILER_H
