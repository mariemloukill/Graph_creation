//
// Created by ramizouari on 21/04/22.
//

#ifndef PFAPROJECT_TYPES_H
#define PFAPROJECT_TYPES_H
#include "boost/mp11/mpl.hpp"
#include "memory/ProfilableAllocator.h"
#include "graph/graph_container.h"

namespace PFA
{
    using TestTypes=boost::mp11::mp_list<VectorVectorContainer<ProfilableAllocator>,
    VectorSetContainer<ProfilableAllocator>,
    VectorUnorderedSetContainer<ProfilableAllocator>,
    MapVectorContainer<ProfilableAllocator>,
    MapSetContainer<ProfilableAllocator>,
    MapUnorderedSetContainer<ProfilableAllocator>,
    UnorderedMapVectorContainer<ProfilableAllocator>,
    UnorderedMapSetContainer<ProfilableAllocator>,
    UnorderedMapUnorderedSetContainer<ProfilableAllocator>>;

    using CurrentType=boost::mp11::mp_list<VectorVectorContainer<ProfilableAllocator>>;
    using AlternativeType=boost::mp11::mp_list<VectorSetContainer<ProfilableAllocator>>;
}

#endif //PFAPROJECT_TYPES_H
