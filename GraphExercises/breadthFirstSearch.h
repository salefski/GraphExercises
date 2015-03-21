//
//  breadthFirstSearch.h
//  Graph Algorithms
//
//  Created by Bill Salefski on 07-Mar-15.
//  Copyright (c) 2015 Bill Salefski. All rights reserved.
//

#ifndef __Graph_Algorithms__breadthFirstSearch__
#define __Graph_Algorithms__breadthFirstSearch__

#include <stdio.h>
#include "graphdb.h"
#include <queue>
#include "vertexVisitingClass.h"

class breadthFirstSearchClass {
    struct vertexRecord {
        bool processed; // which vertices have been processed
        bool discovered; // which vertices have been found
        int parent; // discovery relation
    };
    
    std::vector<vertexRecord> vertexInfo;
    graphDatabaseClass* graphToProcess=nullptr; // graph we are searching
    vertexVistingClass* visitingActions=nullptr;

    edgenode* getNextEdgeToProcess(std::deque<edgenode*>& edgeDeque);
    
public:
    void initializeSearch (graphDatabaseClass* g, vertexVistingClass* v);
    void bfs (int start);
};

#endif /* defined(__Graph_Algorithms__breadthFirstSearch__) */
