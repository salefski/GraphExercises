//
//  vertexPrintVisitingClass.h
//  Graph Algorithms
//
//  Created by Bill Salefski on 09-Mar-15.
//  Copyright (c) 2015 Bill Salefski. All rights reserved.
//

#ifndef __Graph_Algorithms__vertexPrintVisitingClass__
#define __Graph_Algorithms__vertexPrintVisitingClass__

#include <stdio.h>
#include "graphdb.h"
#include "vertexVisitingClass.h"

class vertexPrintVisitingClass : public vertexVistingClass {

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
    
};

#endif /* defined(__Graph_Algorithms__vertexPrintVisitingClass__) */