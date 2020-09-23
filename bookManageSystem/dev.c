#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_STRING 100
#define MAX_INDEX 4
#define MAX_MENU 6
typedef struct certiNode
{
    char id[MAX_STRING];
    char name[MAX_STRING];
    char depart[MAX_STRING];
    char class0[MAX_STRING];
    struct certiNode *next; // 指针域
    struct certiNode *link; // 排序空间
} cert;
// STR索引
char strIndex[4][MAX_STRING] = {"id", "name", "depart", "class0"};
// menu索引
char selIndex[MAX_MENU][MAX_STRING] = {"help", "insert", "sortlink", "build", "retr", "exit"};
struct AvlNode
{
    cert mycert;
    struct AvlNode *left;
    struct AvlNode *right;
    int frequency;
    int heigh;
};
typedef struct AvlNode *NodePtr;
typedef struct AvlNode *AvlTree;
typedef struct AvlNode Node;
typedef struct ReturnSearchAvlTree
{
    bool wExist;
    int frequency;
} rsvt;
void help();
cert *init();
cert *insert(cert *head);
void prints(cert *head, bool selct); // selct为真时为原链表
int Heigh(NodePtr node);
NodePtr MallocAvlNode(NodePtr node, cert mycert);
AvlTree SingleRotateLeft(AvlTree t);
AvlTree SingleRotateRight(AvlTree t);
AvlTree DoubleRotateLeft(AvlTree t);
AvlTree DoubleRotateRight(AvlTree t);
AvlTree Insert(cert mycert, AvlTree t);
// void PrintAvlTreeInorder(NodePtr node);
int rideStrcmp(char *str1, char *str2);
void sortLink(cert *head, char *key);
rsvt SearchAvlTree(char *depart, NodePtr node);

int sumCert = 0;
rsvt myrsvt;

int main()
{
    bool wExit = false;
    printf("input \"help\" for help\n");
    // 链表结构
    cert *mycert;
    mycert = init();
    cert *p;
    //int sum;
    //printf("sumInput:");
    //scanf("%d", &sum);
    //for (int i = 0; i < sum; i++)
    //{
    //}
    char key[MAX_STRING];
    char input[MAX_STRING];
    char depart[MAX_STRING];
    while (true)
    {
        int sel = 0;
        scanf("%s", input);
        for (sel = 0; sel < MAX_MENU; sel++)
        {
            if (!strcmp(selIndex[sel], input))
            {
                break;
            }
        }
        switch (sel)
        {
        // menu
        case 0:
            help();
            break;
        case 1:
            mycert = insert(mycert);
            printf("Current linklist is:\n");
            prints(mycert, true);
            break;
        case 2:
            // char key[MAX_STRING];
            scanf("%s", key);
            sortLink(mycert, key);
            prints(mycert, false);
            break;
        case 3:
            // 二叉平衡排序树AVL
            p = mycert;
            AvlTree t;
            t = NULL;
            while (p->next)
            {
                p = p->next;
                t = Insert(*p, t);
            }
            break;
        // 检索
        case 4:
            // char depart[MAX_STRING];
            scanf("%s", depart);
            myrsvt.wExist = false;
            myrsvt.frequency = 0;
            rsvt myrsvt = SearchAvlTree(depart, t);
            if (myrsvt.wExist)
            {
                printf("Depart %s is exist\n", depart);
                p = mycert->link;
                while (myrsvt.frequency)
                {
                    if (!rideStrcmp(p->depart, depart))
                    {
                        printf("ID: %s Name: %s Depart: %s Class: %s\n", p->id, p->name, p->depart, p->class0);
                        myrsvt.frequency--;
                    }
                    p = p->link;
                }
                myrsvt.wExist = false;
                myrsvt.frequency = 0;
            }
            else {
                printf("Depart %s is not exist\n", depart);
            }
            break;
        case 5:
            wExit = true;
            break;
        default:
            printf("Command does not exist\n");
            break;
        }
        printf("Execution completed\n");
        if (wExit)
        {
            break;
        }
    }
    return 0;
}

void help()
{
    printf("help                        format[help]\n"
           "insert                      format[insert <id name depart class>]\n"
           "sortlink                    format[sortlink]\n"
           "build AVL                   format[build]\n"
           "retrieval                   format[retr <key>]\n"
           "exit                        format[exit]\n");
}

/**
 * @description: 初始化链表
 * @param {type} void
 * @return: void
 */
cert *init()
{
    cert *head;
    head = (cert *)malloc(sizeof(cert));
    head->next = NULL;
    head->link = NULL;
    return head;
}

/**
 * @description:带头结点 尾插
 * @param {type: cert*} head
 * @return:head
 */
cert *insert(cert *head)
{
    cert *p, *pre, *Lastpos;
    pre = head;
    p = (cert *)malloc(sizeof(cert));

    printf("ID Name Depart Class:");
    scanf("%s %s %s %s", p->id, p->name, p->depart, p->class0);

    while (pre->next)
    {
        // 禁止学号重复 sumSert++;
        if (!strcmp(pre->id, p->id))
        {
            return NULL;
        }
        else
        {
            sumCert++;
        }
        pre = pre->next;
    }
    if (!pre->next)
    {
        sumCert++;
    }
    p->next = pre->next;
    pre->next = p;
    return head;
}

/**
 * @description: 结点连续输出
 * @param {type: node_stu*} head
 * @return:void
 */
void prints(cert *head, bool selct)
{
    cert *p;
    p = head;
    if (selct)
        p = p->next;
    else
        p = p->link;
    if (!p)
    {
        printf("Empty\n");
        return;
    }
    while (p)
    {
        printf("ID: %s Name: %s Depart: %s Class: %s\n", p->id, p->name, p->depart, p->class0);
        if (selct)
            p = p->next;
        else
            p = p->link;
    }
}

/* // 成员清零
void Clear(unsigned char *pta, int size)
{
    while (size > 0)
    {
        *pta++ = 0;
        size--;
    }
} */

int Heigh(NodePtr node)
{
    if (!node)
        return 0;
    int left = Heigh(node->left) + 1;
    int right = Heigh(node->right) + 1;
    return left > right ? left : right;
}

int MAX(int a, int b)
{
    return a > b ? a : b;
}

NodePtr MallocAvlNode(NodePtr node, cert mycert)
{
    node = (NodePtr)malloc(sizeof(Node));
    node->mycert = mycert;
    node->left = node->right = NULL;
    node->frequency = 0;
    node->heigh = 0;
    return node;
}

// 左单
AvlTree SingleRotateLeft(AvlTree t)
{
    NodePtr tmp = t->left;
    t->left = tmp->right;
    tmp->right = t;
    t->heigh = MAX(Heigh(t->left), Heigh(t->right)) + 1; //更新子树节点深度
    tmp->heigh = MAX(Heigh(tmp->left), Heigh(tmp->right)) + 1;
    return tmp;
}

// 右单
AvlTree SingleRotateRight(AvlTree t)
{
    NodePtr tmp = t->right;
    t->right = tmp->left;
    tmp->left = t;
    t->heigh = MAX(Heigh(t->left), Heigh(t->right)) + 1;
    tmp->heigh = MAX(Heigh(tmp->left), Heigh(tmp->right)) + 1;
    return tmp;
}

//先右再左
AvlTree DoubleRotateLeft(AvlTree t)
{
    t->left = SingleRotateRight(t->left);
    t = SingleRotateLeft(t);
    return t;
}

//先左再右
AvlTree DoubleRotateRight(AvlTree t)
{
    t->right = SingleRotateLeft(t->right);
    t = SingleRotateRight(t);
    return t;
}

AvlTree Insert(cert mycert, AvlTree t)
{
    if (t == NULL)
    {
        t = MallocAvlNode(t, mycert); //节点插入位置
        if (t == NULL)
        {
            printf("malloc avl node failed\n");
            return t;
        }
    }
    else if (rideStrcmp(mycert.depart, t->mycert.depart) < 0)
    {
        t->left = Insert(mycert, t->left); //插入元素小于节点元素则插入左子树中
        if (Heigh(t->left) - Heigh(t->right) == 2)
        {
            if (rideStrcmp(mycert.depart, t->mycert.depart) < 0) //为第一种情况
            {
                t = SingleRotateLeft(t);
            }
            else
            {
                t = DoubleRotateLeft(t); //第三种情况
            }
        }
    }
    else if (rideStrcmp(mycert.depart, t->mycert.depart) > 0) //若是大于则插入右子树
    {
        t->right = Insert(mycert, t->right);
        if (Heigh(t->right) - Heigh(t->left) >= 2)
        {
            if (rideStrcmp(mycert.depart, t->mycert.depart) > 0) //第二种情况
            {
                t = SingleRotateRight(t);
            }
            else
            {
                t = DoubleRotateRight(t); //第四种情况
            }
        }
    }
    else //若是相等，更新节点结构中frequency，进行加1
    {
        ++t->frequency;
    }
    t->heigh = MAX(Heigh(t->left), Heigh(t->right)) + 1; //更新节点的heigh成员
    return t;
}

/**
 * @description: 重写strcmp函数,使可以优先判断模拟数组的长度,防止数字2排在10之后
 * @param {type :char*} str1
 * @param {type :char*} str2
 * @return: re
 */
int rideStrcmp(char *str1, char *str2)
{
    int re;
    int lenstr1 = 0;
    int lenstr2 = 0;
    int i;
    for (i = 0; str1[i] != 0; i++)
    {
        lenstr1++;
    }
    for (i = 0; str2[i] != 0; i++)
    {
        lenstr2++;
    }
    if (lenstr1 < lenstr2)
    {
        re = -1;
    }
    else if (lenstr1 > lenstr2)
    {
        re = 1;
    }
    else
    {
        re = strcmp(str1, str2);
    }

    return re;
}

// 链表有序
void sortLink(cert *head, char *key)
{
    if (!head->next)
    {
        printf("Empty\n");
        return;
    }
    int index = 0;
    for (; index < MAX_INDEX; index++)
    {
        if (!strcmp(key, strIndex[index]))
        {
            break;
        }
    }
    cert *p, *q;
    head->link = head->next;
    head->link->link = NULL; // 终止位置
    for (cert *ahead = head->next->next; ahead != NULL; ahead = ahead->next)
    {
        q = head;
        p = head->link;
        char aheadStr[MAX_STRING];
        char pStr[MAX_STRING];
        switch (index)
        {
        case 0:
            strcpy(aheadStr, ahead->id);
            strcpy(pStr, p->id);
            break;
        case 1:
            strcpy(aheadStr, ahead->name);
            strcpy(pStr, p->name);
            break;
        case 2:
            strcpy(aheadStr, ahead->depart);
            strcpy(pStr, p->depart);
            break;
        case 3:
            strcpy(aheadStr, ahead->class0);
            strcpy(pStr, p->class0);
            break;
        default:
            printf("linkSort key ERROR\n");
            return;
        }
        // 寻找插入位置
        while (p != NULL && rideStrcmp(aheadStr, pStr) >= 0)
        {
            q = p;
            p = p->link;
            if (p != NULL)
            {
                switch (index)
                {
                case 0:
                    strcpy(pStr, p->id);
                    break;
                case 1:
                    strcpy(pStr, p->name);
                    break;
                case 2:
                    strcpy(pStr, p->depart);
                    break;
                case 3:
                    strcpy(pStr, p->class0);
                    break;
                default:
                    printf("linkSort key ERROR\n");
                    return;
                }
            }
        }
        ahead->link = p;
        q->link = ahead;
    }
    // 保留next域
    /* for (cert *ahead = head->next; ahead != NULL; ahead = ahead->next)
    {

    } */
}

rsvt SearchAvlTree(char *depart, NodePtr node)
{
    if (node)
    {
        SearchAvlTree(depart, node->left);
        if (!rideStrcmp(node->mycert.depart, depart))
        {
            myrsvt.wExist = true;
            myrsvt.frequency = node->frequency;
            return myrsvt;
        }
        SearchAvlTree(depart, node->right);
    }
    return myrsvt;
}