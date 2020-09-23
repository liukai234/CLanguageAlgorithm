/*
 * @Description: 
 * @Author: 
 * @Date: 2019-11-13 12:37:59
 * @Version: 
 * @LastEditTime: 2019-11-16 09:13:37
 * @LastEditors: Liu Kai
 */
// test test git git
#include <stdio.h>
#include <stdlib.h>
#include "topsort.h"

#define MAXFILENAME 100
int visited[M];

int main(int args, char *argv[])
{
    printf("The program starting\n");
    AovGraph *g;
    g = (AovGraph *)malloc(sizeof(AovGraph));
    // if(c == 0) no direct if(c == 1) have direct
    int c = 1; 
    char filename[MAXFILENAME] = "Text.txt";
    creat(g, filename, c);
    DfsTraveres(*g);
    TopSort(*g);
    printf("The last line\n");
    return 0;
}

void creat(AovGraph *g, char *filename, int c)
{
    FILE *fp;
    edgenode *s;
    fp = fopen(filename, "r");
    perror((const char *)fp);
    if (fp)
    {
        int i, j, k;
        printf("file open success\n");
        fscanf(fp, "%d%d", &g->n, &g->e);

        for (i = 0; i < g->n; i++)
        {
            fscanf(fp, "%1s", &g->adjlist[i].vertex);
            g->adjlist[i].id = 0;
            g->adjlist[i].FirstEdge = NULL;
        }
        for (k = 0; k < g->e; ++k)
        {
            fscanf(fp, "%d%d", &i, &j);
            s = (edgenode *)malloc(sizeof(edgenode));
            s->adjvex = j;
            s->next = g->adjlist[i].FirstEdge;
            g->adjlist[i].FirstEdge = s;
            g->adjlist[j].id++;
            if (c == 0)
            {
                s = (edgenode *)malloc(sizeof(edgenode));
                s->adjvex = i;
                s->next = g->adjlist[j].FirstEdge;
                g->adjlist[j].FirstEdge = s;
                g->adjlist[i].id = 0;
            }
        }
        fclose(fp);
    }
    else
    {
        g->n = 0;
    }
}

void DfsTraveres(AovGraph g)
{
    for (int i = 0; i < g.n; ++i)
    {
        visited[i] = 0;
    }
    for (int i = 0; i < g.n; ++i)
    {
        if (!visited[i])
        {
            dfs(g, i);
        }
    }
}

void dfs(AovGraph g, int i)
{
    edgenode *p;
    printf("visited vertex: %c\n", g.adjlist[i].vertex);
    visited[i] = 1;
    p = g.adjlist[i].FirstEdge;
    while (p)
    {
        // p maybe NULL, so p->adjvex is error
        if (!visited[p->adjvex])
        {
            dfs(g, p->adjvex);
        }
        p = p->next;
    }
}

int TopSort(AovGraph g)
{
    int k = 0;
    int i, j, v, flag[M];
    int queue[M];
    int front, rear;
    edgenode *p;
    front = rear = 0;
    for (i = 0; i < g.n; i++)
    {
        flag[i] = 0;
    }
    for (i = 0; i < g.n; i++)
    {
        if (g.adjlist[i].id == 0 && flag[i] == 0)
        {
            queue[rear++] = i;
            flag[i] = 1;
        }
    }
    printf("TopoSort is:\n");
    while (front < rear)
    {
        v = queue[front++];
        printf("%c->", g.adjlist[v].vertex);
        k++; // 计数器自增
        p = g.adjlist[v].FirstEdge;
        while (p)
        {
            j = p->adjvex;
            if (--g.adjlist[j].id == 0 && flag[j] == 0)
            {
                queue[rear++] = j;
                flag[j] = 1;
            }
            p = p->next;
        }
    }
    printf("\n");
    return k; // 返回个数
}