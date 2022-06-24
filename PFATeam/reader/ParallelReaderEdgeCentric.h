//
// Created by user on 20/06/22.
//

#ifndef PFAPROJECT_PARALLELREADEREDGECENTRIC_H
//
// Created by ramizouari on 16/04/22.
//

#include <fstream>
#include <vector>
#include <future>
#include <filesystem>
#include "graph/graphsplit.h"
#include "graph/Edge_centric.h"

namespace PFA {


    class ParallelReaderEdgeCentric {
        std::vector<std::ifstream> files;
        size_t file_size;
        std::vector<size_t> pos;
        std::launch strategy;
        std::exception_ptr thread_exception;
        Edge_centric read_chunk(int id)
        {
            size_t current_pos=pos[id];
            Edge_centric G;
            int a,b;
            try {
                while ((files[id] >> a >> b) && current_pos < pos[id + 1] && !thread_exception) {
                    current_pos += fast_digit_count(a) + fast_digit_count(b) + 2;
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
        ParallelReaderEdgeCentric(const std::string &fileName, int nbThreads,std::launch strategy=std::launch::async):files(nbThreads),
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
        virtual ~ParallelReaderEdgeCentric() = default;
        auto read()
        {
            thread_exception=nullptr;
            // Allocator<std::future<std::vector<Graph<Container>,Allocator<Graph<Container>>>>>
            std::vector<std::future<Edge_centric>> futures;
            for(int i=0;i<files.size();i++)
                futures.emplace_back(std::async(strategy,&ParallelReaderEdgeCentric::read_chunk,this,i));
            if(thread_exception)
                std::rethrow_exception(thread_exception);
            return futures;
        }
    };

} // PFA



#define PFAPROJECT_PARALLELREADEREDGECENTRIC_H

#endif //PFAPROJECT_PARALLELREADEREDGECENTRIC_H
