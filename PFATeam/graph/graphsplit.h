//
// Created by ramizouari on 07/04/2022.
//

#ifndef PFAPROJECT_GRAPHSPLIT_H
#define PFAPROJECT_GRAPHSPLIT_H

#include "graph.h"
#include <filesystem>
#include <regex>
#include <fstream>
#include <execution>
#include <future>

namespace PFA {


    template<EdgeContainer Container,template <typename> typename Allocator=std::allocator>
    class GraphSplit
    {
    public:
        GraphSplit() = default;
        GraphSplit(std::vector<Graph<Container>,Allocator<Graph<Container>>> _graphs) : graphs(std::move(_graphs)) {}
        std::vector<Graph<Container>,Allocator<Graph<Container>>> graphs;
        std::unordered_map<int,std::vector<int>,std::hash<int>,std::equal_to<int>,Allocator<std::pair<const int,std::vector<int>>>> keyGraphs;
        /**
         * @brief create graph splits from files
         * @details This function is used to create graph splits from files, Each file will be affected to its own graph-split. Then graph split will be rearrenged
         * adequately to avoid memory overflow.
         * @param fileRegEx regular expression matching the files to be read
         * */
        static std::vector<Graph<Container>,Allocator<Graph<Container>>> createGraphsFromFiles(std::string fileRegEx)
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
                futures.push_back(std::async(std::launch::deferred,&Graph<Container>::createGraphFromFile,fileName));
            std::vector<Graph<Container>,Allocator<Graph<Container>>> graphs;

            for(auto &future:futures)
                graphs.push_back(std::move(future.get()));
            PFA::punordered_map<int,PFA::punordered_set<int>> mapper;

            return graphs;
        }
    };
};

#endif //PFAPROJECT_GRAPHSPLIT_H
