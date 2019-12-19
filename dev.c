/**
 * @description: dev�汾
 * @file: dev.c
 * @author: LiuKai
 * @ver: 1.0 2019/12/16
 * @lastchange: LiuKai
 */
#include "myhead.h"
#define MAX_FILE_NAME 100 // ����ļ�����
#define MENU_SEL 2 // �˵����Ⱥ�
#define MAX_FILE_NUM 1000 // ����ļ�����
char menuSel[MENU_SEL][MAX_FILE_NAME] = {"help", "exit"}; // �˵�����

// ǰ������[���ڻ�ת����myhead.h�ļ���]
void menuPrint();
int dir(char* path);
void madir(char* inputFileName);
// void del();
/**
 * @description: ����ṹ��
 * @author��Liukai
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
char searchFileName[MAX_FILE_NUM][MAX_FILE_NAME];
int main(int args, char *argv[])
{
    char path[MAX_FILE_NAME];
    char strSel[MAX_FILE_NAME];
    char inputFileName[MAX_FILE_NAME] = '\0'; // �����ļ���
    char outputFileName[MAX_FILE_NAME] = '\0'; // ����ļ���
    bool fileExist = false; // �ļ��Ƿ���ڱ�־�� �ļ�����fileExistΪtrue
    int indexSel; // �˵�ѡ���±�
    bool exitFlag = false; // �˳���־��Ϊ���ʾ�˳�
    _getcwd(path, MAX_FILE_NAME); // ��ȡ��ǰ����·��
    printf("_getcwd: %s\n", path);
    printf("Input \"help\" for more.\n");
    while (true)
    {
        // ����������ļ�ֵ
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
 * @description: ��pathĿ¼�²���.dat�ļ�
 * author�� liukai
 * @param {type: char*} path
 * @return: void
 * @ver: 1.0 2019/12/19
 * @lastchange: liukai
 */
int dir(char* path) {
    long hFile = 0;
    struct _finddata_t fileInfo;

    int count = 0;
    // \\* ����Ҫ�������е�����, \\*.dat��ʾ����dat�����ļ�
    if ((hFile = _findfirst(path, &fileInfo)) == -1) {
        // printf("���������ļ�");
        return 0;
    }
    do {
        // printf("%s\n", fileInfo.name);
        strcpy(searchFileName[count], fileInfo.name);
        // (fileInfo.attrib & _A_SUBDIR ? "[folder]" : "[file]")
        // �ж��ļ����������ļ��л����ļ�
        count++;
    } while (_findnext(hFile, &fileInfo) == 0);
    _findclose(hFile);
    return count;
}


/**
 * @description: �����������ļ�
 * @param {type} 
 * @return: 
 */
void madir(char* inputFileName) {
    FILE* pFile;

    pFile = fopen(inputFileName, "wb"); // ����ʹ��txt�ļ�
    if (!pFile) {
        fprintf(stderr, "%s\n", strerror(errno));
    }
    fclose(pFile);
}
