#ifndef __TESTER_HEADER__
#define __TESTER_HEADER__

#include "graph/graph.h"
#include "graph/graph_container.h"
#include "writer/writer.h"
#include <iomanip>
#include <chrono>
#include <iostream>
#include "graph/splitcreator.h"
#include "graph/splitmerger.h"
#include "boost/mp11/mpl.hpp"


namespace PFA
{
    template<typename T>
    extern std::string testTypeName;


    struct AlgorithmTest
    {
        /**
         * @brief The name of the algorithm
         */
        std::string name;
        /**
         * @brief Type of test: sequential or parallel
         */
        std::string type;
        /**
         * @brief The name of the graph
         */
        std::string graphName;
        /**
         * @brief Number of trials for this test
         */
        int numberOfTrials;
        /**
         * @brief Execution time of each trial, in milliseconds
         */
        std::vector<double> timeResults;
        std::vector<double> memoryResults;
        AlgorithmTest(std::string name, std::string type, std::string graphName, int numberOfTrials,
                      std::vector<double> timeResults, std::vector<double> memoryResults);
        AlgorithmTest(std::string name, std::string type, std::string graphName, int numberOfTrials,
                      const std::vector<std::pair<double,double>>& timeMemoryResults);
    };

    class TestResult : public std::vector<AlgorithmTest>
    {
    private:
        std::string type;
    public:
        std::string getType() { return type; }
        explicit TestResult(std::string type);
    };

    class Tester {

    private:
        int numberOfTrials;
    public:
        Tester(int numberOfTrials=10);

        /**
         * @brief Test the creation of a graph and return the time it took.
         *
         * @tparam Container Container type
         * @param path path to the graph file
         * @return double time in milliseconds
         */
        template<typename Container>
        double testGraphCreationParallel(std::string path,SplitCreator<Container,ProfilableAllocator>& splitCreator,
                                         SplitMerger<Container,ProfilableAllocator>& splitMerger)
        {
            std::ios_base::sync_with_stdio(false);
            auto start = std::chrono::system_clock::now();
            auto graphs=splitCreator.createSplitsFromFileRegex(path);
            splitMerger.merge(graphs);
            auto end=std::chrono::system_clock::now();
            return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()/1000.0;
        }

        /**
 * @brief Test the creation of a graph and return the time it took.
 *
 * @tparam Container Container type
 * @param path path to the graph file
 * @return double time in milliseconds
 */
        template<typename Container>
        double testGraphCreationParallelInplace(std::string path,int count,SplitCreator<Container,ProfilableAllocator>& splitCreator,
                                         SplitMerger<Container,ProfilableAllocator>& splitMerger)
        {
            std::ios_base::sync_with_stdio(false);
            auto start = std::chrono::system_clock::now();
            auto graphs=splitCreator.createSplitsFromFile(path,count);
            splitMerger.merge(graphs);
            auto end=std::chrono::system_clock::now();
            return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()/1000.0;
        }

        /**
 * @brief Test the creation of a graph and return the time it took.
 *
 * @tparam Container Container type
 * @param path path to the graph file
 * @return double time in milliseconds
 */
        template<typename Container>
        double testGraphCreation(std::string path) {
            std::ios_base::sync_with_stdio(false);
            Graph<Container> G;
            auto start = std::chrono::system_clock::now();
            G=Graph<Container>::createGraphFromFile(path);
            auto end=std::chrono::system_clock::now();
            return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()/1000.0;
        }



        /**
         * @brief Test the creation of a graph  multiple times and return the average result
         *
         * @tparam Container Container type
         * @param path path to the graph file
         * @return double average time in milliseconds
         */
        template<typename Container>
        double testAvgGraphCreation(std::string path) {
            int avg = 0 ;
            for (int i=0 ; i<numberOfTrials ; i++) {
                avg += testGraphCreation<Container>(path);
            }
            return avg/numberOfTrials;
        }



        /**
         * @brief Test the creation of the graph multiple times and return the results in a vector
         *
         * @tparam Container Container type
         * @param path path to the graph file
         * @return std::vector<double> the results of the test
         */
        template<typename Container>
        std::vector<std::pair<double,double>> testMultipleGraphCreation(std::string path) {
            std::vector<std::pair<double,double>> avg;
            for (int i=0 ; i<numberOfTrials ; i++) {
                double time=testGraphCreation<Container>(path);
                avg.emplace_back(time,GlobalAllocator::max_memory);
            }
            return avg;
        }

        template<typename Container>
        std::vector<std::pair<double,double>> testMultipleGraphCreationParallel(std::string path,SplitCreator<Container,ProfilableAllocator>& splitCreator,
                                                                                SplitMerger<Container,ProfilableAllocator>& splitMerger) {
            std::vector<std::pair<double,double>> avg;
            for (int i=0 ; i<numberOfTrials ; i++) {
                double time=testGraphCreationParallel<Container>(path,splitCreator,splitMerger);
                avg.emplace_back(time,GlobalAllocator::max_memory);
            }
            return avg;
        }

        template<typename Container>
        std::vector<std::pair<double,double>> testMultipleGraphCreationParallelInplace(std::string path,int count,SplitCreator<Container,ProfilableAllocator>& splitCreator,
                                                                                SplitMerger<Container,ProfilableAllocator>& splitMerger) {
            std::vector<std::pair<double,double>> avg;
            for (int i=0 ; i<numberOfTrials ; i++) {
                double time=testGraphCreationParallelInplace<Container>(path,count,splitCreator,splitMerger);
                avg.emplace_back(time,GlobalAllocator::max_memory);
            }
            return avg;
        }


        template<typename TestTypes>
        void writeGraphCreationAllImplementationsSequential(const std::string &dir, Writer &writer,int skip=0)
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


        template<typename TestTypes>
        void writeGraphCreationAllImplementationsParallel(const std::string &dir, Writer &writer,int skip=0)
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

        template<typename TestTypes>
        void writeGraphCreationAllImplementationsParallelInplace(const std::string &dir, Writer &writer,int count, int skip=0) {

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



        /**
         * @brief Print out the results of the test
         *
         * @param type The Container Type ( Vector of vectors, Map of vectors, etc)
         * @param avg The average test result
         */
        void printAvgTestResult(std::string type, double avg);

        /**
         * @brief Test container on all available implementations and print out the results
         *
         * @param path path to the graph file
         */
        template<typename TestTypes>
        void testAllImplementationsSequential(std::string path){
            boost::mp11::mp_for_each<TestTypes>([&](auto type)
                                                {
                                                    using Container = decltype(type);
                                                    printAvgTestResult(testTypeName<Container>, this->testAvgGraphCreation<Container>(path));
                                                });
        }
        /**
         * @brief Test all graphs in the provided directory
         * @param dir directory containing the graphs
         */
        void testGraphsInFolder(std::string dir);
    };
}

#endif