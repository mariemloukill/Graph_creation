#include "tester.h"
#include <iostream>
#include <filesystem>

using namespace PFA;
Tester::Tester(int numberOfTrials):numberOfTrials(numberOfTrials)  {}

void Tester::printAvgTestResult(std::string type, double avg){
        std::cout << std::left << std::setfill('.') << std::setw(40) << type << std::right << std::setfill('.') << std::setw(40) << avg << " ms" << std::endl;
}

void Tester::testAllImplementationsSequential(std::string path){

            printAvgTestResult("VectorVectorContainer", this->testAvgGraphCreation<VectorVectorContainer<ProfilableAllocator>>(path));

            printAvgTestResult("VectorSetContainer", this->testAvgGraphCreation<VectorSetContainer<ProfilableAllocator>>(path));

            printAvgTestResult("VectorUnorderedSetContainer", this->testAvgGraphCreation<VectorUnorderedSetContainer<ProfilableAllocator>>(path));

            printAvgTestResult("MapVectorContainer", this->testAvgGraphCreation<MapVectorContainer<ProfilableAllocator>>(path));

            printAvgTestResult("MapSetContainer", this->testAvgGraphCreation<MapSetContainer<ProfilableAllocator>>(path));

            printAvgTestResult("MapUnorderedSetContainer", this->testAvgGraphCreation<MapUnorderedSetContainer<ProfilableAllocator>>(path));

            printAvgTestResult("UnorderedMapVectorContainer", this->testAvgGraphCreation<UnorderedMapVectorContainer<ProfilableAllocator>>(path));

            printAvgTestResult("UnorderedMapSetContainer", this->testAvgGraphCreation<UnorderedMapSetContainer<ProfilableAllocator>>(path));

            printAvgTestResult("UnorderedMapUnorderedSetContainer", this->testAvgGraphCreation<UnorderedMapUnorderedSetContainer<ProfilableAllocator>>(path));

    }

void Tester::testGraphsInFolder(std::string dir) {
        for (const auto& dirEntry : std::filesystem::directory_iterator(dir)) {
                std::cout << "Test on " << dirEntry.path() << '\n';
                this->testAllImplementationsSequential(dirEntry.path().string());
                std::cout << std::endl;
        }
}

void Tester::writeGraphCreationAllImplementationsSequential(const std::string &dir, Writer &writer,int skip)
{
    constexpr int numberOfImplementations = 9;
    if(skip==0)
        writer.initialize();
    else skip--;
    for (const auto& dirEntry : std::filesystem::directory_iterator(dir))
    {
        if(skip < numberOfImplementations)
            writer.write(dirEntry.path().filename().string());
        if(skip==0) {
            writer.write(
                    AlgorithmTest("VectorVectorContainer", "Sequential", dirEntry.path().filename(), numberOfTrials,
                                  this->testMultipleGraphCreation<VectorVectorContainer<ProfilableAllocator>>(
                                          dirEntry.path().string())));
            GlobalAllocator::resetMax();
        }
        else
            skip--;

        if(skip==0) {
            writer.write(AlgorithmTest("VectorSetContainer", "Sequential", dirEntry.path().filename(), numberOfTrials,
                                       this->testMultipleGraphCreation<VectorSetContainer<ProfilableAllocator>>(
                                               dirEntry.path().string())));
            GlobalAllocator::resetMax();
        }
        else skip--;

        if(skip==0) {
            writer.write(AlgorithmTest("VectorUnorderedSetContainer", "Sequential", dirEntry.path().filename(),
                                       numberOfTrials,
                                       this->testMultipleGraphCreation<VectorUnorderedSetContainer<ProfilableAllocator>>(
                                               dirEntry.path().string())));
            GlobalAllocator::resetMax();
        }
        else skip--;

        if(skip==0) {
            writer.write(AlgorithmTest("MapVectorContainer", "Sequential", dirEntry.path().filename(), numberOfTrials,
                                       this->testMultipleGraphCreation<MapVectorContainer<ProfilableAllocator>>(
                                               dirEntry.path().string())));
            GlobalAllocator::resetMax();
        }
        else skip--;

        if(skip==0){
            writer.write(AlgorithmTest("MapSetContainer", "Sequential", dirEntry.path().filename(), numberOfTrials,
                                       this->testMultipleGraphCreation<MapSetContainer<ProfilableAllocator>>(
                                               dirEntry.path().string())));
            GlobalAllocator::resetMax();
        }
        else skip--;

        if(skip==0) {
            writer.write(
                    AlgorithmTest("MapUnorderedSetContainer", "Sequential", dirEntry.path().filename(), numberOfTrials,
                                  this->testMultipleGraphCreation<MapUnorderedSetContainer<ProfilableAllocator>>(
                                          dirEntry.path().string())));
            GlobalAllocator::resetMax();
        }
        else skip--;
        if(skip==0) {
            writer.write(AlgorithmTest("UnorderedMapVectorContainer", "Sequential", dirEntry.path().filename(),
                                       numberOfTrials,
                                       this->testMultipleGraphCreation<UnorderedMapVectorContainer<ProfilableAllocator>>(
                                               dirEntry.path().string())));
            GlobalAllocator::resetMax();
        }
        else skip--;
        if(skip==0) {
            writer.write(
                    AlgorithmTest("UnorderedMapSetContainer", "Sequential", dirEntry.path().filename(), numberOfTrials,
                                  this->testMultipleGraphCreation<UnorderedMapSetContainer<ProfilableAllocator>>(
                                          dirEntry.path().string())));
            GlobalAllocator::resetMax();
        }
        else skip--;
        if(skip==0) {
            writer.write(AlgorithmTest("UnorderedMapUnorderedSetContainer", "Sequential", dirEntry.path().filename(),
                                       numberOfTrials,
                                       this->testMultipleGraphCreation<UnorderedMapUnorderedSetContainer<ProfilableAllocator>>(
                                               dirEntry.path().string())));
            GlobalAllocator::resetMax();
        }
        else skip--;
    }
    writer.finalize();
}




AlgorithmTest::AlgorithmTest(std::string name, std::string type, std::string graphName, int numberOfTrials, std::vector<double> timeResults,
                             std::vector<double> memoryResults) : name(std::move(name)), type(std::move(type)),
                                                                  numberOfTrials(numberOfTrials),
                                                                  timeResults(std::move(timeResults)),
                                                                  memoryResults(std::move(memoryResults)),
                                                                  graphName(std::move(graphName)){}

AlgorithmTest::AlgorithmTest(std::string name, std::string type, std::string graphName, int numberOfTrials,
                             const std::vector<std::pair<double,double>>& timeMemoryResults): name(std::move(name)), type(std::move(type)),
                                                                                     numberOfTrials(numberOfTrials),
                                                                                     graphName(std::move(graphName)){
for(auto&& [time,memory] : timeMemoryResults){
    this->timeResults.push_back(time);
    this->memoryResults.push_back(memory);
}
}


TestResult::TestResult(std::string type):type(std::move(type)) {}

