//
// Created by ramizouari on 07/04/2022.
//

#ifndef PFAPROJECT_SPLITMERGER_H
#define PFAPROJECT_SPLITMERGER_H
#include "graph.h"
#include "graphsplit.h"
#include <random>


namespace PFA
{
    /**
     * @brief A merging algorithm that merges two graphs.
     * @details This class is used to merge the split of the graph using a deterministic algorithm.
     * @tparam Container The container used to store the graph.
     * @tparam Allocator The allocator used allocate memory.
     * @complexity O(n)
     */
    template<EdgeContainer Container, template<typename> typename Allocator=std::allocator>
    class SplitMerger
    {
    public:
        virtual ~SplitMerger() = default;
        virtual void merge(std::vector<Graph<Container>, Allocator<Graph<Container>>>  &graphs) = 0;
    };

    template<EdgeContainer Container, template<typename> typename Allocator=std::allocator>
    class DefaultSplitMerger:public SplitMerger<Container, Allocator>
    {
    public:
        virtual void merge(std::vector<Graph<Container>, Allocator<Graph<Container>>> &graphs) override
        {
            std::unordered_map<int,std::vector<int,Allocator<int>>,std::hash<int>,std::equal_to<int>,Allocator<std::pair<const int,std::vector<int,Allocator<int>>>>> mapper;
            for(int graphId=0;graphId<graphs.size();graphId++)
                for(auto &&outwardAdjacent:graphs[graphId].adjacencyList)
                    mapper[outwardAdjacent.first].push_back(graphId);

            for(auto &&[vertex,subGraphs]:mapper)
            {
                bool isFirst=true;
                int representative;
                for(const auto &graphNumber:subGraphs)
                {
                    if(isFirst)
                    {
                        representative=graphNumber;
                        isFirst=false;
                        continue;
                    }
                    for(const auto &adjacenctVertex:graphs[graphNumber].adjacencyList[vertex])
                        graphs[representative].addEdge(vertex,adjacenctVertex);
                    graphs[graphNumber].clearVertex(vertex);
                }
            }
        }
    };
    /**
 * @brief A randomized merging algorithm that merges two graphs.
 * @details This class is used to merge the split of the graph using a randomized algorithm
 * @tparam Container The container used to store the graph.
 * @tparam Allocator The allocator used allocate memory.
 * @tparam URBG A uniform bit random generator used to select the representative.
 * @complexity O(n)
 */
    template<EdgeContainer Container, template<typename> typename Allocator=std::allocator,
    typename URBG=std::mt19937_64>
    class RandomizedSplitMerger:public SplitMerger<Container, Allocator>
    {
        URBG rng;
    public:
        RandomizedSplitMerger() = default;
        explicit RandomizedSplitMerger(std::random_device &&d):rng(d()){}
        explicit RandomizedSplitMerger(URBG g):rng(std::move(g)){}
        void merge(std::vector<Graph<Container>, Allocator<Graph<Container>>> &graphs) override
        {
            std::unordered_map<int,std::vector<int,Allocator<int>>,std::hash<int>,std::equal_to<int>,Allocator<std::pair<const int,std::vector<int,Allocator<int>>>>> mapper;
            for(int graphId=0;graphId<graphs.size();graphId++)
                for(auto &&outwardAdjacent:graphs[graphId].adjacencyList)
                    mapper[outwardAdjacent.first].push_back(graphId);

            for(auto &&[vertex,subGraphs]:mapper)
            {
                bool isFirst=true;
                int representative;
                std::vector<int,Allocator<int>> tmp;
                std::sample(mapper[vertex].begin(),mapper[vertex].end(),std::back_inserter(tmp),1,rng);
                representative=tmp[0];
                for(const auto &graphNumber:subGraphs)
                {
                    if(graphNumber == representative)
                        continue;
                    for(const auto &adjacenctVertex:graphs[graphNumber].adjacencyList[vertex])
                        graphs[representative].addEdge(vertex,adjacenctVertex);
                    graphs[graphNumber].clearVertex(vertex);
                }
            }
        }
    };


    template<EdgeContainer Container, template<typename> typename Allocator=std::allocator>
    class OneGraphSplitMerger
    {
        int graphRepresentative;
    public:
        OneGraphSplitMerger(int representative=0):graphRepresentative(representative){}
        Graph<Container>& merge(std::vector<Graph<Container>, Allocator<Graph<Container>>> &graphs)
        {
//            std::unordered_map<int,std::vector<int,Allocator<int>>,
//                    std::hash<int>,std::equal_to<int>,
//                            Allocator<std::pair<const int,std::vector<int,Allocator<int>>>>> mapper;
            graphs[0].adjacencyList.swap(graphs[graphRepresentative].adjacencyList);
            for(int graphId=graphs.size()-1;graphId>0;graphId--)
            {
                for(auto outwardAdjacent:graphs[graphId].adjacencyList)
                    if constexpr (std::is_same_v<Container,std::list<int,Allocator<int>>>)
                        graphs[graphRepresentative].adjacencyList[outwardAdjacent.first].splice(
                                graphs[graphRepresentative].adjacencyList[outwardAdjacent.first].begin(),
                                outwardAdjacent.second);
                    else for(auto adjacent:outwardAdjacent.second)
                        graphs.front().addEdge(outwardAdjacent.first,adjacent);
                graphs.pop_back();
            }


//            for(auto &&[vertex,subGraphs]:mapper)
//            {
//                for(const auto &graphNumber:subGraphs)
//                {
//                    if(graphNumber == graphRepresentative)
//                        continue;
//                    for(const auto &adjacentVertex:graphs[graphNumber].adjacencyList[vertex])
//                        graphs[graphRepresentative].addEdge(vertex,adjacentVertex);
//                    graphs[graphNumber].clearVertex(vertex);
//                }
//            }
            return graphs.front();
        }
    };

}

#endif //PFAPROJECT_SPLITMERGER_H
