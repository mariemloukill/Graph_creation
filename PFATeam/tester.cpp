#include "tester.h"
#include <iostream>
#include <filesystem>


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