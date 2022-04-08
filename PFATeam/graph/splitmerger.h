//
// Created by ramizouari on 07/04/2022.
//

#ifndef PFAPROJECT_SPLITMERGER_H
#define PFAPROJECT_SPLITMERGER_H
#include "graph.h"
#include "graphsplit.h"


namespace PFA
{
    /**
     * @brief A merging algorithm that merges two graphs.
     * @details This class is used to merge the split of the graph
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
        void merge(std::vector<Graph<Container>, Allocator<Graph<Container>>> &graphs) override
        {
            std::unordered_map<int,std::vector<int,Allocator<int>>,std::hash<int>,std::equal_to<int>,Allocator<std::pair<const int,std::vector<int,Allocator<int>>>>> mapper;
            for(int graphId=0;graphId<graphs.size();graphId++)
                for(auto &&edge:graphs[graphId].adjacencyList)
                    mapper[edge.first].push_back(graphId);

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
                    for(const auto &adjacenctVertex:graphs[representative].adjacencyList[vertex])
                        graphs[representative].addEdge(vertex,adjacenctVertex);
                    graphs[graphNumber].clearVertex(vertex);
                }
            }
        }
    };

}

#endif //PFAPROJECT_SPLITMERGER_H
