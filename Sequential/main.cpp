#include <iostream>
#include "Sequential_Graph.h"
#include "Split_Sequential_Graph.h"
#include "methods.h"
#include "metrics.h"
#include <glob.h>
#include <map>
#include <pthread.h>
#include <algorithm>

using namespace std;
struct graph_data {
    Split_Sequential_Graph  g;
    vector<int> keys; // the list of keys (nodes in each graph)
};

int main(int argc, char *argv[]) {
    // getting the list of files in the split folder (the list of split files)


    // if argv[1] is 1 run sequential graph
    // if argv[1] is 2 run split sequential
    if (atoi(argv[1])==1){

        Sequential_Graph seq_graph;
        auto start = std::chrono::system_clock::now();
        seq_graph.create_graph(argv[2]);
        auto end = std::chrono::system_clock::now();
        double creation= std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()/1000.0;
        add_result_to_file (creation, "creation_time_sequential.txt");
        calculate_peak_RAM ("creation_ram_sequential.txt" );
        // creating sequential graph, argv[2] is the file path
    }


    else {if (atoi(argv[1])==2) {
            // getting the list of files in the split folder (the list of split files)
            vector<string> files = globVector("/home/user/Code/Graph creation cpp/sequential/splitfiles/*");
            // creating an array of graphs
            struct graph_data Graphs_data[files.size()];
            //start time
            auto start = std::chrono::system_clock::now();


            for (int i = 0; i < files.size(); i++) { //loop of creating each graph and updating the keys
                Graphs_data[i].g.create_graph(files[i]);
                //loop of creating each graph and updating the keys
                Graphs_data[i].keys=Graphs_data[i].g.get_keys();
                Graphs_data[i].g.print_graph();
                cout <<"------------"<<endl;
            }


            //Graphs_data[i].g.get_in_keys();

            auto end = std::chrono::system_clock::now();
            double creation= std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()/1000.0;
            cout << "creation time:"<< creation <<endl;
            add_result_to_file (creation, "creation_time_split_seq.txt");

            auto start1 = std::chrono::system_clock::now();
            // reorganizing graphs to remove redundancy (implementation in method.cpp)
            if (files.size()>1){
                // reorganize adj_out
                for (int l = 0; l < files.size()-1; l++)
                { //cout << "l= "<< l <<endl;
                    int m = l+1;

                    for(auto it:Graphs_data[l].keys)
                    { while (m<files.size()-1){
                            if (std::binary_search(Graphs_data[m].keys.begin(), Graphs_data[m].keys.end(), it)) {
                                Graphs_data[l].g.adj_out[it].insert( Graphs_data[l].g.adj_out[it].end(), Graphs_data[m].g.adj_out[it].begin(), Graphs_data[m].g.adj_out[it].end());

                                Graphs_data[m].g.adj_out.erase(it);

                            }
                            //std::cout <<"test;";
                            m++;}
                    }}
            }
            //cout << "finished reorganizing";
            //updating the keys after the step of reorganizing
            for (int i = 0; i < files.size(); i++)
            {Graphs_data[i].keys=Graphs_data[i].g.get_keys();
                Graphs_data[i].g.print_graph();
                cout <<"-------------"<<endl;
            }
            auto end1 = std::chrono::system_clock::now();
            double reorganization= std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count()/1000.0;
            add_result_to_file (reorganization, "reorganization_time_split_seq.txt");
            // creating a map that informs the graph in which we can find each node
            auto start2 = std::chrono::system_clock::now();
            map <int,int> keys_dictionary;
            for (int t=0; t<files.size();t++){
                for (auto const &x : Graphs_data[t].keys) {
                    keys_dictionary[x]=t;
                }}
            auto end2 = std::chrono::system_clock::now();
            double dictionary= std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count()/1000.0;
            add_result_to_file (dictionary, "dictionary_time_split_seq.txt");
            // reporting the time and the ram usage
            calculate_peak_RAM ("creation_ram_split_seq.txt" );
        }}




    return 0;


}

