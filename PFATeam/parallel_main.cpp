#include <iostream>
#include "graph/parallel_graph.h"
#include "graph/graph_container.h"
#include "graph/graphsplit.h"
#include <chrono>
#include "tester.h"
#include <filesystem>
#include "writer/writer.h"
#include "memory/MemoryProfiler.h"
#include "graph/graphsplit.h"
#include "graph/splitcreator.h"
#include "graph/splitmerger.h"


enum Mode
{
    DISCARD,RESUME
};

/**
 * @brief main function
 * @param  filename name of the file to be generated.
 * @param  mode mode of the file generation, either discard or resume. discard will redo all the calculations, resume will resume the calculations from the last point.
 * */
int main(int argc, char** argv)
{
    PFA::MapVectorContainer container;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    auto graphs=PFA::parallelSplitCreator<PFA::MapVectorContainer<PFA::ProfilableAllocator>,PFA::ProfilableAllocator>.createSplitsFromFileRegex("datasets/parallel/x.+");
    PFA::DefaultSplitMerger<PFA::MapVectorContainer<PFA::ProfilableAllocator>,PFA::ProfilableAllocator> merger;
    merger.merge(graphs);
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Memory: " << PFA::GlobalAllocator::max_memory << '\n';
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()/1000 << "ms" << '\n';
}
