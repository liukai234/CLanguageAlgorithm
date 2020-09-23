/*
 * @Description: 
 * @Author: 
 * @Date: 2019-11-14 12:51:53
 * @Version: 
 * @LastEditTime: 2019-11-16 08:56:47
 * @LastEditors: Liu Kai
 */

#ifndef AOV_TOPSORT_H
#define AOV_TOPSORT_H
#define M 20
typedef char vertextype;
typedef struct node
{
    int adjvex;
    struct node *next;
} edgenode;
typedef struct de
{
    edgenode *FirstEdge;
    vertextype vertex;
    int id; // 带入读的边表结点
} vertexnode;

typedef struct
{
    vertexnode adjlist[M];
    int n, e;
} AovGraph;

// Forward declaration
void creat(AovGraph *g, char *filename, int c);
void dfs(AovGraph g, int i);
void DfsTraveres(AovGraph g);
int TopSort(AovGraph g);
#endif // AOV_TOPSORT_H