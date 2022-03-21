#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <map>
#include <glob.h>
#include <chrono>
#include <mutex>
#include <atomic>
#include <cstdlib>
#include <pthread.h>
#include <algorithm>
#include "Graph.h"
#include "methods.h"

using namespace std;
using namespace std::chrono;
using std::vector;







vector<int> get_keys( Graph g){
    vector<int> keys;
    for (const auto &x : g.adj_out)
        keys.push_back(x.first);
    return keys;
}
vector<int> get_in_keys( Graph g){
    vector<int> keys;
    for (const auto &x : g.adj_out)
        keys.push_back(x.first);
    return keys;
}


struct thread_data {
    int thread_id;
    string message;
    Graph result;
    vector<int> keys;
    //vector<int> in_keys;
    //int first_key;
    //int last_key;
};
void add_result_to_file (double result, string f)
{
    ofstream results_file;
    results_file.open(f, ios_base::app); // append instead of overwrite
    results_file << result<< "\n";
    results_file.close();
}

void *Create_graph(void *threadarg) {
    struct thread_data *my_data;
    Graph g;
    int a, b;

    my_data = (struct thread_data *) threadarg;
    ifstream infile(my_data->message);

    if (infile.is_open()) {
        while (infile >> a >> b)
            g.add_edge_unweighted(a, b);
        infile.close();
    }
    //cout << "Thread ID : " << my_data->thread_id;

    my_data->result=g;

    my_data->keys=get_keys(my_data->result);
    //my_data->in_keys=get_in_keys(my_data->result);
    //my_data->first_key=my_data->keys[0];
    //my_data->last_key=my_data->keys[my_data->keys.size()-1];

    pthread_exit(NULL);

}

void *update_keys(void *threadarg)
{
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;
    my_data->keys= get_keys(my_data->result);
    //my_data->first_key=my_data->keys[0];
    //my_data->last_key=my_data->keys[my_data->keys.size()-1];
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    cout <<"start"<<endl;
    Graph temp;


    vector<string> files = globVector("/home/user/Code/Graph_creation/Parallel/splitfiles/*");
    //vector<Graph *> graphs(files.size());



    pthread_t threads[files.size()];
    struct thread_data td[files.size()];
    int rc;
    int i;
    auto start = std::chrono::system_clock::now();

    for (i = 0; i < files.size(); i++) {
        //cout << "main() : creating thread, " << i << endl;
        td[i].thread_id = i;
        td[i].message = files[i];
        rc = pthread_create(&threads[i], NULL, Create_graph, (void *) &td[i]);

        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }

    }

    for (i = 0; i < files.size(); i++) {
        (void) pthread_join(threads[i], NULL);

    }
    auto end = std::chrono::system_clock::now();
    double creation= std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()/1000.0;
    cout << "creation time:"<< creation <<endl;
    add_result_to_file (creation, "creation_time_parallel.txt");
    //cout <<"joined threads";


    /*for (int j = 0; j < files.size(); j++) {
        td[j].result.print_graph();
        cout << "[" ;
        for (int k=0; k<td[j].keys.size();k++)
            cout << td[j].keys[k]<<"  ";
        cout << "]" <<endl;
        cout << "--------------------------" << endl;
        cout<< "first key   " <<td[j].first_key;
        cout<< "   last key" <<td[j].last_key;
        cout << "-------" << endl;}*/

    //reorganizing the graph
    auto start1 = std::chrono::system_clock::now();
    if (files.size()>1){
        // reorganize adj_out
        for (int l = 0; l < files.size()-1; l++)
        { //cout << "l= "<< l <<endl;
            int m = l+1;

            for(auto it:td[l].keys)
            { while (m<files.size()-1){
                    if (std::binary_search(td[m].keys.begin(), td[m].keys.end(), it)) {
                        td[l].result.adj_out[it].insert( td[l].result.adj_out[it].end(), td[m].result.adj_out[it].begin(), td[m].result.adj_out[it].end());

                        td[m].result.adj_out.erase(it);

                    }
                    //std::cout <<"test;";
                    m++;}
            }}
    }

    // get new keys

    pthread_t threads_keys[files.size()];
    //updating the keys after reorganization
    for (int j = 0; j < files.size(); j++) {
        //cout << "main() : creating thread, " << j << endl;
        td[j].thread_id = j;
        td[j].message = files[j];
        rc = pthread_create(&threads_keys[j], NULL, update_keys, (void *) &td[j]);

        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }

    }

    for (int j = 0; j < files.size(); j++) {
        (void) pthread_join(threads_keys[j], NULL);

    }

    auto end1 = std::chrono::system_clock::now();
    double reorganization= std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count()/1000.0;
    add_result_to_file (reorganization, "reorganization_time_parallel.txt");

    //cout << "graph should be printed before this";

    /*for (int j = 0; j < files.size(); j++) {
        td[j].result.print_graph();
        cout << "[" ;
        for (int k=0; k<td[j].keys.size();k++)
            cout << td[j].keys[k]<<"  ";
        cout << "]" <<endl;
        cout<< "first key   " <<td[j].first_key;
        cout<< "   last key" <<td[j].last_key;
        cout << "-------" << endl;}*/

    // creating keys dictionary
    auto start2 = std::chrono::system_clock::now();
    map <int,int> keys_dictionary;
    for (int t=0; t<files.size();t++){
        for (auto const &x : td[t].keys) {
            keys_dictionary[x]=t;
        }
    }
    auto end2 = std::chrono::system_clock::now();
    double dictionary= std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count()/1000.0;
    add_result_to_file (dictionary, "dictionary_time_parallel.txt");

    cout << "number of files=" << files.size() <<  "\n";


    FILE *fp;
    unsigned long peaksize = 0;
    char buf[1024];
    fp = fopen("/proc/self/status", "r");
    if (fp == NULL)
        return -1;
    while (fgets(buf, sizeof(buf) - 1, fp) != NULL) {
        if (sscanf(buf, "VmPeak:%lu", &peaksize) > 0) {
            break;
        }
    }
    fclose(fp);
    cout << peaksize / 1024 << endl;
    ofstream outfile1;
    outfile1.open("creation_ram_parallel.txt", ios_base::app); // append instead of overwrite
    outfile1 << peaksize / 1024 << "\n";

    return 0;


}