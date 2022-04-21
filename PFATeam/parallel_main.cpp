#include <iostream>
#include "graph/graph.h"
#include "graph/graph_container.h"
#include "graph/graphsplit.h"
#include <chrono>
#include "tester.h"
#include <filesystem>
#include "writer/writer.h"
#include "memory/MemoryProfiler.h"
#include "utils.h"

enum Mode
{
    DISCARD,RESUME,AUTO
};


size_t countLines(std::istream &I)
{
    return std::count(std::istreambuf_iterator<char>(I),
                      std::istreambuf_iterator<char>(), '\n');
}

using namespace PFA;
/**
 * @brief main function
 * @param  filename name of the file to be generated.
 * @param  mode mode of the file generation, either discard or resume. discard will redo all the calculations, resume will resume the calculations from the last point.
 * */
int main(int argc, char** argv)
{
    PFA::Tester tester(3);
    PFA::MultipleWriter writers;
    PFA::StandardWriter stdWriter(std::cout);
    writers.addWriter(stdWriter);
    if(argc > 1)
    {
        std::string fileName = argv[1];
        Mode mode = DISCARD;
        if(argc > 2)
        {
            std::string modeStr = argv[2];
            if(modeStr == "resume")
                mode = RESUME;
            else if(modeStr == "auto")
                mode = AUTO;
        }
        /*
         * Number of iterations to skip
         * Works only in resume mode
         * */
        int skip=0;
        std::ios::openmode openMode=std::ios::out;
        if(mode==RESUME)
        {
            openMode|=std::ios::app;
            /*
             * File containing last session, if it exists
             * */
            std::ifstream inFile(fileName + ".csv");
            if (inFile) {
                skip= countLines(inFile);
                inFile.close();
            }
        }
        else if(mode ==AUTO)
        {
            std::filesystem::path path(fileName+".csv");
            if(std::filesystem::exists(path))
            {
                std::ifstream inFile(path);
                if (inFile) {
                    skip= countLines(inFile);
                    inFile.close();
                }
            }
        }
        std::ofstream JSONFile(fileName+".json",openMode);
        std::ofstream CSVFile(fileName+".csv",openMode);
        std::ofstream profileFile(fileName+".profile",openMode);
        PFA::JSONWriter JSONWriter(JSONFile);
        PFA::CSVWriter CSVWriter(CSVFile);
        writers.addWriter(JSONWriter);
        writers.addWriter(CSVWriter);
        using  namespace std::chrono_literals;
        PFA::StandardMemoryProfiler profiler(profileFile,200ms);
        tester.writeGraphCreationAllImplementationsParallel<TestTypes>("datasets/parallel",writers,skip);
        profiler.endProfiler=true;
        profiler.join();
    }
    else tester.writeGraphCreationAllImplementationsParallel<TestTypes>("datasets",writers);
}
