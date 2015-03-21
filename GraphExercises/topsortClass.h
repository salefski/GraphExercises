//
//  depththFirstSearch.h
//  Graph Algorithms
//
//  Created by Bill Salefski on 07-Mar-15.
//  Copyright (c) 2015 Bill Salefski. All rights reserved.
//
#ifndef __Graph_Algorithms__topsortClass__
#define __Graph_Algorithms__topsortClass__

#include <stdio.h>
#include "graphdb.h"
#include <stack>
#include "topsortClass.h"

class topographialSortClass {
    std::stack<int> sortStack;
    std::vector<int> sortedVector;

    enum edgeClassification {unknownEdge, treeEdge, backEdge, forwardEdge, crossEdge};
    
    struct vertexRecord {
        bool processed; // which vertices have been processed
        bool discovered; // which vertices have been found
        int entryTime;
        int exitTime;
        int parent; // discovery relation, -1 is impossible value
        int reachableAncestor;
        int treeOutDegree;
    };
    
    std::vector<vertexRecord> vertexInfo;
    //
    // edge record used for debugging
    struct edgeRecord {
        edgeClassification edgeType;
        bool inAdjacencyList;
    };
    std::vector<std::vector<edgeRecord> > edgeInfo; // only used for debugging
    
    graphDatabaseClass* graphToProcess=nullptr; // graph we are searching

    int searchTimer = 0;
    bool finished = false;
    
public:
    void initializeSort (graphDatabaseClass* g);
    void topSortReport();
    void topSort(int start);
    
private:
    edgenode* getNextEdgeToProcess(std::deque<edgenode*>& edgeDeque);
    void processVertexEarly (int v);
    void processVertexLate (int v);
    void processEdge (int x, int y, int w);
    bool checkForCycle (int x, int y);
    void printEdgeClassification (edgeClassification edgeIsA);
    edgeClassification classifyEdge (int x, int y);
    void dfs (int start);
};

#endif /* defined(__Graph_Algorithms__topsortClass__) */
