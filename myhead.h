/**
 * @description: ͷ�ļ�
 * @file: myhead.h
 * @author: LiuKai
 * @ver: 2.0 2019/12/21
 * @lastaurhot:LiuKai
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

#define MAX_FILE_NAME 100 // �ļ����ĳ���
#define MAX_STRING 100
#define MENU_SEL 12       // �˵����Ⱥ�
#define MAX_FILE_NUM 1000 // ����ļ�����

#define MENU_PRINT 0
#define LS 1
#define MK 2
#define OPEN 3
#define CLOSE 4
#define DEL 5
#define ID_FIND_PERSON 6
#define NAME_FIND_PERSON 7
#define INPUT 8
#define PRINT_TREE_NODE 9
#define EXIT 10
#define CLEAR 11

char menuSel[MENU_SEL][MAX_FILE_NAME] = {"help",
                                         "ls",
                                         "mk",
                                         "open",
                                         "close",
                                         "del",
                                         "idFindPerson",
                                         "nameFindPerson",
                                         "treeInput",
                                         "printTreeNode",
                                         "exit",
                                         "clear"}; // �˵�����

/**
 * @description: printfColor
 * @author: liukai
 * @ver:1.0 2019/12/19
 * @lastchange: liukai
 */
/*�������ǰ��ɫ*/
#define PRINT_FONT_BLA printf("\033[30m"); //��ɫ
#define PRINT_FONT_RED printf("\033[31m"); //��ɫ
#define PRINT_FONT_GRE printf("\033[32m"); //��ɫ
#define PRINT_FONT_YEL printf("\033[33m"); //��ɫ
#define PRINT_FONT_BLU printf("\033[34m"); //��ɫ
#define PRINT_FONT_PUR printf("\033[35m"); //��ɫ
#define PRINT_FONT_CYA printf("\033[36m"); //��ɫ
#define PRINT_FONT_WHI printf("\033[37m"); //��ɫ
/*�����������ɫ*/
#define PRINT_BACK_BLA printf("\033[40m"); //��ɫ
#define PRINT_BACK_RED printf("\033[41m"); //��ɫ
#define PRINT_BACK_GRE printf("\033[42m"); //��ɫ
#define PRINT_BACK_YEL printf("\033[43m"); //��ɫ
#define PRINT_BACK_BLU printf("\033[44m"); //��ɫ
#define PRINT_BACK_PUR printf("\033[45m"); //��ɫ
#define PRINT_BACK_CYA printf("\033[46m"); //��ɫ
#define PRINT_BACK_WHI printf("\033[47m"); //��ɫ
/*�����������*/
#define PRINT_ATTR_REC printf("\033[0m");   //�����������Ե�ȱʡ����
#define PRINT_ATTR_BOL printf("\033[1m");   //���ô���
#define PRINT_ATTR_LIG printf("\033[2m");   //����һ������(ģ���ɫ��ʾ������ɫ)
#define PRINT_ATTR_LIN printf("\033[4m");   //�����»���(ģ���ɫ��ʾ������ɫ)
#define PRINT_ATTR_GLI printf("\033[5m");   //������˸
#define PRINT_ATTR_REV printf("\033[7m");   //���÷���ͼ��
#define PRINT_ATTR_THI printf("\033[22m");  //����һ���ܶ�
#define PRINT_ATTR_ULIN printf("\033[24m"); //�ر��»���
#define PRINT_ATTR_UGLI printf("\033[25m"); //�ر���˸
#define PRINT_ATTR_UREV printf("\033[27m"); //�رշ���ͼ��

/**
 * @description: ���ṹ��
 * @author��Liukai
 * @ver:1.0 2019/12/20
 * @lastchange:liukai
 */
typedef struct info0
{
    char name[MAX_STRING];
    char father[MAX_STRING];
    int id;
    char sex[MAX_STRING];
    char age[MAX_STRING];
    char spouse[MAX_STRING];
    // ������Ӧ������һ�עchar note[MAX_STRING];
} info;

typedef struct chbrotree0
{
    info myinfo;
    struct chbrotree0 *firstchild, *rightsibling;
} chbrotree;

// ����һ��ջ�����ָ��ǰ������ // �󼸴��� // �ֵܽڵ�
typedef struct linkStack0
{
    chbrotree node;
    struct linkStack0 *next;
} linkStack;

// ǰ��������
void menuPrint();
int ls(char *path);
void mk(char *inputFileName);
chbrotree *load(chbrotree *root, char *fileName);
bool save(chbrotree *root, char *fileName);
chbrotree *idFindPerson(chbrotree *root, int id);
chbrotree *nameFindPerson(chbrotree *root, char *name);
chbrotree *treeInput(chbrotree *root, info myinfo, char *relation, char *relationName);
chbrotree *mallocTreeNode(chbrotree *node, info myinfo);
chbrotree *printTreeNode(chbrotree *root);
chbrotree namePrintTreeNode(chbrotree root, char name, int generation, char *param);
chbrotree *delAllTree(chbrotree *root);
#endif