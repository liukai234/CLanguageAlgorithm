/**
 * @description: dev版本
 * @file: dev.c
 * @author: LiuKai
 * @ver: 1.0 2019/12/16
 * @lastchange: LiuKai
 */
#include "myhead.h"
#include "exception.h"

/**
 * @description: main
 * @author: LiuKai
 * @param: int args, char *argv[]
 * @return: 0
 * @ver: 1.0 2019/12/16
 * @lastchange: LiuKai
 */
char searchFileName[MAX_FILE_NUM][MAX_FILE_NAME];
int ID = 0; // 全局变量ID为每一个人的唯一身份
int colorCount = 0;
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
    char inputFileName[MAX_FILE_NAME] = '\0';  // 输入文件名
    char outputFileName[MAX_FILE_NAME] = '\0'; // 输出文件名
    bool fileExist = false;                    // 文件是否存在标志， 文件存在fileExist为true
    int indexSel;                              // 菜单选择下标
    bool exitFlag = false;                     // 退出标志，为真表示退出
    chbrotree *mychbrotree;
    _getcwd(path, MAX_FILE_NAME); // 获取当前工作路径
    printf("_getcwd: %s\n", path);
    printf("Input \"help\" for more.\n");
    while (true)
    {
        // 检索命令键的键值
        scanf("%s", strSel);
        for (indexSel = 0; indexSel < MENU_SEL; indexSel++)
        {
            if (!strcmp(strSel, menuSel[indexSel]))
            {
                break;
            }
        }
        switch (indexSel)
        {
        case 0:
            menuPrint();
            break;
        case 1:
            info myinfo;
            char relation[MAX_STRING];
            char relationName[MAX_STRING];
            scanf("%s%s", relation, relationName);
            scanf("%s%s%s%s%s", myinfo.name, myinfo.id, myinfo.sex, myinfo.age, myinfo.spouse);
            treeInput(mychbrotree, myinfo, relation, relationName);
            break;
        case 2:
            exitFlag = true;
            break;

        defaule:
            printf("Command error or does not exist\n");
        }
        if (exitFlag)
        {
            break;
        }
    }
    system("pause");
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
void menuPrint()
{
    printf("help           format: help\n"
           "treeInput      format: input [name][id][sex][age][spouse]"
           "exit           format: exit\n");
}

/**
 * @description: 在path目录下查找.dat文件
 * @author： liukai
 * @param {type: char*} path
 * @return: void
 * @ver: 1.0 2019/12/19
 * @lastchange: liukai
 */
int ls(char *path)
{
    long hFile = 0;
    struct _finddata_t fileInfo;

    int count = 0;
    // \\* 代表要遍历所有的类型, \\*.dat表示遍历dat类型文件
    if ((hFile = _findfirst(path, &fileInfo)) == -1)
    {
        // printf("暂无数据文件");
        return 0;
    }
    do
    {
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
void mk(char *inputFileName)
{
    FILE *pFile;

    pFile = fopen(inputFileName, "wb"); // 考虑使用txt文件
    if (!pFile)
    {
        fprintf(stderr, "%s\n", strerror(errno));
    }
    fclose(pFile);
}
// void del();
/**
 * @description: findPerson
 * @author: LiuKai
 * @param: chbrotree *root, int id
 * @return: chbrotree *root
 * @ver: 1.0 2019/12/20
 * @lastchange: LiuKai
 */
chbrotree *idFindPerson(chbrotree *root, int id)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->myinfo.id == id)
    {
        return root;
    }
    idFindPerson(root->firstchild, id);
    idFindPerson(root->rightsibling, id);
}

/**
 * @description: findPerson
 * @author: LiuKai
 * @param: chbrotree *root, char *name
 * @return: chbrotree *root
 * @ver: 1.0 2019/12/20
 * @lastchange: LiuKai
 */
chbrotree *nameFindPerson(chbrotree *root, char *name)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (!strcmp(root->myinfo.name, name))
    {
        return root;
    }
    nameFindPerson(root->firstchild, name);
    nameFindPerson(root->rightsibling, name);
}

/**
 * @description: treeInput
 * @author: LiuKai
 * @param: chbrotree *root, info myinfo, char *relation, char *relationName
 * @return: chbrotree *root
 * @ver: 1.0 2019/12/20
 * @lastchange: LiuKai
 */
chbrotree *treeInput(chbrotree *root, info myinfo, char *relation, char *relationName)
{
    chbrotree *node;
    node = mallocTreeNode(node, myinfo);

    if (root == NULL)
    {
        root = node;
        return root;
    }
    // 输入节点与该节点的父亲 // 母亲
    chbrotree *pre = findPerson(root, relationName);
    if (pre == NULL)
    {
        PRINT_FONT_RED
        printf("%s%s is not exist\n");
        printf("Modification cannot be saved\n");
        return root;
    }
    chbrotree *next = pre->firstchild;
    pre->firstchild = node;
    node->rightsibling = next;
    return root;
}

/**
 * @description: mallocTreeNode
 * @author: LiuKai
 * @param: chbrotree *root, info myinfo
 * @return: chbrotree *node
 * @ver: 1.0 2019/12/20
 * @lastchange: LiuKai
 */
chbrotree *mallocTreeNode(chbrotree *node, info myinfo)
{

    node = (chbrotree *)malloc(sizeof(chbrotree));
    node->myinfo = myinfo;
    node->firstchild = node->rightsibling = NULL;
    node->myinfo.id = ID;
    ID++;
    return node;
}

chbrotree printTreeNode(chbrotree root)
{
    // 对父节点标红
    // linkStack mystack;
    /* if (colorCount == 0)
    {
        PRINT_FONT_RED
    }
    colorCount ++; */
    printf("%s %d %s %s %s", root.myinfo.name, root.myinfo.id, root.myinfo.sex, root.myinfo.age, root.myinfo.spouse);
    printTreeNode(*root.rightsibling);
    // PRINT_FONT_RED
    printTreeNode(*root.firstchild);
}

// 参数param表示输出父系// 母系 // 兄弟
chbrotree namePrintTreeNode(chbrotree root, char name, int generation, char *param)
{
    linkStack mystack;
    // 用栈暂时保存代数信息
}