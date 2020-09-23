/*
 * @Description: Traffic_query_system
 * @Author: 
 * @Date: 2019-11-16 09:33:34
 * @Version: 2.0
 * @LastEditTime: 2019-11-25 19:10:23
 * @LastEditors: Liu Kai
 */
#include "myhead.h"
info *myinfo;
int main(int args, char *argv[])
{
    int c = 0;
    int v0 = 0;   // 源点
    int vEnd = 0; // 终点
    char find0[MAXSTRING], findEnd[MAXSTRING];
    int sel;
    Mgraph g;
    path p;
    dist d;
    char filename[100] = "Text.txt";
    char cwdPath[MAXSTRING];
    char strsel[MAXSTRING];
    bool exitFlag = false;
    _getcwd(cwdPath, MAXSTRING);
    printf("Current Mgraph saved directory: %s\n", cwdPath);
    printf("Input Type of Mgraph[directed graph is 1 and undirected graph is 0]:");
    scanf("%d", &c);
    myinfo = init(); // First to init
    creatM(&g, filename, c);
    printf("Input \"help\" for help\n");
    while (true)
    {
        scanf("%s", strsel);
        for (sel = 0; sel < SELATION; sel++)
        {
            if (!strcmp(strsel, selarr[sel]))
            {
                break;
            }
        }
        switch (sel)
        {
        case 0:
            help();
            break;
        case 1:
            // dijkstrea算法查找源点到任意结点
            scanf("%s%s", &find0, &findEnd);
            for (sel = 0; sel < g.n; sel++)
            {
                if (!strcmp(find0, cities[sel]))
                {
                    v0 = sel;
                }
                if (!strcmp(findEnd, cities[sel]))
                {
                    vEnd = sel;
                }
            }
            dijkstra(g, v0, p, d);
            print(g, p, d, 0, vEnd); // 对于dijk算法来说, print每次从源点开始
            break;
        case 2:
            scanf("%s%s", &find0, &findEnd);
            for (sel = 0; sel < g.n; sel++)
            {
                if (!strcmp(find0, cities[sel]))
                {
                    v0 = sel;
                }
                if (!strcmp(findEnd, cities[sel]))
                {
                    vEnd = sel;
                }
            }
            floyd(g, p, d);
            print(g, p, d, v0, vEnd);
            break;
        case 3:
            exitFlag = true;
            break;
        case 4:
            linkPrint(myinfo);
            break;
        case 5:
            if (modify(g))
            {
                printf("Test.txt has been updated\n");
            }
            else{
                printf("update ERROR\n");
            }
            // 重建链表和图
            myinfo = init();
            creatM(&g, filename, c);
            break;
        default:
            printf("Command does not exist\n");
            break;
        }
        printf("Execution completed\n");
        if (exitFlag)
        {
            break;
        }
    }

    // linkPrint(myinfo);
    return 0;
}

void help()
{
    printf(
        "dijkstraAlgorithm            dijkstra(Format: dijkstra [startName endName])\n"
        "floydAlgorithm               floyd(Format: floyd [startName endName]\n"
        "linkPrint                    print\n"
        "modifyTextFile               modify\n"
        "help                         help\n"
        "exit                         exit\n");
}

/**
 * @description: 交通网络图的创建
 * @param {type} 
 * @return: 
 */
void creatM(Mgraph *g, char *filename, int c)
{
    int i, j, k, w;
    FILE *pFile;
    pFile = fopen(filename, "r");
    if (pFile)
    {
        fscanf(pFile, "%d%d", &g->n, &g->e);
        for (i = 0; i < g->n; i++)
        {
            fscanf(pFile, "%s", g->vers[i]);
            myinfo = insert(pFile, myinfo, g->vers[i]);
            strcpy(cities[i], g->vers[i]);
        }
        for (i = 0; i < g->n; i++)
        {
            for (j = 0; j < g->n; j++)
            {
                if (i == j)
                {
                    g->edges[i][j] = 0;
                }
                else
                {
                    g->edges[i][j] = FINITY;
                }
            }
        }
        for (k = 0; k < g->e; k++)
        {
            fscanf(pFile, "%d%d%d", &i, &j, &w);
            g->edges[i][j] = w;
            if (c == 0)
            {
                g->edges[j][i] = w;
            }
        }
        fclose(pFile);
    }
    else
    {
        g->n = 0;
    }
}

/**
 * @description: dijk
 * @param {type} 
 * @return: 
 */
void dijkstra(Mgraph g, int v0, path p, dist d)
{
    bool final[M];
    int i, j, k, v, min, x;
    // test print
    // printf("start: %s\n", g.vers[v0]);
    for (v = 0; v < g.n; v++)
    {
        final[v] = false;
        d[0][v] = g.edges[v0][v]; // d中保存的是源点到其他结点的距离
        if (d[0][v] < FINITY && d[0][v] != 0)
        {
            p[0][v] = v0; // p[v]用来保存路径
        }
        else
        {
            p[0][v] = -1;
        }
    }
    final[v0] = true;
    d[0][v0] = 0; // 初始时s中只有v0一个结点
    // 选出v0到其他顶点的距离最小, 依次加入
    for (i = 1; i < g.n; i++) // i从1开始是因为少了v0, v0已经被选择入s中
    {
        min = FINITY;
        for (k = 0; k < g.n; k++)   
        {
            if (!final[k] && d[0][k] < min) // final表示结点是否被选入s中
            {
                v = k;
                min = d[0][k];
            }
        }
        // 输出本次入选的顶点距离
        // test print
        // printf("%s---%d\n", g.vers[v], min);
        if (min == FINITY)
        {
            return;
        }
        final[v] = true;
        for (k = 0; k < g.n; k++)
        {
            if (!final[k] && (min + g.edges[v][k] < d[0][k]))
            {
                d[0][k] = min + g.edges[v][k];
                p[0][k] = v; // 寻找当前结点的前驱, 当前驱不存在时为-1
            }
        }
    }
    // test print
    // for (int i = 0; i < g.n; i++)
    // {
    //     printf("%d ", p[0][i]);
    // }
    // printf("\n");
    // for (int i = 0; i < g.n; i++)
    // {
    //     printf("%d ", d[0][i]);
    // }
    // printf("\n");
}

/**
 * @description: 源点v0到其他结点的最短路径,最小运费, v0表示当前源点
 * @param {type} 
 * @return: 
 */
/* 
void print(Mgraph g, path p, dist d, int v0)
{
    // 依赖st栈寻找前驱后逆序输出
    int st[M];
    int i, pre, top = -1;
    for (i = 0; i < g.n; i++) // i表示正在输出哪个结点的路径
    {
        printf("\nDistancd: %d, path: ", d[v0][i]);
        st[++top] = i;
        pre = p[v0][i];
        // if(i == 1 && pre == -1) printf("当前节点");
        while (pre != -1)
        {
            st[++top] = pre;
            pre = p[v0][pre]; // 不断访问前驱, 当寻找到-1(无前驱)为止
        }
        while (top > 0)
        {
            printf("%s ", g.vers[st[top--]]);
        }
    }
    printf("\n");
} */

/**
 * @description: 源点v0到其他结点的最短路径,最小运费, v0表示当前源点, vEnd表示当前终点
 * @param {type} 
 * @return: 
 */
void print(Mgraph g, path p, dist d, int v0, int vEnd)
{
    int st[M], pre, top = -1;
    st[++top] = vEnd;
    pre = p[v0][vEnd];
    while (pre != -1)
    {
        st[++top] = pre;
        pre = p[v0][pre];
    }
    printf("path: ");
    while (top > 0)
    {
        printf("%s", g.vers[st[top--]]);
        // if (top != 0)
        // {
        printf(" -> ");
        // }
    }
    printf("%s\n", g.vers[vEnd]);
    printf("Distancd: %d, Price: %.1f\n", d[v0][vEnd], fareCal(d[v0][vEnd]));
}

/**
 * @description: 任意一对结点的最短路径,最小费用
 * @param {type} 
 * @return: 
 */
void floyd(Mgraph g, path p, dist d)
{
    int i, j, k;
    for (i = 0; i < g.n; i++)
    {
        for (j = 0; j < g.n; j++)
        {
            d[i][j] = g.edges[i][j];
            if (i != j && d[i][j] < FINITY)
            {
                p[i][j] = i;
            }
            else
            {
                p[i][j] = -1;
            }
        }
    }
    for (k = 0; k < g.n; k++)
    {
        for (i = 0; i < g.n; i++)
        {
            for (int j = 0; j < g.n; j++)
            {
                if (d[i][j] > (d[i][k] + d[k][j]))
                {
                    d[i][j] = d[i][k] + d[k][j];
                    p[i][j] = k;
                }
            }
        }
    }
}

/**
 * @description: 带头结点链表初始化
 * @param {type} void
 * @return: head
 */
info *init()
{
    info *head;
    head = (info *)malloc(sizeof(info));
    head->next = NULL;
    return head;
}

/**
 * @description: 链表尾插
 * @param {type: node_stu*} head
 * @return:head
 */
info *insert(FILE *pFile, info *head, char *nameCity)
{
    info *p, *pre;
    pre = head;
    p = head->next;
    while (p)
    {
        pre = p;
        p = p->next;
    }
    p = (info *)malloc(sizeof(info));
    strcpy(p->nameCity, nameCity);
    fscanf(pFile, "%d", &p->sumPersion);
    p->next = pre->next;
    pre->next = p;
    return head;
}

/**
 * @description: 链表输出
 * @param {type} 
 * @return: 
 */
void linkPrint(info *head)
{
    info *p, *pre;
    p = head->next;
    if (!p)
    {
        printf("no City Infomation\n");
        return;
    }
    while (p)
    {
        printf("nameCity:%s sumPersion:%d\n", p->nameCity, p->sumPersion);
        p = p->next;
    }
    return;
}

// 起步价 & 路程if(taxi)
float fareCal(int distance)
{
    if (distance <= 1)
    {
        return FLAG_FALL_PRICE * 1.0;
    }
    return (FLAG_FALL_PRICE + (distance - 1) * PRICE);
}

bool modify(Mgraph g)
{
    FILE *pFile;
    pFile = fopen("Text.txt", "w");
    if (pFile)
    {
        scanf("%d %d", &g.n, &g.e);
        fprintf(pFile, "%d %d\n", g.n, g.e);
        int v0, vEnd, w;
        info scanfInfo;
        for (int i = 0; i < g.n; i++)
        {
            scanf("%s %d", scanfInfo.nameCity, &scanfInfo.sumPersion);
            fprintf(pFile, "%s %d\n", scanfInfo.nameCity, scanfInfo.sumPersion);
        }
        for (int i = 0; i < g.e; i++)
        {
            scanf("%d %d %d", &v0, &vEnd, &w);
            fprintf(pFile, "%d %d %d\n", v0, vEnd, w);
        }
        fclose(pFile);
        return true;
    }
    return false;
}