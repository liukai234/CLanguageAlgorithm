#pragma once
#include <stdio.h>
#include <stdlib.h>
#define M 20
#define FINITY 5000
typedef char vertextype;
typedef int edgetype;
typedef struct{
	vertextype vexs[M];
	edgetype edges[M][M];
	int n, e;
}MGraph;
typedef struct edgedata{
	int begin, end;
	int length;
}edge;

// Ç°ÏòÉùÃ÷
void creat(MGraph* g, char* filename, int c);
void prim(MGraph g, edge* tree);
