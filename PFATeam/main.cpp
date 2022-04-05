#include <iostream>
#include "graph.h"
#include "graph_container.h"
#include <chrono>
#include "tester.h"
#include <filesystem>
#include "writer/writer.h"
#include "memory/MemoryProfiler.h"

int main(int argc, char** argv) 
{
    PFA::Tester tester(10);
    PFA::MultipleWriter writers;
    PFA::StandardWriter stdWriter(std::cout);
    writers.addWriter(stdWriter);
    if(argc > 1)
    {
        std::string fileName = argv[1];
        std::ofstream JSONFile(fileName+".json");
        std::ofstream CSVFile(fileName+".csv");
        std::ofstream profileFile(fileName+".profile");
        PFA::JSONWriter JSONWriter(JSONFile);
        PFA::CSVWriter CSVWriter(CSVFile);
        writers.addWriter(JSONWriter);
        writers.addWriter(CSVWriter);
        using  namespace std::chrono_literals;
        PFA::MemoryProfiler profiler(profileFile,200ms);
        tester.writeGraphCreationAllImplementationsSequential("datasets",writers);
    }
    else tester.writeGraphCreationAllImplementationsSequential("datasets",writers);
}
