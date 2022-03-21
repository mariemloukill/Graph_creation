#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <numeric>
#include "metrics.h"


int sum (std::vector<int> count, int element_index)
{
    int s=0;
    if (element_index ==0) return count.at(0);
    else
    {
        for (int i=0; i<=element_index; i++)
            s+=count.at(i);
        return s;
    }
}
int main(int argc, char *argv[]) {

    std::ifstream infile(argv[2]);
    std::vector <int> src; //vector containing the source of the edge
    std::vector <int> count; // vector containing the number of consecutive edge for a given node
    std::vector <int> dst;   // vector containing the destination edges
    //std::vector <int> index; // vector containing the index at which the destination edges start for a node

    dst.reserve(atoi(argv[1])); // reserving a length (number of edges) for the destination vector
    std::string str;
    int a, b;
    auto start = std::chrono::system_clock::now();
    //UNCOMMENT THE NEXT SECTION (IF STATEMENT) IF YOU WANT TO CREATE THE GRAPH WITH REDUNDANCY
    if (infile.is_open()) {


        while (infile >> a >> b) {
            if ( (src.size()==0)|| (src.back()!=a))
            {
                src.push_back(a);
                count.push_back(1);
            }
            else
            {
                count.back()++;
            }

            dst.push_back(b);

        }
    }

    /*if (infile.is_open()) {

        while (infile >> a >> b) {

            if ( (src.size()==0))
            {
                src.push_back(a);
                count.push_back(1);
                dst.push_back(b);
            }
            else {
                if ((src.back() == a)) {
                    count.back()++;
                    dst.push_back(b);
                }
                else {
                    std::vector<int>::iterator it = std::find(src.begin(), src.end(), a);
                    if (it != src.end()) {
                        int element_index = std::distance(src.begin(), it);
                        dst.insert(dst.begin() + sum(count, element_index), b);
                        count.at(element_index)++;


                    } else {
                        src.push_back(a);
                        count.push_back(1);
                        dst.push_back(b);

                    }
                }
            }


            /*std::cout << "src:"<< std::endl;
            for(int i=0; i < src.size(); i++)
                std::cout << src.at(i) << ' ';
            std::cout <<std::endl<< "count:"<< std::endl;
            for(int i=0; i < count.size(); i++)
                std::cout << count.at(i) << ' ';
            std::cout <<std::endl<< "dst:"<< std::endl;
            for(int i=0; i < dst.size(); i++)
                std::cout << dst.at(i) << ' ';
            std::cout<<std::endl<<"--------------"<<std::endl;

        }

    }*/

    auto end = std::chrono::system_clock::now();

    double creation= std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()/1000.0;
    std::cout <<"creation time ="<<creation<<std::endl;
    add_result_to_file (creation, "creation_time_edge.txt");

    calculate_peak_RAM ("creation_ram_edge.txt" );



    return 0;
}