//
//  vertexPrintVisitingClass.cpp
//  Graph Algorithms
//
//  Created by Bill Salefski on 09-Mar-15.
//  Copyright (c) 2015 Bill Salefski. All rights reserved.
//
#include <stdio.h>
#include "graphdb.h"
#include "vertexPrintVisitingClass.h"

void processVertexEarly (graphDatabaseClass* g, int v) {
        printf("Process Vertex Early %s\n", g->getVertexName(v).c_str());
}
    
void processVertexLate (graphDatabaseClass* g, int v) {
        printf("Process Vertex Late %s\n", g->getVertexName(v).c_str());
}
    
void processEdge (graphDatabaseClass* g, int x, int y, int w) {
        printf("Process Edge between %s", g->getVertexName(x).c_str());
        printf(" and %s", g->getVertexName(y).c_str());
        printf(" of weight %i\n", w);
}
