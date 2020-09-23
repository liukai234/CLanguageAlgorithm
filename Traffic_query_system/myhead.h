/*
 * @Description: 
 * @Author: 
 * @Date: 2019-11-16 10:00:47
 * @Version: 
 * @LastEditTime: 2019-11-25 17:17:30
 * @LastEditors: Liu Kai
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <io.h>
#include <stdbool.h>
#include <string.h>
#define FINITY 5000
// help检索表总数
#define SELATION 6
#define M 20
#define MAXSTRING 200
// 起步价
#define FLAG_FALL_PRICE 5
// 每公里单价
#define PRICE 1.2
typedef int edgetype;
typedef char vertextype;
// typedef enum
// {
//     FALSE,
//     TRUE
// } boolean;

// 城市信息链表
typedef struct infor
{
    char nameCity[MAXSTRING];
    int sumPersion;
    struct infor *next;
} info;

typedef int dist[M][M];
// path用来保存当前结点的前驱, 输出时要依靠栈来输出
typedef int path[M][M];

//交通网络图
typedef struct
{
    vertextype vers[M][MAXSTRING];
    edgetype edges[M][M];
    int n, e;
} Mgraph;

// 前向声明块
void creatM(Mgraph *g, char *filename, int c);
void dijkstra(Mgraph g, int v0, path p, dist d);
void print(Mgraph g, path p, dist d, int v0, int vEnd);
void floyd(Mgraph g, path p, dist d);
info *init();
info *insert(FILE *pFile, info *head, char *nameCity);
void linkPrint(info *head);
float fareCal(int distance);
bool modify(Mgraph g);
void help();

// 菜单检索表
char selarr[SELATION][MAXSTRING] = {"help", "dijkstra", "floyd", "exit", "print", "modify"};
// 城市检索表
char cities[M][MAXSTRING];
