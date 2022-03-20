//
// Created by Mariem Loukil on 3/20/22.
//

#ifndef PARALLEL_GRAPH_H
#define PARALLEL_GRAPH_H


#include "vector"
#include "map"
using namespace std;
class Graph {
    int count = 0;// The class
public:             // Access specifier
    map<int, vector<int> > adj_out;
    //map<int, vector<int> > adj_in;


public:
    void add_edge_unweighted(int a, int b) ;
public:
    void print_graph() ;


};


#endif //PARALLEL_GRAPH_H
