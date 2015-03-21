//
//  depthFirstSearch.cpp
//  Graph Algorithms
//
//  Created by Bill Salefski on 07-Mar-15.
//  Copyright (c) 2015 Bill Salefski. All rights reserved.
//

#include "depthFirstSearch.h"

//
// enable diagnostic stuff
//
const bool noisy = true;
const bool checkForCycles = true;

depthFirstSearchClass::depthFirstSearchClass() {
    searchTimer = 0; // incremented each time we enter or exit a vertex
    finished = false; // used for early termination. Unwinds to first call
}

void depthFirstSearchClass::initializeSearch (graphDatabaseClass* g) {

    graphToProcess = g;
    searchTimer = 0; // incremented each time we enter or exit a vertex
    finished = false; // used for early termination. Unwinds to first call
    
    vertexInfo.resize(graphToProcess->numVertices(), {false, false, 0, 0, -1, -1, 0});
    //
    // create the 2D vector for edge info
    //
    for(int i = 0; i < graphToProcess->numVertices(); ++i) {
        std::vector<edgeRecord> p;
        std::vector<edgeRecord>::iterator itr;
        p.resize(graphToProcess->numVertices());
        for(itr=p.begin(); itr<p.end(); ++itr) {
            itr->edgeType = unknownEdge;
            itr->inAdjacencyList = false;
        }
        edgeInfo.push_back(p);
    }
}
//
// vertex processing routines
//
void depthFirstSearchClass::processVertexEarly (int v) {
    if(noisy) {
        printf("Process Vertex Early %s\n", graphToProcess->getVertexName(v).c_str());
    }
    vertexInfo[v].reachableAncestor = v; // initial version until we find a more distant ancestor
}

void depthFirstSearchClass::processVertexLate (int vertexID) {
    bool isRoot = false;
    int earliestReachableTimeForVertexID = -1;
    int earliestReachableTimeForParentOfVertexID = -1;
    
    if(noisy) {
        printf("Process Vertex Late %s\n", graphToProcess->getVertexName(vertexID).c_str());
    }
    // handle the root of the tree
    if(vertexInfo[vertexID].parent < 0) {
        if(noisy) {
            printf("Vertex %s", graphToProcess->getVertexName(vertexID).c_str());
            printf(" is the root\n");
        }
        if(vertexInfo[vertexID].treeOutDegree > 1) {
            printf("Vertex %s", graphToProcess->getVertexName(vertexID).c_str());
            printf(" is a root articulation vertex\n");
        }
        return;
    }
    // handle the immediate children of the root
    isRoot = vertexInfo[vertexInfo[vertexID].parent].parent < 1;
    if((!isRoot) && (vertexInfo[vertexID].reachableAncestor == vertexInfo[vertexID].parent)) {
        printf("Vertex %s", graphToProcess->getVertexName(vertexInfo[vertexID].parent).c_str());
        printf(" is a parent articulation vertex\n");
    }
    if(vertexInfo[vertexID].reachableAncestor == vertexID) {
        printf("Vertex %s", graphToProcess->getVertexName(vertexInfo[vertexID].parent).c_str());
        printf(" is a bridge articulation vertex\n");
        // test if vertexID is not a leaf
        if(vertexInfo[vertexID].treeOutDegree > 0) {
            printf("Vertex %s", graphToProcess->getVertexName(vertexID).c_str());
            printf(" is a bridge articulation vertex\n");
        }
    }
    earliestReachableTimeForVertexID = vertexInfo[vertexInfo[vertexID].reachableAncestor].entryTime;
    earliestReachableTimeForParentOfVertexID = vertexInfo[vertexInfo[vertexInfo[vertexID].parent].reachableAncestor].entryTime;
    
    if(earliestReachableTimeForVertexID < earliestReachableTimeForParentOfVertexID) {
        vertexInfo[vertexInfo[vertexID].parent].reachableAncestor = vertexInfo[vertexID].reachableAncestor;
    }
}

void depthFirstSearchClass::processEdge (int x, int y, int w) {
    if(noisy) {
        printf("Process Edge between %s", graphToProcess->getVertexName(x).c_str());
        printf(" and %s", graphToProcess->getVertexName(y).c_str());
        printf(" of weight %i\n", w);
    }
    edgeClassification edgeIsA = unknownEdge;
    edgeIsA = classifyEdge(x, y);
    // if the edge is a tree, increase the degree of the from vertex
    if(edgeIsA == treeEdge) {
        ++vertexInfo[x].treeOutDegree;
    }
    // if this is a back edge, then it can either be a true backedge if vertexInfo[x].parent != y
    // if vertexInfo[x].parent == y and the graph is undirected, then this is just part of the
    // undirected edge to the parent
    if((edgeIsA == backEdge) && (vertexInfo[x].parent != y)) {
        if(vertexInfo[y].entryTime < vertexInfo[vertexInfo[x].reachableAncestor].entryTime) {
            vertexInfo[x].reachableAncestor = y;
        }
    }
    edgeInfo[x][y].edgeType = edgeIsA;
}

depthFirstSearchClass::edgeClassification depthFirstSearchClass::classifyEdge (int x, int y) {
    //
    // if the edge connects a child node to a parent node, it is a treeEdge
    //
    if(vertexInfo[y].parent == x) return treeEdge;
    //
    // if the toVertex is discovered and is not been processed,
    // then this is a back edge on the current depth-first descent
    //
    if(vertexInfo[y].discovered && !vertexInfo[y].processed) return backEdge;
    //
    // if y has already been processed, and we entered y later than we entered the current
    // vertex x, then this is a forward edge
    //
    if(vertexInfo[y].processed && (vertexInfo[y].entryTime > vertexInfo[x].entryTime)) return forwardEdge;
    //
    // However, if we entered the y earlier than we entered the current vertex x,
    // this is a cross edge
    //
    if(vertexInfo[y].processed && (vertexInfo[y].entryTime < vertexInfo[x].entryTime)) return crossEdge;
    //
    // Should not get here!
    //
    if(noisy) {
        printf("Warning: unclassified edge from vertex %s",graphToProcess->getVertexName(x).c_str());
        printf(" to %s", graphToProcess->getVertexName(y).c_str());
    }
    return unknownEdge;
}

//
// picks the next edge based on lexicographical order of tovertex names.
//
edgenode* depthFirstSearchClass::getNextEdgeToProcess(std::deque<edgenode*>& edgeDeque) {
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
// checks for cycle between x and y
//
bool depthFirstSearchClass::checkForCycle (int x, int y) {
    bool returnVal = false;
    if(vertexInfo[y].discovered) {
        // we have encountered an already discovered vertex
        // there is potentially cycle in graph
        // if x is not a parent => is a cycle
        if(vertexInfo[x].parent != y) {
            // the from vertex is not the parent of this vertex => is a cycle
            returnVal = true;
        } else {
            // the from vertex is the parent, this is a cycle in a directed graph
            // but not a cycle in an undirected graph
            returnVal = graphToProcess->isDirected();
        }
    }
    if((noisy) && (returnVal == true)) {
        printf("Cycle discovered from %s", graphToProcess->getVertexName(x).c_str());
        printf(" to %s\n\n", graphToProcess->getVertexName(y).c_str());
    }
    return returnVal;
}
//
// printEdgeedgeClassification
//
void depthFirstSearchClass::printEdgeClassification (edgeClassification edgeIsA) {

    if(edgeIsA == treeEdge) printf("tree");
    if(edgeIsA == backEdge) printf("back");
    if(edgeIsA == forwardEdge) printf("forward");
    if(edgeIsA == crossEdge) printf("cross");
    if(edgeIsA == unknownEdge) printf("unknown");
}
//
// edgeReport finds all edges in the graph and tells what they are after dfs has decorated
// the verticies
//
void depthFirstSearchClass::dfsReport() {
    int x = 0; // vertex
    edgenode* p = nullptr; // temporary

    for(x=0; x<graphToProcess->numVertices(); ++x) {
        printf("-------------------------------------------------------------------\n");
        // report on the vertex
        printf("Vertex %s", graphToProcess->getVertexName(x).c_str());
        printf(" was%s processed\n", (vertexInfo[x].processed? "" : " not"));
        printf("Vertex %s", graphToProcess->getVertexName(x).c_str());
        printf(" was%s discovered\n", (vertexInfo[x].discovered? "" : " not"));
        printf("entryTime=%i exitTime=%i\n", vertexInfo[x].entryTime, vertexInfo[x].exitTime);
        printf("TreeOutDegree=%i\n", vertexInfo[x].treeOutDegree);
        if(vertexInfo[x].parent < 0) {
            printf("Is the root node\n");
        } else {
            printf("Has parent %s\n", graphToProcess->getVertexName(vertexInfo[x].parent).c_str());
        };
        // report on the edges out of the vertex
        if((p = graphToProcess->getEdges(x))) {
            for(/* initialized in if */ ; p != nullptr; p = p->next) {
                printf("Edge from vertex %s", graphToProcess->getVertexName(x).c_str());
                printf(" to vertex %s", graphToProcess->getVertexName(p->y).c_str());
                printf(" of weight %i", p->w);
                printf(" is a ");
                printEdgeClassification (edgeInfo[x][p->y].edgeType);
                printf(" edge and it");
                printf(" was%s processed\n", (edgeInfo[x][p->y].inAdjacencyList? "" : " not"));
            }
        } else {
            printf("Has no outgoing edges\n");
        }
    };
}

//
// depth first search
//
void depthFirstSearchClass::dfs (int vertexID) {
    std::deque<edgenode*> edgesToProcess; // list of edges to process from this vertex
    
    int y = 0; // successor vertex
    int w = 0; // edge weight
    edgenode* p = nullptr; // temporary
    //
    // initialize
    //
    vertexInfo[vertexID].discovered = true;
    vertexInfo[vertexID].entryTime = ++searchTimer;
    processVertexEarly(vertexID);
    //
    // get all the edges we need to process from the adjencency list
    //
    for(p = graphToProcess->getEdges(vertexID); p != nullptr; p = p->next) {
        edgesToProcess.push_front(p);
        edgeInfo[vertexID][p->y].inAdjacencyList = true;
    };
    //
    // process the edges from this vertex
    //
    while(!edgesToProcess.empty()) {
        p = getNextEdgeToProcess(edgesToProcess);
        y = p->y;
        w = p->w;
        if(vertexInfo[y].discovered == false) {
            // we have not seen this vertex, follow it
            // vertexID is the parent of y
            vertexInfo[y].parent = vertexID;
            // process the edge
            processEdge(vertexID, y, w);
            // check if there is a cycle
            if(checkForCycles) checkForCycle(vertexID, y);
            // continue the search through y
            dfs(y);
        } else if((vertexInfo[y].processed == false) || graphToProcess->isDirected()) {
            processEdge(vertexID, y, w);
            // check if there is a cycle
            if(checkForCycles) checkForCycle(vertexID, y);
            if(finished) return;
        }
    }
    processVertexLate(vertexID);
    vertexInfo[vertexID].processed = true;
    vertexInfo[vertexID].exitTime = ++searchTimer;
 }
