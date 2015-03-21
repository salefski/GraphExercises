//
//  breadthFirstSearch.cpp
//  Graph Algorithms
//
//  Created by Bill Salefski on 07-Mar-15.
//  Copyright (c) 2015 Bill Salefski. All rights reserved.
//

#include "breadthFirstSearch.h"

#include <queue>

void breadthFirstSearchClass::initializeSearch (graphDatabaseClass* g, vertexVistingClass* v) {
   
    graphToProcess = g;
    visitingActions = v;
    
    vertexInfo.resize(graphToProcess->numVertices(), {false, false, -1});
    
}
//
// picks the next edge based on lexicographical order of tovertex names.
//
edgenode* breadthFirstSearchClass::getNextEdgeToProcess(std::deque<edgenode*>& edgeDeque) {
    std::deque<edgenode*>::iterator etr, lexEtr;
    std::string lexString, cmpString;
    edgenode *returnVal=nullptr;
    //
    // initialize to the first element
    //
    lexEtr = etr = edgeDeque.begin();
    lexString = graphToProcess->getVertexName((*lexEtr)->y);
    //
    // look for someone better
    //
    for(etr=lexEtr+1; etr < edgeDeque.end(); ++etr) {
        cmpString = graphToProcess->getVertexName((*etr)->y);
        if(cmpString.compare(lexString) < 0) {
            // better one. Take it
            lexEtr = etr;
            lexString = cmpString;
        }
    }
    //
    // get the return value and erase it from the edgeDeque
    //
    returnVal = *lexEtr;
    edgeDeque.erase(lexEtr);
    
    return returnVal;
}
//
// breadth first search
//
void breadthFirstSearchClass::bfs (int start) {
    std::queue<int> verticesToProcess;
    std::deque<edgenode*> edgesToProcess;
    
    int v = 0; // current vertex
    int y = 0; // successor vertex
    int w = 0; // edge weight
    edgenode* p = nullptr;
    //
    // initialize
    //
    verticesToProcess.push(start);
    vertexInfo[start].discovered = true;
    //
    // traverse breadth first by taking the first element of the queue
    //
    while(!verticesToProcess.empty()) {
        v = verticesToProcess.front();
        verticesToProcess.pop();
        visitingActions->processVertexEarly(graphToProcess, v);
        vertexInfo[v].processed = true;
        //
        // get all the edges we need to process
        //
        for(p = graphToProcess->getEdges(v); p != nullptr; p = p->next) {
            edgesToProcess.push_front(p);
        };
        //
        // process the edges at this vertex
        //
        while(!edgesToProcess.empty()) {
            p = getNextEdgeToProcess(edgesToProcess);
            y = p->y;
            w = p->w;
            if((vertexInfo[y].processed == false) || graphToProcess->isDirected()) {
                visitingActions->processEdge(graphToProcess, v, y, w);
            };
            if(vertexInfo[y].discovered == false) {
                verticesToProcess.push(y);
                vertexInfo[y].discovered = true;
                vertexInfo[y].parent = v;
            }
        }
        visitingActions->processVertexLate(graphToProcess, v);
    }
}
