//
//  graph.cpp
//  Graph Algorithms
//
//  Created by Bill Salefski on 07-Mar-15.
//  Copyright (c) 2015 Bill Salefski. All rights reserved.
//

#include "graphdb.h"
#include <istream>
#include <string>
//
// directed edge is an edge in the adjacency matrix and isDirected==false
// undirected edge represented by two edges in the adjacency matrix for x and y and isDirected == true
// So, search algorithms need to check if the graph is directed or not
//
void graphDatabaseClass::initializeGraph(bool isDirected) {
    nvertices = 0;
    nedges = 0;
    directed = isDirected;
    edges.resize(MAXV+1, nullptr);
    degree.resize(MAXV+1, 0);
    vertexName.resize(MAXV+1, "");
};

void graphDatabaseClass::insertEdge(int x, int y, int weight, bool directed) {
    edgenode *p=nullptr; // new edgenode
    edgenode *t=nullptr; // traversal if we need it
    
    p = new edgenode;
    
    p->w = weight;
    p->y = y;
    p->next = nullptr;
    if((t=edges.at(x)) == nullptr) {
        edges.at(x) = p; // first edge, insert at the head of the list
    } else {
        // insert at the tail. Find the tail
        while(t->next != nullptr) {
            t = t->next;
        }
        t->next = p;
    };
    degree.at(x) = degree.at(x) + 1;;
    if (directed == false) {
        graphDatabaseClass::insertEdge(y, x, weight, true);
    } else {
        ++nedges;
    }
};

int graphDatabaseClass::lookupVertexIndex (std::string vertexNameToFind) {
    int i=0;
    for(i=0; i<nvertices; ++i) {
        if(vertexName.at(i).compare(vertexNameToFind) == 0) {
            return(i);
        }
    }
    return(-1);
}

// file format
// 1: numVertices numEedges isDirected
// 2-#verticies: vertexName
// #verticies: fromVertex toVertex weight
//
void graphDatabaseClass::readGraph(FILE* f) {
    int i=0;
    int numEdges=0; // counter for # edges, inserteEdge increments g->nedges
    int isDirected=0;
    int x=0, y=0; // vertices in edge (x,y)
    int w=0; // weight of edge
    char fromVertexName[maxVertexNameLength];
    char toVertexName[maxVertexNameLength];
    
    initializeGraph(true);
    fscanf(f, "%i %i %i", &nvertices, &numEdges, &isDirected);
    directed = (isDirected==1);
    
    // read in the vertex names
    for(i=0; i<nvertices; ++i) {
        fscanf(f, "%s", fromVertexName);
        vertexName.at(i).assign(fromVertexName);
    }
    
    // Read in the edges.
    while(!feof(f)) {
        if(3==fscanf(f, "%s %s %i", fromVertexName, toVertexName, &w)) {
                x = lookupVertexIndex(fromVertexName);
                y = lookupVertexIndex(toVertexName);
                insertEdge(x, y, w, true); // all edges are explicit, so directed == true
        } else {
            printf("Error reading graph file\n");
        }
    }
}

void graphDatabaseClass::printGraph (FILE* f) {
    int i=0; /* counter */
    edgenode *p; /* temporary pointer */
    
    fprintf(f, "%i %i %i\n", nvertices, nedges, directed);
    
    // print the vertex names
    for(i=0; i<nvertices; ++i) {
        fprintf(f, "%s\n", vertexName.at(i).c_str());
    };
    
    for (i=0; i < nvertices; ++i) {
        p = edges.at(i);
        while (p != nullptr) {
            fprintf(f, "%s ", vertexName.at(i).c_str());
            fprintf(f, "%s ", vertexName.at(p->y).c_str());
            fprintf(f, "%i\n", p->w);
            p = p->next;
        }
    }
}




