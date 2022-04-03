#ifndef __GRAPH_HEADER__
#define __GRAPH_HEADER__
#include <fstream>
#include "graph_container.h"

/**
 * @brief The Graph class
 * @details This class is used to represent a graph.
 * @author PFA Team
 * @param numberOfVertices Number of vertices
 * @tparam Container having a method addEdge(int,int)
 */
template<EdgeContainer Container>
class Graph
{
    public:
        int numberOfVertices;
        Container adjacencyList;
        Graph():numberOfVertices(0){}
        explicit Graph(int numberOfVertices): numberOfVertices(numberOfVertices)
        {
            
        }
    
        static Graph createGraphFromFile(std::string path)
        {
            std::ifstream file(path);
            Graph G;
            int a,b;
            while(file >> a >> b)
                {
                    G.addEdge(a,b);
                    G.numberOfVertices=std::max(G.numberOfVertices,std::max(a,b));
                }
            return G;
        }
        
        void saveToFile(std::string path)
        {
            std::ofstream file(path);
            for(int i=0; i < numberOfVertices; i++)
            {
                for(auto j: adjacencyList[i])
                    file << i << " " << j << std::endl;
            }
        }

        void addEdge(int a, int b)
        { 
            adjacencyList.addEdge(a,b);
        }

        auto& getAdjacentNeighbors(int a)
        {
            return adjacencyList[a];
        }
};
#endif