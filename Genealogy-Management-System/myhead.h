/**
 * @description: 头文件
 * @file: myhead.h
 * @author: LiuKai
 * @ver: 4.0 2019/12/26
 **/
#ifndef __MYHEAD_H__
#define __MYHEAD_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <io.h>
#include <time.h>

#define MAX_FILE_NAME 100 // 文件名的长度
#define MAX_STRING 100
#define MENU_SEL 15         // 菜单长度宏
#define MAX_FILE_NUM 1000   // 最大文件数量
#define MAX_FIND_DEEPTH 100 // 最大查找深度
#define MAX_PERSON_NUM 1000 // 最大人数

#define MENU_PRINT 0
#define LS 1
#define MK 2
#define OPEN 3
#define CLOSE 4
#define DEL 5
#define PRINT_BRO_NODE 6
#define PRINT_SOMEONE 7
#define INPUT 8
#define PRINT_TREE_NODE 9
#define EXIT 10
#define CLEAR 11
#define MODIFY 12
#define GENERAT 13
#define FIND_RELATION 14

char menuSel[MENU_SEL][MAX_FILE_NAME] = {
    "help",
    "ls",
    "mk",
    "open",
    "close",
    "del",
    "printBrother", 
    "nameFind",
    "input",
    "printTree",
    "exit",
    "clear",
    "modify",
    "printGenerat",
    "findRelation",
}; // 菜单索引

/**
 * @description: printfColor
 * @author: liukai
 * @ver:1.0 2019/12/19
 */
/*设置输出前景色*/
#define PRINT_FONT_BLA printf("\033[30m"); //黑色
#define PRINT_FONT_RED printf("\033[31m"); //红色
#define PRINT_FONT_GRE printf("\033[32m"); //绿色
#define PRINT_FONT_YEL printf("\033[33m"); //黄色
#define PRINT_FONT_BLU printf("\033[34m"); //蓝色
#define PRINT_FONT_PUR printf("\033[35m"); //紫色
#define PRINT_FONT_CYA printf("\033[36m"); //青色
#define PRINT_FONT_WHI printf("\033[37m"); //白色
/*设置输出背景色*/
#define PRINT_BACK_BLA printf("\033[40m"); //黑色
#define PRINT_BACK_RED printf("\033[41m"); //红色
#define PRINT_BACK_GRE printf("\033[42m"); //绿色
#define PRINT_BACK_YEL printf("\033[43m"); //黄色
#define PRINT_BACK_BLU printf("\033[44m"); //蓝色
#define PRINT_BACK_PUR printf("\033[45m"); //紫色
#define PRINT_BACK_CYA printf("\033[46m"); //青色
#define PRINT_BACK_WHI printf("\033[47m"); //白色
/*输出属性设置*/
#define PRINT_ATTR_REC printf("\033[0m");   //重新设置属性到缺省设置
#define PRINT_ATTR_BOL printf("\033[1m");   //设置粗体
#define PRINT_ATTR_LIG printf("\033[2m");   //设置一半亮度(模拟彩色显示器的颜色)
#define PRINT_ATTR_LIN printf("\033[4m");   //设置下划线(模拟彩色显示器的颜色)
#define PRINT_ATTR_GLI printf("\033[5m");   //设置闪烁
#define PRINT_ATTR_REV printf("\033[7m");   //设置反向图象
#define PRINT_ATTR_THI printf("\033[22m");  //设置一般密度
#define PRINT_ATTR_ULIN printf("\033[24m"); //关闭下划线
#define PRINT_ATTR_UGLI printf("\033[25m"); //关闭闪烁
#define PRINT_ATTR_UREV printf("\033[27m"); //关闭反向图象

/**
 * @description: 树结构体
 * @author：Liukai
 * @ver:1.0 2019/12/20
 */
typedef struct info0
{
    char name[MAX_STRING];
    char father[MAX_STRING];
    int id;
    char sex[MAX_STRING];
    char birth[MAX_STRING];
    char spouse[MAX_STRING];
    // ！！！应该增加一项备注char note[MAX_STRING];
} info;

typedef struct chbrotree0
{
    info myinfo;
    struct chbrotree0 *myfather;
    struct chbrotree0 *firstchild;   //第一个后代
    struct chbrotree0 *rightsibling; //自己的兄弟
} chbrotree;

// 借助一个栈来输出指定前几代人 // 后几代人 // 兄弟节点
typedef struct linkQueue0
{
    chbrotree node;
    struct linkQueue0 *next;
} linkQueue;

typedef struct Relation0
{
    char relation;
    char name[MAX_STRING];
} Relation;
Relation rela[MAX_PERSON_NUM];

// 前向声明块
void menuPrint();
int ls(char *path);
void mk(char *inputFileName);
chbrotree *load(chbrotree *root, char *fileName);
bool save(chbrotree *root, char *fileName);
// chbrotree *idFindPerson(chbrotree *root, int id);
chbrotree *idFindWithLevelOrder(chbrotree *root, int id);
// chbrotree *nameFindPerson(chbrotree *root, char *name, int deepth);
chbrotree *nameFindWithLevelOrder(chbrotree *root, char *name, int deep);
chbrotree *modify(chbrotree *root, char *name);
chbrotree *addChildToFather(chbrotree *Father, chbrotree *Child);
chbrotree *treeInput(chbrotree *root, info myinfo, char *relation, char *relationName);
chbrotree *delAllTree(chbrotree *root);
chbrotree *mallocTreeNode(chbrotree *node, info myinfo);
void printTreeNode(chbrotree *root);
void generationPrintTreeNode(chbrotree *root, int generation);
void printCondition(chbrotree *root, char *name, char *direction, int generation);
chbrotree *conGeneration(chbrotree *firstPerson, chbrotree *secondPerson);
bool modifyRelation(chbrotree *nowGeneration, int *idx, chbrotree *p, chbrotree *secondPerson);
int difGeneration(chbrotree *root, chbrotree *firstPerson, chbrotree *secondPerson);
void transToAppellation(chbrotree *root, chbrotree *firstPerson, chbrotree *secondPerson);
chbrotree *printBrother(chbrotree *root, char *name);
#endif