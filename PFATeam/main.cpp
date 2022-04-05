#include <iostream>
#include "graph.h"
#include "graph_container.h"
#include <chrono>
#include "tester.h"
#include <filesystem>
#include "writer/writer.h"

int main(int argc, char** argv) 
{
    PFA::Tester tester(1);
    std::ofstream file("results.txt");
    PFA::JSONWriter writer(file);
    PFA::StandardWriter stdWriter(std::cout);
    PFA::MultipleWriter writers;
    writers.addWriter(writer);
    writers.addWriter(stdWriter);
    tester.writeGraphCreationAllImplementationsSequential("../datasets/test",writers);
}
