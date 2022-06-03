//
// Created by ramizouari on 16/04/22.
//

#ifndef PFAPROJECT_PARALLELREADER_H
#define PFAPROJECT_PARALLELREADER_H
#include <fstream>
#include <vector>
#include <future>
#include <filesystem>
#include "graph/graphsplit.h"
namespace PFA {

    constexpr unsigned int fast_digit_count(unsigned int n)
    {
        if(n<10)
            return 1;
        if(n<100)
            return 2;
        if(n<1000)
            return 3;
        if(n<10000)
            return 4;
        if(n<100000)
            return 5;
        if(n<1000000)
            return 6;
        if(n<10000000)
            return 7;
        if(n<100000000)
            return 8;
        return 9;
    }

    template<typename Container,template <typename > typename Allocator=std::allocator>
    class ParallelReader {
        std::vector<std::ifstream,Allocator<std::ifstream>> files;
        size_t file_size;
        std::vector<size_t,Allocator<size_t>> pos;
        std::launch strategy;
        std::exception_ptr thread_exception;
        Graph<Container> read_chunk(int id)
        {
            size_t current_pos=pos[id];
            Graph<Container> G;
            int a,b;
            try {
                while ((files[id] >> a >> b) && current_pos < pos[id + 1] && !thread_exception) {
                    current_pos += fast_digit_count(a) + fast_digit_count(b) + 2;
                    G.adjacencyLists.addEdge(a, b);
                }
                if(thread_exception)
                    return {};
            }
            catch(...)
            {
                thread_exception=std::current_exception();
                std::rethrow_exception(thread_exception);
            }
            return G;
        }
    public:
        ParallelReader(const std::string &fileName, int nbThreads,std::launch strategy=std::launch::async):files(nbThreads),
        file_size(std::filesystem::file_size(fileName)),pos(nbThreads),strategy(strategy)
        {
            for(auto &file:files)
                file.open(fileName);
            for(int i=0;i<nbThreads;i++) {
                files[i].seekg(static_cast<std::streamoff>(static_cast<double>(i) / nbThreads * file_size));
                std::string line;
                std::getline(files[i], line);
                pos[i]=files[i].tellg();
            }
            std::ifstream file(fileName);
            file.seekg(0,std::ios::end);
            pos.push_back(file.tellg());
            file.close();
        };
        virtual ~ParallelReader() = default;
        auto read()
        {
            thread_exception=nullptr;
            // Allocator<std::future<std::vector<Graph<Container>,Allocator<Graph<Container>>>>>
            std::vector<std::future<Graph<Container>>,Allocator<std::future<Graph<Container>>>> futures;
            for(int i=0;i<files.size();i++)
                futures.emplace_back(std::async(strategy,&ParallelReader::read_chunk,this,i));
            if(thread_exception)
                std::rethrow_exception(thread_exception);
            return futures;
        }
    };

} // PFA

#endif //PFAPROJECT_PARALLELREADER_H
