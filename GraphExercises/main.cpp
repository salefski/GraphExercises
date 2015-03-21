//
//  main.cpp
//  Graph Algorithms
//
//  Created by Bill Salefski on 07-Mar-15.
//  Copyright (c) 2015 Bill Salefski. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include "graphdb.h"
#include <unistd.h>
#include "depthFirstSearch.h"
#include "topsortClass.h"

int main(int argc, const char * argv[]) {
    graphDatabaseClass* g = nullptr;
    depthFirstSearchClass* dfs=nullptr;
    topographialSortClass* topSorter=nullptr;
    
    const char * ifname = "/Users/Bill/Google Drive/Computer and Network/MacProjects/Graph Algorithms/Graph Algorithms/Exercise5-2.txt";
    
    const char * ofname = "/Users/Bill/Google Drive/Computer and Network/MacProjects/Graph Algorithms/Graph Algorithms/output.txt";
    const std::string startNodeName("A");
    
    FILE* inFile=nullptr, *outFile=nullptr;
    
    int start = 0;
    
    g = new graphDatabaseClass;
    
    inFile = fopen(ifname, "r");
    if(inFile == nullptr) {
        printf("Unable to open\n");
        return 1;
    }
    g->readGraph(inFile);
    fclose(inFile);
    
    outFile = fopen(ofname, "w");
    if(outFile == nullptr) {
        printf("Unable to open output file\n");
        return 1;
    }
    g->printGraph(outFile);
    fclose(outFile);
    
    start = g->lookupVertexIndex(startNodeName);
    
    dfs = new depthFirstSearchClass;
    
    dfs->initializeSearch(g);
    dfs->dfs(start);
    dfs->dfsReport();
    
    topSorter = new topographialSortClass;
    topSorter->initializeSort(g);
    topSorter->topSort(start);
    topSorter->topSortReport();

    return 0;
};
