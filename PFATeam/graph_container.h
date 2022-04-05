#ifndef __GRAPH_CONTAINER_H__
#define __GRAPH_CONTAINER_H__
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

namespace PFA
{
    template<typename Container>
    concept EdgeContainer = requires(Container &C,int a,int b)
    {
        C.addEdge(a, b);
    };

    class VectorVectorContainer: public std::vector<std::vector<int>>
    {
    public:
        using std::vector<std::vector<int>>::vector;
        void addEdge(int a,int b)
        {
            if(this->size()<a+1)
                this->resize(2*a+2);
            this->operator[](a).push_back(b);
        }
    };


    class VectorSetContainer: public std::vector<std::set<int>>
    {
    public:
        using std::vector<std::set<int>>::vector;
        void addEdge(int a,int b)
        {
            if(this->size()<a+1)
                this->resize(2*a+2);
            this->operator[](a).insert(b);
        }
    };

    class VectorUnorderedSetContainer: public std::vector<std::unordered_set<int>>
    {
    public:
        using std::vector<std::unordered_set<int>>::vector;
        void addEdge(int a,int b)
        {
            if(this->size()<a+1)
                this->resize(2*a+2);
            this->operator[](a).insert(b);
        }
    };


    class MapVectorContainer: public std::map<int,std::vector<int>>
    {
    public:
        using std::map<int,std::vector<int>>::map;
        void addEdge(int a,int b)
        {
            this->operator[](a).push_back(b);
        }
    };


    class MapSetContainer: public std::map<int,std::set<int>>
    {
    public:
        using std::map<int,std::set<int>>::map;
        void addEdge(int a,int b)
        {
            this->operator[](a).insert(b);
        }
    };

    class MapUnorderedSetContainer: public std::map<int,std::unordered_set<int>>
    {
    public:
        using std::map<int,std::unordered_set<int>>::map;
        void addEdge(int a,int b)
        {
            this->operator[](a).insert(b);
        }
    };


    class UnorderedMapVectorContainer: public std::unordered_map<int,std::vector<int>>
    {
    public:
        using std::unordered_map<int,std::vector<int>>::unordered_map;
        void addEdge(int a,int b)
        {
            this->operator[](a).push_back(b);
        }
    };


    class UnorderedMapSetContainer: public std::unordered_map<int,std::set<int>>
    {
    public:
        using std::unordered_map<int,std::set<int>>::unordered_map;
        void addEdge(int a,int b)
        {
            this->operator[](a).insert(b);
        }
    };

    class UnorderedMapUnorderedSetContainer: public std::unordered_map<int,std::unordered_set<int>>
    {
    public:
        using std::unordered_map<int,std::unordered_set<int>>::unordered_map;
        void addEdge(int a,int b)
        {
            this->operator[](a).insert(b);
        }
    };
}

#endif
