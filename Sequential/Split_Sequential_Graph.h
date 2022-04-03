//
// Created by Mariem Loukil on 3/20/22.
//

#ifndef SEQUENTIAL_SPLIT_SEQUENTIAL_GRAPH_H
#define SEQUENTIAL_SPLIT_SEQUENTIAL_GRAPH_H


#include <vector>
#include <map>
using std::vector;
using namespace std;

class Split_Sequential_Graph {
public:
    map<int, vector<int> > adj_out; // map for out-going edges
    //map<int, vector<int> > adj_in;  // map for in-going edges

public: string graph_file;
//---------------------------------------//
public: void  add_edge_unweighted(int a, int b) ; //method for adding one line of the file
public: void create_graph(std::string graph_file) ; // method for creating the graph
public: void print_graph(); // method for printing the graph
public: vector<int> get_keys( ); // method for getting the list of nodes of a graph as well as the first node and the last node
//public: vector<int> get_in_keys( );
};


#endif //SEQUENTIAL_SPLIT_SEQUENTIAL_GRAPH_H
