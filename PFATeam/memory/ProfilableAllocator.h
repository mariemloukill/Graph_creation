//
// Created by ramizouari on 05/04/2022.
//

#ifndef PFAPROJECT_PROFILABLEALLOCATOR_H
#define PFAPROJECT_PROFILABLEALLOCATOR_H
#include <memory>
#include <atomic>

namespace PFA
{
/**
 * @brief Global allocator that stores the size of the allocated memory, as well as the maximal size of the allocated memory.
 * @author PFA Team
 * @date 05/04/2022
 * */
    struct GlobalAllocator
    {
        inline static std::atomic<std::uint64_t> allocated_memory=0;
        inline static std::atomic<std::uint64_t> max_memory=0;
        static void resetMax()
        {
            max_memory=0;
        }
    };
    /**
     * @brief Allocator that extends both std::allocator and PFA::GlobalAllocator
     * @details This allocator is used to allocate and deallocate memory. It also keeps track of the allocated memory and the maximal allocated memory.
     * @author PFA Team
     * @date 05/04/2022
     * */
template <class T>
class ProfilableAllocator : public GlobalAllocator, public std::allocator<T>
    {
    public:
        typedef size_t    size_type;
        typedef ptrdiff_t difference_type;
        typedef T*        pointer;
        typedef const T*  const_pointer;
        typedef T&        reference;
        typedef const T&  const_reference;
        typedef T         value_type;
        using std::allocator<T>::allocator;

        pointer allocate(size_type n)
        {
            auto result=std::allocator<T>::allocate(n);
            if(result) {
                allocated_memory += n * sizeof(T);
                max_memory=std::max<std::uint64_t>(max_memory,allocated_memory);
            }
            return result;
        }

        void deallocate(void* p, size_type n) {
            std::allocator<T>::deallocate(static_cast<T*>(p), n);
            allocated_memory-=n*sizeof(T);
        }
    };
}
#endif //PFAPROJECT_PROFILABLEALLOCATOR_H
