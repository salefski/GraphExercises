//
//  VertexPrintVisitingClass.h
//  Graph Algorithms
//
//  Created by Bill Salefski on 09-Mar-15.
//  Copyright (c) 2015 Bill Salefski. All rights reserved.
//

#ifndef Graph_Algorithms_VertexPrintVisitingClass_h
#define Graph_Algorithms_VertexPrintVisitingClass_h


#include "findCycleClass.h"

class findCycleClass : public vertexVistingClass {
    
public:
    void processVertexEarly (graphDatabaseClass* g, int v) {
        printf("Processing Vertex Early %s\n", g->getVertexName(v).c_str());
    }
    
    void processVertexLate (graphDatabaseClass* g, int v) {
        printf("Processing Vertex Late %s\n", g->getVertexName(v).c_str());
    }
    
    void processEdge (graphDatabaseClass* g, int x, int y, int w) {
        printf("Processing Edge between %s", g->getVertexName(x).c_str());
        printf(" and %s", g->getVertexName(y).c_str());
        printf(" of weight %i\n", w);
    }
    
    void processEdgeFor
};


#endif
