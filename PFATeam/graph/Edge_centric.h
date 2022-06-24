//
// Created by user on 17/06/22.
//

#ifndef PFAPROJECT_EDGE_CENTRIC_H
#define PFAPROJECT_EDGE_CENTRIC_H
#include "iostream"
#include<vector>
#include <fstream>

namespace PFA {

    class Edge_centric {
    public:
        std::vector <int> src; //vector containing the source of the edge
        std::vector <int> count; // vector containing the number of consecutive edge for a given node
        std::vector <int> dst;

        static Edge_centric createGraphFromFile(std::string path)
        {
            std::ifstream file(path);
            Edge_centric G;
            int a,b;
            while(file >> a >> b)
            {
                if ( (G.src.size()==0)|| (G.src.back()!=a))
                {
                    G.src.push_back(a);
                    G.count.push_back(1);
                }
                else
                {
                    G.count.back()++;
                }

                G.dst.push_back(b);
            }
            return G;
        }


    };
}

#endif //PFAPROJECT_EDGE_CENTRIC_H
