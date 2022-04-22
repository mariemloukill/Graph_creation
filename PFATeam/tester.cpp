#include "tester.h"
#include <iostream>
#include <filesystem>
#include "boost/mp11/mpl.hpp"


using namespace PFA;
Tester::Tester(int numberOfTrials):numberOfTrials(numberOfTrials)  {}

void Tester::printAvgTestResult(std::string type, double avg){
        std::cout << std::left << std::setfill('.') << std::setw(40) << type << std::right << std::setfill('.') << std::setw(40) << avg << " ms" << std::endl;
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


AlgorithmTestError::AlgorithmTestError(std::string name, std::string type, std::string graphName,std::exception &error) :
        name(std::move(name)), type(std::move(type)), graphName(std::move(graphName)), error(error){}

TestResult::TestResult(std::string type):type(std::move(type)) {}

namespace PFA
{
    template<>
    std::string testTypeName<VectorVectorContainer<ProfilableAllocator>> = "VectorVectorContainer";
    template<>
    std::string testTypeName<VectorSetContainer<ProfilableAllocator>> = "VectorSetContainer";
    template<>
    std::string testTypeName<VectorUnorderedSetContainer<ProfilableAllocator>> = "VectorUnorderedSetContainer";
    template<>
    std::string testTypeName<MapVectorContainer<ProfilableAllocator>> = "MapVectorContainer";
    template<>
    std::string testTypeName<MapSetContainer<ProfilableAllocator>> = "MapSetContainer";
    template<>
    std::string testTypeName<MapUnorderedSetContainer<ProfilableAllocator>> = "MapUnorderedSetContainer";
    template<>
    std::string testTypeName<UnorderedMapVectorContainer<ProfilableAllocator>> = "UnorderedMapVectorContainer";
    template<>
    std::string testTypeName<UnorderedMapSetContainer<ProfilableAllocator>> = "UnorderedMapSetContainer";
    template<>
    std::string testTypeName<UnorderedMapUnorderedSetContainer<ProfilableAllocator>> = "UnorderedMapUnorderedSetContainer";

}
