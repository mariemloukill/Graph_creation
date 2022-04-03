#include <iostream>
#include "Graph.h"
using namespace std;
void Graph::add_edge_unweighted(int a, int b)

{
    adj_out[a].push_back(b);

}



void Graph::print_graph() {
    for (const auto &x : adj_out) {
        cout << x.first << ": [";
        for (auto it = x.second.begin(); it != x.second.end(); ++it)
            cout << ' ' << *it;
        cout << "]" << "\n";
    }
}