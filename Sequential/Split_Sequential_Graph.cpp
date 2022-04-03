#include <iostream>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <fstream>
#include "Split_Sequential_Graph.h"
#include "metrics.h"

using std::vector;
using namespace std;

void Split_Sequential_Graph::add_edge_unweighted(int a, int b) {
    adj_out[a].push_back(b);
    //adj_in[b].push_back(a);
}


void Split_Sequential_Graph::create_graph(string graph_file) {
    ifstream infile(graph_file);
    string str;
    int a, b;
    if (infile.is_open()) {


        while (infile >> a >> b) {
            this->add_edge_unweighted(a, b);
        }
        infile.close();
    }
}
vector<int> Split_Sequential_Graph::get_keys( ){
    vector <int> keys;
    for (const auto &x : this->adj_out)
        keys.push_back(x.first);
    return keys;

}
/*vector <int>  Split_Sequential_Graph::get_in_keys( ){
    vector <int> in_keys;
    //for (const auto &x : this->adj_in)
     //   in_keys.push_back(x.first);
    return in_keys;
}*/
void Split_Sequential_Graph::print_graph() {
    for (const auto &x: adj_out) {
        std::cout << x.first << ": [";
        for (auto it = x.second.begin(); it != x.second.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << "]" << "\n";
    }
}