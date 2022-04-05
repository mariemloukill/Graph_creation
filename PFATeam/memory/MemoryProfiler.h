//
// Created by ramizouari on 05/04/2022.
//

#ifndef PFAPROJECT_MEMORYPROFILER_H
#define PFAPROJECT_MEMORYPROFILER_H
#include <thread>
#include <atomic>

namespace PFA {
    /**
     * @brief an abstract class for memory profiling.
     * @details this class is used to profile the memory usage of a program, periodically.
     * @author PFA Team
     * */
    class MemoryProfiler : public std::thread {
    protected:
        /**
         * @brief The main thread for profiling.
         * */
        virtual void run()=0;
        std::ostream& out;
        std::chrono::milliseconds interval;
    public:
        std::atomic<bool> endProfiler = false;
        MemoryProfiler(std::ostream &out,std::chrono::milliseconds interval=std::chrono::milliseconds(1000));
        MemoryProfiler(std::chrono::milliseconds interval=std::chrono::milliseconds(1000));
    };
    /**
     * @brief a class for profiling using OS dependent features.
     * @details this class is used to profile the memory usage of a program, periodically, using OS dependent features. It only works on Linux, Windows & Mac.
     * @author PFA Team
     * */
    class ExteriorMemoryProfiler : public MemoryProfiler {
        void run() override;
    public:
        using MemoryProfiler::MemoryProfiler;
    };

    /**
 * @brief a class for profiling using ProfilableAllocators.
 * @details this class is used to profile the memory usage of a program, periodically, using a custom allocator that stores the size of the allocated memory.
 * @author PFA Team
 * */
    class StandardMemoryProfiler : public MemoryProfiler {
        void run() override;
    public:
        using MemoryProfiler::MemoryProfiler;
    };
}


#endif //PFAPROJECT_MEMORYPROFILER_H
