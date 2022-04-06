#ifndef __GRAPH_HEADER__
#define __GRAPH_HEADER__
#include <fstream>
#include "graph/graph_container.h"



namespace PFA {
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
        explicit Graph(int numberOfVertices): numberOfVertices(numberOfVertices) {}


        /**
         * @brief Create a Graph From a file
         *
         * @param path path of the graph file
         * @return Graph
         */

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

        /**
         * @brief Save a graph to a file
         *
         * @param path
         */
        void saveToFile(std::string path)
        {
            std::ofstream file(path);
            for(int i=0; i < numberOfVertices; i++)
            {
                for(auto j: adjacencyList[i])
                    file << i << " " << j << std::endl;
            }
        }

        /**
         * @brief Add an edge to the adjacency list
         *
         * @param a first vertex
         * @param b second vertex
         */
        void addEdge(int a, int b)
        {
            adjacencyList.addEdge(a,b);
        }

        /**
         * @brief Get the Neighbors of a vertex
         *
         * @param a vertex
         * @return auto& neighbors of the vertex
         */
        auto& getAdjacentNeighbors(int a)
        {
            return adjacencyList[a];
        }
    };
};
#endif