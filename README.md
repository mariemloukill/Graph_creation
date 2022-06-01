# Graph Creation

## Overview 

This project aims to determine the best strategy for Graph creation based on provided machine and its specifications.

### Input 

As an input we have Graphs described as an `edge list`. Data has been gathered from [Data sources](./data_sources)

### Output 


## Technical Overview

The entire project was written in `c++`. And can be divided to two main parts

### Initial Implementation

Each of the strategies has its respective `cmake` project, making it simpler to test them individually

`Parallel` : the parallel creation strategy
`Sequential` : The sequential creation Strategy
`Strategy3` : a third *experimental* creation strategy

Each of these projects will run the underlying strategy on the provided input. And then will produce some metrics ( based on the system status) 

### Newer Implementation

This implementation provides a couple of improvements to the initial one. Can be found under `/PFATeam` as a separate `cmake` project


#### Testing multiple Data Structures

We can now test multiple *Graph data structures* for each implementation. 


## Building the Project

This project is built using `cmake`. Prerequisites depend on the module you want to build.

- `C++ 20` or higher : The initial implementation only requires `C++ 14`
- `Boost C++ 1.7` or higher : required by the new implementation

## Usage

