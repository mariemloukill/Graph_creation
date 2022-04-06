//
// Created by ramizouari on 06/04/2022.
//

#ifndef PFAPROJECT_PARALLEL_GRAPH_H
#define PFAPROJECT_PARALLEL_GRAPH_H
#include "graph.h"
#include <filesystem>
#include <regex>
#include <fstream>
#include <execution>
#include <future>

namespace PFA {
    /**
 * @brief The Graph class
 * @details This class is used to represent a graph.
 * @author PFA Team
 * @param numberOfVertices Number of vertices
 * @tparam Container having a method addEdge(int,int)
 */
    template<EdgeContainer Container, template <typename T>typename  Allocator=std::allocator>
    std::vector<Graph<Container>,Allocator<Graph<Container>>> createFromFiles(std::string fileRegEx,int k)
    {
        std::regex regex(fileRegEx);
        std::vector<std::string> fileNames;
        using couple = std::pair<std::string,Graph<Container>>;
        std::vector<couple,Allocator<couple>> graphMap;
        auto path=std::filesystem::path(fileRegEx).parent_path().string();
        for(const auto &dir: std::filesystem::directory_iterator(path))
        {
            if(!dir.is_regular_file())
                continue;
            std::smatch match;
            auto name=dir.path().string();

            if(std::regex_match(name,match,regex))
            {
                graphMap.emplace_back();
                graphMap.back().first=name;
            }
        }
        std::vector<std::future<Graph<Container>>> futures;
        for(auto &[fileName,_]:graphMap)
            futures.push_back(std::async(std::launch::async,&Graph<Container>::createGraphFromFile,fileName));
        std::vector<Graph<Container>,Allocator<Graph<Container>>> graphs;

        for(auto &future:futures)
            graphs.push_back(std::move(future.get()));

        return graphs;
    }
};

#endif //PFAPROJECT_PARALLEL_GRAPH_H
