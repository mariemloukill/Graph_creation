//
// Created by Mariem Loukil on 3/20/22.
//

#ifndef SEQUENTIAL_SEQUENTIAL_GRAPH_H
#define SEQUENTIAL_SEQUENTIAL_GRAPH_H


#include <iostream>
#include <vector>
#include <chrono>
#include <map>

using namespace std;
class Sequential_Graph{
public:             // Access specifier
    map<int, vector<int> > adj_out;

    //map< int,set<double> > weight;

public: void  add_edge_unweighted(int a, int b) ;

public:   void print_graph();

public:
    void create_graph(std::string graph_file) ;
};


#endif //SEQUENTIAL_SEQUENTIAL_GRAPH_H
