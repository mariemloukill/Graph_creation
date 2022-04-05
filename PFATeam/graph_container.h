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
    template<typename T>
    using pvector=std::vector<T,ProfilableAllocator<T>>;
    template<
            class Key,
            class Compare = std::less<Key>
    > using pset = std::set<Key, Compare, ProfilableAllocator<Key>>;
    template<
            class Key,
            class T,
            class Compare = std::less<Key>
            > using pmap = std::map<Key, T, Compare, ProfilableAllocator<std::pair<const Key, T>>>;
    template<
            class Key,
            class T,
            class Hash = std::hash<Key>,
            class KeyEqual = std::equal_to<Key>
    > using punordered_map= std::unordered_map<Key,T,Hash,KeyEqual,ProfilableAllocator<std::pair<const Key, T>>>;

    template<
            class Key,
            class Hash = std::hash<Key>,
            class KeyEqual = std::equal_to<Key>
    > using punordered_set= std::unordered_set<Key,Hash,KeyEqual,ProfilableAllocator<Key>>;



    template<typename Container>
    concept EdgeContainer = requires(Container &C,int a,int b)
    {
        C.addEdge(a, b);
    };

template<template <typename > typename Allocator=std::allocator>
class VectorVectorContainer: public std::vector<std::vector<int,Allocator<int>>,Allocator<std::vector<int,Allocator<int>>>>
    {
    public:
        using std::vector<std::vector<int,Allocator<int>>,Allocator<std::vector<int,Allocator<int>>>>::vector;
        void addEdge(int a,int b)
        {
            if(this->size()<a+1)
                this->resize(2*a+2);
            this->operator[](a).push_back(b);
        }
    };

template<template <typename > typename Allocator=std::allocator>
class VectorSetContainer: public std::vector<std::set<int,std::less<int>,Allocator<int>>,Allocator<std::set<int,std::less<int>,Allocator<int>>>>
    {
    public:
        using std::vector<std::set<int,std::less<int>,Allocator<int>>,Allocator<std::set<int,std::less<int>,Allocator<int>>>>::vector;
        void addEdge(int a,int b)
        {
            if(this->size()<a+1)
                this->resize(2*a+2);
            this->operator[](a).insert(b);
        }
    };

    template<template <typename > typename Allocator=std::allocator>
class VectorUnorderedSetContainer: public std::vector<std::unordered_set<int,std::hash<int>,std::equal_to<int>,Allocator<int>>,
        Allocator<std::unordered_set<int,std::hash<int>,std::equal_to<int>,Allocator<int>>>>
    {
    public:
        using std::vector<std::unordered_set<int,std::hash<int>,std::equal_to<int>,Allocator<int>>,
                Allocator<std::unordered_set<int,std::hash<int>,std::equal_to<int>,Allocator<int>>>>::vector;
        void addEdge(int a,int b)
        {
            if(this->size()<a+1)
                this->resize(2*a+2);
            this->operator[](a).insert(b);
        }
    };


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
    };

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
    };

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
    };

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
    };

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
};

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
};
}

#endif
