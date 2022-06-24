//
// Created by ramizouari on 07/04/2022.
//

#ifndef PFAPROJECT_SPLITCREATOR_H
#define PFAPROJECT_SPLITCREATOR_H
#include "graph.h"
#include "reader/ParallelReader.h"
#include "reader/ParallelReaderEdgeCentric.h"
#include "Edge_centric.h"
#include <future>
#include <regex>
#include <filesystem>
#include <thrust/allocate_unique.h>


namespace PFA
{
    template<EdgeContainer Container,template<typename> typename Allocator=std::allocator>
    class SplitCreator
    {
    private:
        std::launch strategy;
    public:
        explicit SplitCreator(std::launch strategy) : strategy(strategy) {}

        std::vector<Graph<Container>,Allocator<Graph<Container>>> createSplitsFromFiles(const std::vector<std::string> &fileNames) const
        {
            std::vector<std::future<Graph<Container>>> futures;
            for(const auto &fileName:fileNames)
                futures.push_back(std::async(strategy,&Graph<Container>::createGraphFromFile,fileName));
            std::vector<Graph<Container>,Allocator<Graph<Container>>> graphs;

            for(auto &future:futures)
                graphs.push_back(std::move(future.get()));
            PFA::punordered_map<int,PFA::punordered_set<int>> mapper;

            return graphs;

        }
        /**
     * @brief create graph splits from files defined by regex.
     * @details This function is used to create graph splits from files, Each file will be affected to its own graph-split. Then graph split will be rearrenged
     * adequately to avoid memory overflow.
     * @param fileRegEx regular expression matching the files to be read
     * */
        std::vector<Graph<Container>,Allocator<Graph<Container>>> createSplitsFromFileRegex(const std::string &fileRegEx) const
        {
            std::regex regex(fileRegEx);
            std::vector<std::string> fileNames;
            auto path=std::filesystem::path(fileRegEx).parent_path().string();
            for(const auto &dir: std::filesystem::directory_iterator(path))
            {
                if(!dir.is_regular_file())
                    continue;
                std::smatch match;
                auto name=dir.path().string();

                if(std::regex_match(name,match,regex))
                    fileNames.push_back(name);
            }
            return createSplitsFromFiles(fileNames);
        }

        /**
* @brief create graph splits from files defined by regex.
* @details This function is used to create graph splits from files, Each file will be affected to its own graph-split. Then graph split will be rearrenged
* adequately to avoid memory overflow.
* @param fileRegEx regular expression matching the files to be read
* */
        std::vector<Graph<Container>,Allocator<Graph<Container>>> createSplitsFromFile(const std::string &fileName,int count) const
        {
            ParallelReader<Container,Allocator> reader(fileName,count,strategy);
            std::vector<Graph<Container>,Allocator<Graph<Container>>> graphs;
            auto futures=reader.read();
            for(auto &future:futures)
                graphs.push_back(std::move(future.get()));
            return graphs;
        }
    };

    class SplitCreatorEdgeCentric
    {
    private:
        std::launch strategy;
    public:
        explicit SplitCreatorEdgeCentric(std::launch strategy) : strategy(strategy) {}

        /**
     * @brief create graph splits from files defined by regex.
     * @details This function is used to create graph splits from files, Each file will be affected to its own graph-split. Then graph split will be rearrenged
     * adequately to avoid memory overflow.
     * @param fileRegEx regular expression matching the files to be read
     * */


        /**
* @brief create graph splits from files defined by regex.
* @details This function is used to create graph splits from files, Each file will be affected to its own graph-split. Then graph split will be rearrenged
* adequately to avoid memory overflow.
* @param fileRegEx regular expression matching the files to be read
* */

    std::vector<Edge_centric> createSplitsFromFileEdgeCentric(const std::string &fileName,int count) const
    {
        ParallelReaderEdgeCentric reader(fileName,count,strategy);
        std::vector<Edge_centric> graphs;
        auto futures=reader.read();
        for(auto &future:futures)
            graphs.push_back(std::move(future.get()));
        return graphs;
    }
};

template<EdgeContainer Container,template<typename> typename Allocator=std::allocator>
    class SequentialSplitCreator : public PFA::SplitCreator<Container,Allocator>
    {
    public:
        SequentialSplitCreator() : PFA::SplitCreator<Container,Allocator>(std::launch::deferred) {}
    };
    template<EdgeContainer Container,template<typename> typename Allocator=std::allocator>
    class ParallelSplitCreator : public PFA::SplitCreator<Container,Allocator>
    {
    public:
        ParallelSplitCreator() : SplitCreator<Container,Allocator>(std::launch::async) {}
    };
    class ParallelSplitCreatorEdgeCentric : public PFA::SplitCreatorEdgeCentric
    {
    public:
        ParallelSplitCreatorEdgeCentric() : SplitCreatorEdgeCentric(std::launch::async) {}
    };
    template<EdgeContainer Container,template<typename> typename Allocator=std::allocator>
            inline SequentialSplitCreator<Container,Allocator> sequentialSplitCreator;

    template<EdgeContainer Container,template<typename> typename Allocator=std::allocator>
        inline ParallelSplitCreator<Container,Allocator> parallelSplitCreator;
        inline ParallelSplitCreatorEdgeCentric parallelSplitCreatorEdgeCentric;
}

#endif //PFAPROJECT_SPLITCREATOR_H
