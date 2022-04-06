#ifndef __TESTER_HEADER__
#define __TESTER_HEADER__

#include "graph/graph.h"
#include "graph/graph_container.h"
#include "writer/writer.h"
#include <iomanip>
#include <chrono>
#include <iostream>

namespace PFA
{
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


        /**
         * @brief Test the time & memory taken to create a graph using all implementations and return the results
         * @param dir directory containing the graph files
         * */
        void writeGraphCreationAllImplementationsSequential(const std::string& dir, Writer &writer,int skip=0);



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
        void testAllImplementationsSequential(std::string path);

        /**
         * @brief Test all graphs in the provided directory
         * @param dir directory containing the graphs
         */
        void testGraphsInFolder(std::string dir);
    };
}

#endif