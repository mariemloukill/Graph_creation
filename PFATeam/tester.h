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

        template<typename Container>
        double testGraphCreation(std::string path) {
            std::ios_base::sync_with_stdio(false);
            Graph<Container> G;
            auto start = std::chrono::system_clock::now();
            G=Graph<Container>::createGraphFromFile(path);
            auto end=std::chrono::system_clock::now();
            return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()/1000.0;
        }

        template<typename Container>
        double testAvgGraphCreation(std::string path) {
            int avg = 0 ;
            for (int i=0 ; i<numberOfTrials ; i++) {
                avg += testGraphCreation<Container>(path);
            }
            return avg/numberOfTrials;
        }
        
        template<typename Container>
        std::vector<double> testMultipleGraphCreation(std::string path) {
            std::vector<double> avg;
            for (int i=0 ; i<numberOfTrials ; i++) {
                avg.push_back(testGraphCreation<Container>(path));
            }
            return avg;
        }

        void printAvgTestResult(std::string type, double avg);

        void testAllImplementationsSequential(std::string path);
        
        void testGraphsInFolder(std::string dir);
};


#endif