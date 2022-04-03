#ifndef __TESTER_HEADER__
#define __TESTER_HEADER__

#include "graph.h"
#include "graph_container.h"
#include <iomanip>
#include <chrono>
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
        std::vector<double> testMultipleGraphCreation(std::string path) {
            std::vector<double> avg;
            for (int i=0 ; i<numberOfTrials ; i++) {
                avg.push_back(testGraphCreation<Container>(path));
            }
            return avg;
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
        void testAllImplementationsSequential(std::string path);
        
        /**
         * @brief Test all graphs in the provided directory
         * @param dir directory containing the graphs
         */
        void testGraphsInFolder(std::string dir);
};


#endif