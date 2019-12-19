/**
 * @description: dev版本
 * @file: dev.c
 * @author: LiuKai
 * @ver: 1.0 2019/12/16
 * @lastchange: LiuKai
 */
#include "myhead.h"
#include "exception.h"
#define MAX_FILE_NAME 100 // 文件名的长度
#define MAX_STRING 100
#define MENU_SEL 2 // 菜单长度宏
#define MAX_FILE_NUM 1000 // 最大文件数量
char menuSel[MENU_SEL][MAX_FILE_NAME] = {"help", "exit"}; // 菜单索引

// 前向声明[后期会转移至myhead.h文件中]
void menuPrint();
// 将dir更名为ls
int ls(char* path);
// mkdir更名为mk
void mk(char* inputFileName);
// void del();


/**
 * @description: 链表结构体
 * @author：Liukai
 * @ver:1.0 2019/12/18
 * @lastchange:liukai
 */
/* typedef struct linkNode0
{
    int data;
    struct linkNode0 *next;

} linkNode; */


typedef struct margh0{
    char id[MAX_STRING];
    char name[MAX_STRING];
    bool sex; // 性别
    char age[MAX_STRING];
}margh;

/**
 * @description: main
 * @author: LiuKai
 * @param: int args, char *argv[]
 * @return: 0
 * @ver: 1.0 2019/12/16
 * @lastchange: LiuKai
 */
char searchFileName[MAX_FILE_NUM][MAX_FILE_NAME];
int main(int args, char *argv[])
{
    // colorTest
    PRINT_FONT_BLA 
    printf("hello world!\n");
    PRINT_FONT_BLU
    printf("hello world!\n");
    PRINT_FONT_RED 
    printf("hello world!\n");
    PRINT_FONT_YEL 
    printf("hello world!\n");
    PRINT_FONT_GRE 
    printf("hello world!\n");
    PRINT_FONT_WHI 
    printf("hello world!\n");
    PRINT_FONT_PUR 
    printf("hello world!\n");
    PRINT_ATTR_REV
    printf("hello world!\n");
    PRINT_ATTR_REC

    char path[MAX_FILE_NAME];
    char strSel[MAX_FILE_NAME];
    char inputFileName[MAX_FILE_NAME] = '\0'; // 输入文件名
    char outputFileName[MAX_FILE_NAME] = '\0'; // 输出文件名
    bool fileExist = false; // 文件是否存在标志， 文件存在fileExist为true
    int indexSel; // 菜单选择下标
    bool exitFlag = false; // 退出标志，为真表示退出
    _getcwd(path, MAX_FILE_NAME); // 获取当前工作路径
    printf("_getcwd: %s\n", path);
    printf("Input \"help\" for more.\n");
    while (true)
    {
        // 检索命令键的键值
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
 * @param: void
 * @return: void
 * @ver: 1.0 2019/12/18
 * @lastchange: LiuKai
 */
void menuPrint(){
    printf("help    format: help\n"
           "exit    format: exit\n");
}


/**
 * @description: 在path目录下查找.dat文件
 * @author： liukai
 * @param {type: char*} path
 * @return: void
 * @ver: 1.0 2019/12/19
 * @lastchange: liukai
 */
int ls(char* path) {
    long hFile = 0;
    struct _finddata_t fileInfo;

    int count = 0;
    // \\* 代表要遍历所有的类型, \\*.dat表示遍历dat类型文件
    if ((hFile = _findfirst(path, &fileInfo)) == -1) {
        // printf("暂无数据文件");
        return 0;
    }
    do {
        // printf("%s\n", fileInfo.name);
        strcpy(searchFileName[count], fileInfo.name);
        // (fileInfo.attrib & _A_SUBDIR ? "[folder]" : "[file]")
        // 判断文件的属性是文件夹还是文件
        count++;
    } while (_findnext(hFile, &fileInfo) == 0);
    _findclose(hFile);
    return count;
}


/**
 * @description: 建立新数据文件
 * @param {type} 
 * @return: 
 */
void mk(char* inputFileName) {
    FILE* pFile;

    pFile = fopen(inputFileName, "wb"); // 考虑使用txt文件
    if (!pFile) {
        fprintf(stderr, "%s\n", strerror(errno));
    }
    fclose(pFile);
}

