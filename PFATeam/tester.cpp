#include "tester.h"
#include <iostream>
#include <filesystem>
#include "boost/mp11/mpl.hpp"

using namespace PFA;
using TestTypes=boost::mp11::mp_list<VectorVectorContainer<ProfilableAllocator>,
        VectorSetContainer<ProfilableAllocator>,
        VectorUnorderedSetContainer<ProfilableAllocator>,
        MapVectorContainer<ProfilableAllocator>,
        MapSetContainer<ProfilableAllocator>,
        MapUnorderedSetContainer<ProfilableAllocator>,
        UnorderedMapVectorContainer<ProfilableAllocator>,
        UnorderedMapSetContainer<ProfilableAllocator>,
        UnorderedMapUnorderedSetContainer<ProfilableAllocator>>;
template<typename T>
std::string testTypeName;
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
Tester::Tester(int numberOfTrials):numberOfTrials(numberOfTrials)  {}

void Tester::printAvgTestResult(std::string type, double avg){
        std::cout << std::left << std::setfill('.') << std::setw(40) << type << std::right << std::setfill('.') << std::setw(40) << avg << " ms" << std::endl;
}

void Tester::testAllImplementationsSequential(std::string path){
        boost::mp11::mp_for_each<TestTypes>([&](auto type)
        {
            using Container = decltype(type);
            printAvgTestResult(testTypeName<Container>, this->testAvgGraphCreation<Container>(path));
        });
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
        if(skip>numberOfImplementations)
        {
            skip-=numberOfImplementations;
            continue;
        }
        else
            writer.write(dirEntry.path().filename().string());
        boost::mp11::mp_for_each<TestTypes>([&](auto type)
        {
            if(skip)
            {
                skip--;
                return;
            }
            using Container = decltype(type);
            writer.write( AlgorithmTest(testTypeName<Container>, "Sequential", dirEntry.path().filename(), numberOfTrials,
                                        this->testMultipleGraphCreation<Container>(dirEntry.path().string())));
            GlobalAllocator::resetMax();
        });
    }
    writer.finalize();
}


void Tester::writeGraphCreationAllImplementationsParallel(const std::string &dir, Writer &writer,int skip)
{
    constexpr int numberOfImplementations = 9;
    if(skip==0)
        writer.initialize();
    else skip--;
    for (const auto& dirEntry : std::filesystem::directory_iterator(dir))
    {
        std::string fileRegex = dirEntry.path().string();
        auto sep_index=fileRegex.find_last_of('#');
        if(fileRegex.substr(sep_index+1)!="01")
            continue;
        if(skip>numberOfImplementations)
        {
            skip-=numberOfImplementations;
            continue;
        }

        std::string fileName=fileRegex.substr(0,sep_index);
        writer.write(fileName);
        fileRegex=fileName+"#[0-9]*";
        boost::mp11::mp_for_each<TestTypes>(
                [&](auto F)
                {
                    using Container=decltype(F);
                    if(skip==0) {
                        RandomizedSplitMerger<Container, ProfilableAllocator> randomizedSplitMerger;
                        writer.write(
                                AlgorithmTest(testTypeName<Container>, "Parallel", dirEntry.path().filename(), numberOfTrials,
                                              this->testMultipleGraphCreationParallel<Container>(
                                                      fileRegex,
                                                      parallelSplitCreator<Container,ProfilableAllocator>,
                                                      randomizedSplitMerger)));
                        GlobalAllocator::resetMax();
                    }
                    else
                        skip--;
                });
    }
    writer.finalize();
}

void Tester::writeGraphCreationAllImplementationsParallelInplace(const std::string &dir, Writer &writer,int count, int skip) {

    constexpr int numberOfImplementations = 9;
    if(skip==0)
        writer.initialize();
    else skip--;
    for (const auto& dirEntry : std::filesystem::directory_iterator(dir))
    {
        if(skip>numberOfImplementations)
        {
            skip-=numberOfImplementations;
            continue;
        }
        else
            writer.write(dirEntry.path().filename().string());
        boost::mp11::mp_for_each<TestTypes>([&](auto type)
                    {
                        if(skip)
                        {
                            skip--;
                            return;
                        }
                        using Container = decltype(type);
                        RandomizedSplitMerger<Container, ProfilableAllocator> randomizedSplitMerger;
                        writer.write( AlgorithmTest(testTypeName<Container>, "ParallelInplace", dirEntry.path().filename(), numberOfTrials,
                                                    this->testMultipleGraphCreationParallelInplace<Container>(dirEntry.path().string(),count,
                                                                                                                parallelSplitCreator<Container,ProfilableAllocator>,
                                                                                                                randomizedSplitMerger)));
                        GlobalAllocator::resetMax();
                    });
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

