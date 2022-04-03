#include <vector>
#include <iostream>
#include <glob.h>
#include <algorithm>
#include "Split_Sequential_Graph.h"

using namespace std;
struct graph_data {
    int thread_id;
    string message;
    Split_Sequential_Graph *g;
    vector<int> keys; // the list of keys (nodes in each graph)

    vector<int> in_keys; // the list of keys (nodes in each graph)

};
// there is a problem of reference/value/ pointers
/*void re_organize_graphs(graph_data Graphs[], int files_size){
    if (files_size>1){
        // reorganize adj_out
        for (int l = 0; l < files_size-1; l++)
        { cout << "l= "<< l <<endl;
            int m = l+1;
            int it = 0;
            for(auto it:Graphs[l].keys)
            {m=l+1;
                if (std::binary_search(Graphs[m].keys.begin(), Graphs[m].keys.end(), it)) {
                    Graphs[l].g->adj_out[it].insert( Graphs[l].g->adj_out[it].end(), Graphs[m].g->adj_out[it].begin(), Graphs[m].g->adj_out[it].end());
                    cout <<"test1"<<it <<endl;
                    Graphs[m].g->adj_out.erase(it);
                }
                //std::cout <<"test;";
                m++;
            }}
    }}
        // reorganize adj_in
        /*for (int l = 0; l < files_size-1; l++)
        {int m = l+1;
            int it = 0;
            for(auto it:Graphs[l].in_keys)
            {m=l+1;
                if (std::binary_search(Graphs[m].in_keys.begin(), Graphs[m].in_keys.end(), it)) {
                    Graphs[l].g.adj_in[it].insert( Graphs[l].g.adj_in[it].end(), Graphs[m].g.adj_in[it].begin(), Graphs[m].g.adj_in[it].end());
                    Graphs[m].g.adj_in.erase(it);
                }
                m++;
            }}*/


vector<string> globVector(const string &pattern) {
    glob_t glob_result;
    glob(pattern.c_str(), GLOB_TILDE, NULL, &glob_result);
    vector<string> files;
    for (unsigned int i = 0; i < glob_result.gl_pathc; ++i) {
        files.push_back(string(glob_result.gl_pathv[i]));
    }
    globfree(&glob_result);
    return files;
}

