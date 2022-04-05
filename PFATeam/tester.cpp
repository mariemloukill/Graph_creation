#include "tester.h"
#include <iostream>
#include <filesystem>

using namespace PFA;
Tester::Tester(int numberOfTrials):numberOfTrials(numberOfTrials)  {}

void Tester::printAvgTestResult(std::string type, double avg){
        std::cout << std::left << std::setfill('.') << std::setw(40) << type << std::right << std::setfill('.') << std::setw(40) << avg << " ms" << std::endl;
}

void Tester::testAllImplementationsSequential(std::string path){

            printAvgTestResult("VectorVectorContainer", this->testAvgGraphCreation<VectorVectorContainer>(path));

            printAvgTestResult("VectorSetContainer", this->testAvgGraphCreation<VectorSetContainer>(path));

            printAvgTestResult("VectorUnorderedSetContainer", this->testAvgGraphCreation<VectorUnorderedSetContainer>(path));

            printAvgTestResult("MapVectorContainer", this->testAvgGraphCreation<MapVectorContainer>(path));

            printAvgTestResult("MapSetContainer", this->testAvgGraphCreation<MapSetContainer>(path));

            printAvgTestResult("MapUnorderedSetContainer", this->testAvgGraphCreation<MapUnorderedSetContainer>(path));

            printAvgTestResult("UnorderedMapVectorContainer", this->testAvgGraphCreation<UnorderedMapVectorContainer>(path));

            printAvgTestResult("UnorderedMapSetContainer", this->testAvgGraphCreation<UnorderedMapSetContainer>(path));

            printAvgTestResult("UnorderedMapUnorderedSetContainer", this->testAvgGraphCreation<UnorderedMapUnorderedSetContainer>(path));

    }

void Tester::testGraphsInFolder(std::string dir) {
        for (const auto& dirEntry : std::filesystem::directory_iterator(dir)) {
                std::cout << "Test on " << dirEntry.path() << '\n';
                this->testAllImplementationsSequential(dirEntry.path().string());
                std::cout << std::endl;
        }
}

void Tester::writeGraphCreationAllImplementationsSequential(const std::string &dir, Writer &writer)
{
    for (const auto& dirEntry : std::filesystem::directory_iterator(dir))
    {
        writer.write(dirEntry.path().filename().string());
            writer.write(AlgorithmTest( "VectorVectorContainer","Sequential",dirEntry.path().filename(),numberOfTrials,
                                        this->testMultipleGraphCreation<VectorVectorContainer>(dirEntry.path().string()),
                                                std::vector<double>{}));
            writer.write(AlgorithmTest( "VectorSetContainer","Sequential",dirEntry.path().filename(),numberOfTrials,
                                        this->testMultipleGraphCreation<VectorSetContainer>(dirEntry.path().string()),
                                        std::vector<double>{}));
            writer.write(AlgorithmTest( "VectorUnorderedSetContainer","Sequential",dirEntry.path().filename(),numberOfTrials,
                                        this->testMultipleGraphCreation<VectorUnorderedSetContainer>(dirEntry.path().string()),
                                        std::vector<double>{}));
            writer.write(AlgorithmTest( "MapVectorContainer","Sequential",dirEntry.path().filename(),numberOfTrials,
                                        this->testMultipleGraphCreation<MapVectorContainer>(dirEntry.path().string()),
                                        std::vector<double>{}));
            writer.write(AlgorithmTest( "MapSetContainer","Sequential",dirEntry.path().filename(),numberOfTrials,
                                        this->testMultipleGraphCreation<MapSetContainer>(dirEntry.path().string()),
                                        std::vector<double>{}));
            writer.write(AlgorithmTest( "MapUnorderedSetContainer","Sequential",dirEntry.path().filename(),numberOfTrials,
                                        this->testMultipleGraphCreation<MapUnorderedSetContainer>(dirEntry.path().string()),
                                        std::vector<double>{}));
            writer.write(AlgorithmTest( "UnorderedMapVectorContainer","Sequential",dirEntry.path().filename(),numberOfTrials,
                                        this->testMultipleGraphCreation<UnorderedMapVectorContainer>(dirEntry.path().string()),
                                        std::vector<double>{}));
            writer.write(AlgorithmTest( "UnorderedMapSetContainer","Sequential",dirEntry.path().filename(),numberOfTrials,
                                        this->testMultipleGraphCreation<UnorderedMapSetContainer>(dirEntry.path().string()),
                                        std::vector<double>{}));
            writer.write(AlgorithmTest( "UnorderedMapUnorderedSetContainer","Sequential",dirEntry.path().filename(),numberOfTrials,
                                        this->testMultipleGraphCreation<UnorderedMapUnorderedSetContainer>(dirEntry.path().string()),
                                        std::vector<double>{}));
        }
    writer.finalize();
}




AlgorithmTest::AlgorithmTest(std::string name, std::string type, std::string graphName, int numberOfTrials, std::vector<double> timeResults,
                             std::vector<double> memoryResults) : name(std::move(name)), type(std::move(type)),
                                                                  numberOfTrials(numberOfTrials),
                                                                  timeResults(std::move(timeResults)),
                                                                  memoryResults(std::move(memoryResults)),
                                                                  graphName(std::move(graphName)){}


TestResult::TestResult(std::string type):type(std::move(type)) {}

