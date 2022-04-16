#ifndef __GRAPH_CONTAINER_H__
#define __GRAPH_CONTAINER_H__
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include "memory/ProfilableAllocator.h"

namespace PFA
{
    /**
     * @brief A vector using a profilable allocator.
     * @tparam T The type of the elements.
     * */
    template<typename T>
    using pvector=std::vector<T,ProfilableAllocator<T>>;

    /**
    * @brief A set using a profilable allocator.
    * @tparam Key The type of the keys.
    * @tparam Compare The type of the comparison function.
    * */
    template<
            class Key,
            class Compare = std::less<Key>
    > using pset = std::set<Key, Compare, ProfilableAllocator<Key>>;

    /**
    * @brief A map using a profilable allocator.
    * @tparam Key The type of the keys.
    * @tparam T The type of the associated value.
    * @tparam Compare The type of the comparison relation.
    * */
    template<
            class Key,
            class T,
            class Compare = std::less<Key>
            > using pmap = std::map<Key, T, Compare, ProfilableAllocator<std::pair<const Key, T>>>;

    /**
    * @brief An unordered map using a profilable allocator.
    * @tparam Key The type of the keys.
    * @tparam T The type of the associated value.
    * @tparam Hash a hash function for the keys.
    * @tparam KeyEqual an equivalence relation between the keys.
    * */
    template<
            class Key,
            class T,
            class Hash = std::hash<Key>,
            class KeyEqual = std::equal_to<Key>
    > using punordered_map= std::unordered_map<Key,T,Hash,KeyEqual,ProfilableAllocator<std::pair<const Key, T>>>;

    /**
    * @brief An unordered set using a profilable allocator.
    * @tparam Key The type of the keys.
    * @tparam Hash a hash function for the keys.
    * @tparam KeyEqual an equivalence relation between the keys.
    * */
    template<
            class Key,
            class Hash = std::hash<Key>,
            class KeyEqual = std::equal_to<Key>
    > using punordered_set= std::unordered_set<Key,Hash,KeyEqual,ProfilableAllocator<Key>>;


/**
 * @brief Any type that contains edges.
 * @details This concept describes the requirements for a container that contains edges.
 * @tparam Container Any container.
 * */
    template<typename Container>
    concept EdgeContainer = requires(Container &C,int a,int b)
    {
        C.addEdge(a, b);
        C.removeEdge(a, b);
        C.clearVertex(a);
    };

    template<typename T>
    class VectorIterator
    {
        int index;
        T *container;
    public:
        VectorIterator(T *c, int i=0) : index(i), container(c) {}
        VectorIterator(const VectorIterator &other) : index(other.index), container(other.container) {}
        VectorIterator &operator=(const VectorIterator &other)
        {
            index = other.index;
            container = other.container;
            return *this;
        }
        VectorIterator &operator++()
        {
            index++;
            return *this;
        }
        VectorIterator operator++(int)
        {
            VectorIterator tmp(*this);
            index++;
            return tmp;
        }
        VectorIterator &operator--()
        {
            index--;
            return *this;
        }
        VectorIterator operator--(int)
        {
            VectorIterator tmp(*this);
            index--;
            return tmp;
        }
        bool operator==(const VectorIterator &other) const
        {
            return index == other.index;
        }
        bool operator!=(const VectorIterator &other) const
        {
            return index != other.index;
        }
        std::pair<int,T&&>operator*()
        {
            return std::make_pair(index,std::forward<T>(container[index]));
        }
        std::pair<int,T*>operator->()
        {
            return std::make_pair(index,&container[index]);
        }
    };

    /**
    * @brief A 2D vector used to store adjacency lists.
    * @details This container is used to store adjacency lists.
    * @requires a Graph having positive integers as vertices, whose largest vertex is on the order of magnitude of the number of vertices.
    * @tparam Allocator the allocator used to allocate the memory.
    * */
template<template <typename > typename Allocator=std::allocator>
class VectorVectorContainer: public std::vector<std::vector<int,Allocator<int>>,Allocator<std::vector<int,Allocator<int>>>>
    {
        using val_type=std::vector<int,Allocator<int>>;
    public:
        using std::vector<std::vector<int,Allocator<int>>,Allocator<std::vector<int,Allocator<int>>>>::vector;
        void addEdge(int a,int b)
        {
            if(this->size()<a+1)
                this->resize(2*a+2);
            this->operator[](a).push_back(b);
        }

        void removeEdge(int a,int b)
        {
            if(this->size()<a+1)
                return;
            auto &v=this->operator[](a);
            auto it=std::find(v.begin(),v.end(),b);
            if(it!=v.end())
                v.erase(it);
        }

        void clearVertex(int a)
        {
            if(this->size()<a+1)
                return;
            this->operator[](a).clear();
        }

        auto begin()
        {
            return VectorIterator<val_type>(this->data());
        }

        auto end()
        {
            return VectorIterator<val_type>(this->data(),this->size());
        }

        auto begin() const
        {
            return VectorIterator<val_type>(this->data());
        }

        auto end() const
        {
            return VectorIterator<val_type>(this->data(),this->size());
        }
    };

    /**
    * @brief A vector over a set used to store adjacency lists.
    * @details This container is used to store adjacency lists.
    * @requires a Graph having positive integers as vertices, whose largest vertex is on the order of magnitude of the number of vertices.
    * @tparam Allocator the allocator used to allocate the memory.
    * */
template<template <typename > typename Allocator=std::allocator>
class VectorSetContainer: public std::vector<std::set<int,std::less<int>,Allocator<int>>,Allocator<std::set<int,std::less<int>,Allocator<int>>>>
    {
    using val_type=std::set<int,std::less<int>,Allocator<int>>;
public:
        using std::vector<std::set<int,std::less<int>,Allocator<int>>,Allocator<std::set<int,std::less<int>,Allocator<int>>>>::vector;
        void addEdge(int a,int b)
        {
            if(this->size()<a+1)
                this->resize(2*a+2);
            this->operator[](a).insert(b);
        }

        void removeEdge(int a,int b)
        {
            if(this->size()<a+1)
                return;
            this->operator[](a).erase(b);
        }

        void clearVertex(int a)
        {
            if(this->size()<a+1)
                return;
            this->operator[](a).clear();
        }
        auto begin()
        {
            return VectorIterator<val_type>(this->data());
        }

        auto end()
        {
            return VectorIterator<val_type>(this->data(),this->size());
        }

        auto begin() const
        {
            return VectorIterator<val_type>(this->data());
        }

        auto end() const
        {
            return VectorIterator<val_type>(this->data(),this->size());
        }
    };


    /**
    * @brief A vector over an unordered set used to store adjacency lists.
    * @details This container is used to store adjacency lists.
    * @requires a Graph having positive integers as vertices, whose largest vertex is on the order of magnitude of the number of vertices.
    * @tparam Allocator the allocator used to allocate the memory.
    * */
    template<template <typename > typename Allocator=std::allocator>
class VectorUnorderedSetContainer: public std::vector<std::unordered_set<int,std::hash<int>,std::equal_to<int>,Allocator<int>>,
        Allocator<std::unordered_set<int,std::hash<int>,std::equal_to<int>,Allocator<int>>>>
    {
    using val_type=std::unordered_set<int,std::hash<int>,std::equal_to<int>,Allocator<int>>;
public:
        using std::vector<std::unordered_set<int,std::hash<int>,std::equal_to<int>,Allocator<int>>,
                Allocator<std::unordered_set<int,std::hash<int>,std::equal_to<int>,Allocator<int>>>>::vector;
        void addEdge(int a,int b)
        {
            if(this->size()<a+1)
                this->resize(2*a+2);
            this->operator[](a).insert(b);
        }
        void removeEdge(int a,int b)
        {
            if(this->size()<a+1)
                return;
            this->operator[](a).erase(b);
        }

        void clearVertex(int a)
        {
            if(this->size()<a+1)
                return;
            this->operator[](a).clear();
        }
        auto begin()
        {
            return VectorIterator<val_type>(this->data());
        }

        auto end()
        {
            return VectorIterator<val_type>(this->data(),this->size());
        }

        auto begin() const
        {
            return VectorIterator<val_type>(this->data());
        }

        auto end() const
        {
            return VectorIterator<val_type>(this->data(),this->size());
        }
    };

    /**
    * @brief A map over a vector used to store adjacency lists.
    * @details This container is used to store adjacency lists.
    * @requires Integer vertices.
    * @tparam Allocator the allocator used to allocate the memory.
    * */
template<template <typename > typename Allocator=std::allocator>
class MapVectorContainer: public std::map<int,std::vector<int,Allocator<int>>,std::less<int>,
        Allocator<std::pair<const int,std::vector<int,Allocator<int>>>>>
    {
    public:
        using std::map<int,std::vector<int,Allocator<int>>,std::less<int>,
                Allocator<std::pair<const int,std::vector<int,Allocator<int>>>>>::map;
        void addEdge(int a,int b)
        {
            this->operator[](a).push_back(b);
        }
        void removeEdge(int a,int b)
        {
            if(!this->count(a))
                return;
            auto &v=this->operator[](a);
            auto it=std::find(v.begin(),v.end(),b);
            if(it!=v.end())
                v.erase(it);
        }

        void clearVertex(int a)
        {
            this->erase(a);
        }
    };

    /**
    * @brief A map over a set used to store adjacency lists.
    * @details This container is used to store adjacency lists.
    * @requires Integer vertices.
    * @tparam Allocator the allocator used to allocate the memory.
    * */
template<template <typename > typename Allocator=std::allocator>
class MapSetContainer: public std::map<int,std::set<int,std::less<int>,Allocator<int>>,std::less<int>,
        Allocator<std::pair<const int,std::set<int,std::less<int>,Allocator<int>>>>>
    {
    public:
        using std::map<int,std::set<int,std::less<int>,Allocator<int>>,std::less<int>,
        Allocator<std::pair<const int,std::set<int,std::less<int>,Allocator<int>>>>>::map;
        void addEdge(int a,int b)
        {
            this->operator[](a).insert(b);
        }

        void removeEdge(int a,int b)
        {
            if(this->count(a))
                this->operator[](a).erase(b);
        }

        void clearVertex(int a)
        {
            this->erase(a);
        }
    };

    /**
    * @brief A map over an unordered used to store adjacency lists.
    * @details This container is used to store adjacency lists.
    * @requires Integer vertices.
    * @tparam Allocator the allocator used to allocate the memory.
    * */
template<template <typename > typename Allocator=std::allocator>
class MapUnorderedSetContainer: public std::map<int,std::unordered_set<int,std::hash<int>,std::equal_to<int>,Allocator<int>>,std::less<int>,
        Allocator<std::pair<const int,std::unordered_set<int,std::hash<int>,std::equal_to<int>,Allocator<int>>>>>
    {
    public:
        using std::map<int,std::unordered_set<int,std::hash<int>,std::equal_to<int>,Allocator<int>>,std::less<int>,
                Allocator<std::pair<const int,std::unordered_set<int,std::hash<int>,std::equal_to<int>,Allocator<int>>>>>::map;
        void addEdge(int a,int b)
        {
            this->operator[](a).insert(b);
        }

    void removeEdge(int a,int b)
    {
        if(this->count(a))
            this->operator[](a).erase(b);
    }

    void clearVertex(int a)
    {
        this->erase(a);
    }
    };


    /**
    * @brief An unordered map over a vector used to store adjacency lists.
    * @details This container is used to store adjacency lists.
    * @requires Integer vertices.
    * @tparam Allocator the allocator used to allocate the memory.
    * */
    template<template <typename > typename Allocator=std::allocator>
    class UnorderedMapVectorContainer: public std::unordered_map<int,std::vector<int,Allocator<int>>,std::hash<int>,std::equal_to<int>,
            Allocator<std::pair<const int,std::vector<int,Allocator<int>>>>>
    {
    public:
        using std::unordered_map<int,std::vector<int,Allocator<int>>,std::hash<int>,std::equal_to<int>,
                Allocator<std::pair<const int,std::vector<int,Allocator<int>>>>>::unordered_map;
        void addEdge(int a,int b)
        {
            this->operator[](a).push_back(b);
        }

        void removeEdge(int a,int b)
        {
            if(!this->count(a))
                return;
            auto &v=this->operator[](a);
            auto it=std::find(v.begin(),v.end(),b);
            if(it!=v.end())
                v.erase(it);
        }

        void clearVertex(int a)
        {
            this->erase(a);
        }

    };

    /**
    * @brief An unordered map over a set used to store adjacency lists.
    * @details This container is used to store adjacency lists.
    * @requires Integer vertices.
    * @tparam Allocator the allocator used to allocate the memory.
    * */
    template<template <typename > typename Allocator=std::allocator>
    class UnorderedMapSetContainer: public std::unordered_map<int,std::set<int,std::less<int>,Allocator<int>>,std::hash<int>,std::equal_to<int>,
            Allocator<std::pair<const int,std::set<int,std::less<int>,Allocator<int>>>>>
    {
    public:
        using std::unordered_map<int,std::set<int,std::less<int>,Allocator<int>>,std::hash<int>,std::equal_to<int>,
                Allocator<std::pair<const int,std::set<int,std::less<int>,Allocator<int>>>>>::unordered_map;
        void addEdge(int a,int b)
        {
            this->operator[](a).insert(b);
        }

        void removeEdge(int a,int b)
        {
            if(this->count(a))
                this->operator[](a).erase(b);
        }

        void clearVertex(int a)
        {
            this->erase(a);
        }

    };

    /**
    * @brief An unordered map over an unordered set used to store adjacency lists.
    * @details This container is used to store adjacency lists.
    * @requires Integer vertices.
    * @tparam Allocator the allocator used to allocate the memory.
    * */
    template<template <typename > typename Allocator=std::allocator>
    class UnorderedMapUnorderedSetContainer: public std::unordered_map<int,std::unordered_set<int,std::hash<int>,std::equal_to<int>,Allocator<int>>,std::hash<int>,
            std::equal_to<int>,Allocator<std::pair<const int,std::unordered_set<int,std::hash<int>,std::equal_to<int>,Allocator<int>>>>>
    {
    public:
        using std::unordered_map<int,std::unordered_set<int,std::hash<int>,std::equal_to<int>,Allocator<int>>,std::hash<int>,
                std::equal_to<int>,Allocator<std::pair<const int,std::unordered_set<int,std::hash<int>,std::equal_to<int>,Allocator<int>>>>>::unordered_map;
        void addEdge(int a,int b)
        {
            this->operator[](a).insert(b);
        }

        void removeEdge(int a,int b)
        {
            if(this->count(a))
                this->operator[](a).erase(b);
        }

        void clearVertex(int a)
        {
            this->erase(a);
        }
    };
}

#endif
