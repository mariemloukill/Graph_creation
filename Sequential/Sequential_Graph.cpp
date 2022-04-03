#include <iostream>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <fstream>
#include "Sequential_Graph.h"
#include "metrics.h"

using std::vector;
using namespace std;

void Sequential_Graph::add_edge_unweighted(int a, int b) {
    adj_out[a].push_back(b);
}


void Sequential_Graph::create_graph(string graph_file) {
    ifstream infile(graph_file);
    string str;
    int a, b;
    if (infile.is_open()) {


        while (infile >> a >> b) {

            this->add_edge_unweighted(a, b);

        }

    }

    infile.close();

}

void Sequential_Graph::print_graph() {
    for (const auto &x: adj_out) {
        std::cout << x.first << ": [";
        for (auto it = x.second.begin(); it != x.second.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << "]" << "\n";
    }
}

