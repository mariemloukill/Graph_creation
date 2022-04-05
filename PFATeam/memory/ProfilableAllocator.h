//
// Created by ramizouari on 05/04/2022.
//

#ifndef PFAPROJECT_PROFILABLEALLOCATOR_H
#define PFAPROJECT_PROFILABLEALLOCATOR_H
#include <memory>
#include <iostream>

namespace PFA
{

    struct GlobalAllocator
    {
        inline static int allocated_memory=0;
        inline static int max_memory=0;
        static void resetMax()
        {
            max_memory=0;
        }
    };

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

        pointer   allocate(size_type n)
        {
            auto result=std::allocator<T>::allocate(n);
            if(result) {
                allocated_memory += n * sizeof(T);
                max_memory=std::max(max_memory,allocated_memory);
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
