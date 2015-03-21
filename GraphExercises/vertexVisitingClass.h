//
//  vertexVisitingClass.h
//  Graph Algorithms
//
//  Created by Bill Salefski on 09-Mar-15.
//  Copyright (c) 2015 Bill Salefski. All rights reserved.
//

#ifndef __Graph_Algorithms__vertexVisitingClass__
#define __Graph_Algorithms__vertexVisitingClass__

#include <stdio.h>
#include "graphdb.h"

class vertexVistingClass {
public:
    
    void virtual processVertexEarly (graphDatabaseClass* g, int v)=0;
    void virtual processVertexLate (graphDatabaseClass* g, int v)=0;
    void virtual processEdge (graphDatabaseClass* g, int x, int y, int w)=0;
};

#endif /* defined(__Graph_Algorithms__vertexVisitingClass__) */
