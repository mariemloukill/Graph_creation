- examples not very clear ( similar software ) 


- Problem : disk access speed for parallel graph creation ( migh limit us to disk speed , same performance as sequential)


---

based on what she said : 
1. sequential :
Baseline

2. Parallel 

Takes more RAM , takes less Time

3. Sequential split 

Takes less Ram , takes more time 

---

possible problems 

- use thread instead of pthread

- log takes time , might effect our clock
---


Data strcture possibility for adjacency list : 
```cpp
    map<int,set<int>>
    map<int,unordered_set<int>>
    vector<set<int>>
    vector<vector<int>> (if key unavailable -> NULL pointer on that vector)
    vector<unordered_set<int>>
    unordered_map<int,vector<int>>
    unordered_map<int,set<int>>
    unordered_map<int,unordered_set<int>>

```



---

other note

```
Graphs_data[l].g.adj_out[it].insert( 
    Graphs_data[l].g.adj_out[it].end(), 
    Graphs_data[m].g.adj_out[it].begin(), 
    Graphs_data[m].g.adj_out[it].end()
    );
```

- this merge is slow


---

merge is not parallel



t].end(), 
    Graphs_data[m].g.adj_out[it].begin(), 
    Graphs_data[m].g.adj_out[it].end()
    );
```

- this merge is slow


---

merge is not parallel







---

















