#include <iostream>
#include "graph.h"
#include "graph_container.h"
#include <chrono>
#include "tester.h"
#include <filesystem>

int main(int argc, char** argv) 
{
    Tester tester(10);
    tester.testGraphsInFolder("../datasets");
}
