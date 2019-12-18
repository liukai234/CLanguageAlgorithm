/**
 * @description: dev版本
 * @file: dev.c
 * @author: LiuKai
 * @ver: 1.0 2019/12/16
 * @lastchange: LiuKai
 */
#include "myhead.h"
#define MAX_FILE_NAME 100
#define MENU_SEL 2
char menuSel[MENU_SEL][MAX_FILE_NAME] = {"help", "exit"};

// 前向声明[后期会转移至myhead.h文件中]
void menuPrint();

/**
 * @description: 链表结构体
 * @author：Liukai
 * @ver:1.0 2019/12/18
 * @lastchange:liukai
 */
typedef struct linkNode0
{
    int data;
    struct linkNode0 *next;
} linkNode;

/**
 * @description: main
 * @author: LiuKai
 * @param: int args, char *argv[]
 * @return: 0
 * @ver: 1.0 2019/12/16
 * @lastchange: LiuKai
 */
int main(int args, char *argv[])
{
    char path[MAX_FILE_NAME];
    char strSel[MAX_FILE_NAME];
    int indexSel;
    bool exitFlag = false;
    _getcwd(path, MAX_FILE_NAME);
    printf("_getcwd: %s\n", path);
    printf("input \"help\" for more.");
    while (true)
    {
        scanf("%s", strSel);
        for(indexSel = 0; indexSel < MENU_SEL; indexSel++){
            if(!strcmp(strSel, menuSel[indexSel])){
                break;
            }
        }
        switch (indexSel){
            case 0:
                menuPrint();
                break;
            case 1:
                exitFlag = true;
                break;

            defaule:
                printf("Command error or does not exist\n");
        }
        if(exitFlag) {
            break;
        }
    }

    return 0;
}


/**
 * @description: menuPrint
 * @author: LiuKai
 * @param: null
 * @return: null
 * @ver: 1.0 2019/12/18
 * @lastchange: LiuKai
 */
void menuPrint(){
    printf("help\n"
    "exit\n");
}