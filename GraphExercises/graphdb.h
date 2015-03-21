//
//  graph.h
//  Graph Algorithms
//
//  Created by Bill Salefski on 07-Mar-15.
//  Copyright (c) 2015 Bill Salefski. All rights reserved.
//

#ifndef __Graph_Algorithms__graph__
#define __Graph_Algorithms__graph__

#include <vector>
#include <string>

const int MAXV = 30; // maximum verticies in graph
const int maxVertexNameLength = 10;

struct edgenode {
    int y; // to vertex
    int w; // weight
    edgenode* next;
};

class graphDatabaseClass {
    std::vector<edgenode*> edges; // edges out of vertex n
    std::vector<int> degree; // degree of vertex n
    std::vector<std::string> vertexName; // name of vertex
    int nvertices=0; // total vertices in graph
    int nedges=0; // total number of edges in graph
    bool directed=false; // true if graph is directed
    
public:

    void initializeGraph(bool isDirected);
    void insertEdge(int x, int y, int weight, bool directed);
    void readGraph(FILE* f);
    void printGraph (FILE* f);
    int lookupVertexIndex (std::string vertexName);
    
    std::string getVertexName(int i) { return vertexName.at(i); }
    edgenode* getEdges(int i) { return edges.at(i); };
    int numVertices() { return nvertices; };
    bool isDirected() { return directed; }
};

#endif /* defined(__Graph_Algorithms__graph__) */
