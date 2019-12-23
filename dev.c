/**
 * @description: dev版本
 * @file: dev.c
 * @author: LiuKai
 * @ver: 2.0 2019/12/21
 */
#include "myhead.h"
#include "exception.h"

/**
 * @description: main
 * @author: LiuKai
 * @param: int args, char *argv[]
 * @return: 0
 * @ver: 2.0 2019/12/21
 */
char searchFileName[MAX_FILE_NUM][MAX_FILE_NAME];
int ID = 0; // 全局变量ID为每一个人的唯一身份
int colorCount = 0;
int main(int args, char *argv[])
{
    // colorTest
    /* PRINT_FONT_BLA
    printf("Hello world.\n");
    PRINT_FONT_BLU
    printf("Hello world.\n");
    PRINT_FONT_RED
    printf("Hello world.\n");
    PRINT_FONT_YEL
    printf("Hello world.\n");
    PRINT_FONT_GRE
    printf("Hello world.\n");
    PRINT_FONT_WHI
    printf("Hello world.\n");
    PRINT_FONT_PUR
    printf("Hello world.\n");
    PRINT_ATTR_REV
    printf("Hello world.\n");
    PRINT_ATTR_REC */

    char path[MAX_FILE_NAME];
    char strSel[MAX_FILE_NAME];
    char inputFileName[MAX_FILE_NAME] = "\0";  // 输入文件名
    char outputFileName[MAX_FILE_NAME] = "\0"; // 输出文件名
    bool fileExist = false;                    // 文件是否存在标志， 文件存在fileExist为true
    int indexSel;                              // 菜单选择下标
    bool exitFlag = false;                     // 退出标志，为真表示退出
    chbrotree *mychbrotree = NULL;

    /**
     * @description: 校准countFile and path
     */
    _getcwd(path, MAX_FILE_NAME); // 获取当前工作路径
    printf("_getcwd: %s\n", path);
    strcat(path, "\\*.dat");
    int countFile = ls(path);

    char fileName[MAX_STRING];
    char name[MAX_STRING];
    info myinfo;
    char relation[MAX_STRING];
    char relationName[MAX_STRING];

    bool fileOpenFlag = false;

    printf("Input \"help\" for more.\n");
    while (true)
    {
        PRINT_FONT_GRE
        // if (mychbrotree)
        if (fileOpenFlag)
        {
            printf("dev\\%s> ", inputFileName);
        }
        else
        {
            printf("dev> ");
        }
        PRINT_ATTR_REC

        // 检索命令键的键值
        scanf("%s", strSel);
        // add del and clear
        for (indexSel = 0; indexSel < MENU_SEL; indexSel++)
        {
            if (!strcmp(strSel, menuSel[indexSel]))
            {
                break;
            }
        }
        switch (indexSel)
        {
        case MENU_PRINT:
            menuPrint();
            break;
        case LS:
            // ls
            printf("There are %d files in total\n", countFile);
            for (int i = 0; i < countFile; i++)
            {
                printf("%s\n", searchFileName[i]);
            }
            break;
        case MK:
            // mk
            scanf("%s", fileName);
            mk(fileName);
            countFile = ls(path); // 校准countFile and searchFileName
            break;
        case OPEN:
            // open // load
            scanf("%s", inputFileName);
            for (int i = 0; i < countFile; i++)
            {
                if (!strcmp(inputFileName, searchFileName[i]))
                {
                    fileExist = true;
                    if (!strcmp(outputFileName, inputFileName))
                    {
                        printf("file already open\n");
                        break;
                    }
                    // if (mychbrotree != NULL)
                    if (fileOpenFlag)
                    {
                        printf("Saving previous data file to %s...\n", outputFileName);
                        save(mychbrotree, outputFileName);
                        mychbrotree = NULL;
                        printf("Save finished\n");
                    }
                    else
                    {
                        strcpy(outputFileName, inputFileName);
                        printf("Initialize memory, load data to memory\n");
                        mychbrotree = load(mychbrotree, inputFileName);
                        fileOpenFlag = true;
                        printf("Load finished\n");
                    }
                    break;
                }
            }
            if (!fileExist)
            {
                printf("File does not exist\n");
            }
            fileExist = false;
            break;
        case CLOSE:
            // close
            if (fileOpenFlag)
            {
                save(mychbrotree, outputFileName);
                printf("Save finished\n");
                // 没有释放内存
                mychbrotree = NULL;
                *outputFileName = '\0';
                fileOpenFlag = false;
            }
            else
            {
                PRINT_FONT_RED
                printf("No file is opening\n");
                PRINT_ATTR_REC
            }
            break;
        case DEL:
            // del
            scanf("%s", inputFileName);
            if (!remove(inputFileName))
            {
                printf("Delete successful\n");
                countFile = ls(path);
            }
            else
            {
                PRINT_FONT_RED
                fprintf(stderr, "%s\n", strerror(errno));
                PRINT_ATTR_REC
            }
            // 如果删除的文件和当前打开的文件是同一个文件则释放mychbrotree
            if (!strcmp(inputFileName, outputFileName))
            {
                mychbrotree = delAllTree(mychbrotree);
                fileOpenFlag = false;
            }

            break;
        case CLEAR:
            // clear清空正在打开的数据文件
            PRINT_FONT_RED
            printf("Empty this file?\n");
            PRINT_ATTR_REC
            printf("continue?(input 'y' or 'Y' to continue)\n");
            char consel[1];
            scanf("%s", consel);
            if (consel[0] == 'Y' || consel[0] == 'y')
            {
                mychbrotree = delAllTree(mychbrotree);
                save(mychbrotree, inputFileName);
                printf("clear successful\n");
                mychbrotree = load(mychbrotree, inputFileName);
                printf("Reload finished\n");
            }
            else
            {
                printf("operation aborted\n");
            }
            break;
        case ID_FIND_PERSON:
            // do idFindPerson
            break;
        case NAME_FIND_PERSON:
            scanf("%s", name);
            nameFindPerson(mychbrotree, name);
            break;
        case INPUT:
            // input
            scanf("%s%s", relation, relationName);
            scanf("%s%s%s%s", myinfo.name, myinfo.sex, myinfo.age, myinfo.spouse);
            mychbrotree = treeInput(mychbrotree, myinfo, relation, relationName);
            break;
        case PRINT_TREE_NODE:
            printTreeNode(mychbrotree);
            break;
        case EXIT:
            exitFlag = true;
            // 保存文件
            if (mychbrotree != NULL)
            {
                save(mychbrotree, outputFileName);
                printf("Save finished\n");
            }
            // 没有释放内存
            mychbrotree = delAllTree(mychbrotree);
            mychbrotree = NULL;
            fileOpenFlag = false;
            break;
        default:
            printf("'%s' is not an internal command\n", strSel);
            break;
        }
        // printf("Execution completed\n");
        if (exitFlag)
        {
            break;
        }
    }
    // system("pause");
    return 0;
}

/**
 * @description: menuPrint
 * @author: LiuKai
 * @param: void
 * @return: void
 * @ver: 2.0 2019/12/21
 */
void menuPrint()
{
    printf("help             format: help\n"
           "ls               format: ls\n"
           "mk               format: mk [*.dat]\n"
           "open             format: open [*.dat]\n"
           "close and save   format: close"
           "load             format: laod [*.dat]\n"
           "save             format: save [*.dat]\n"
           "idFindPerson     format: idFindPerson [id]\n"
           "nameFindPerson   format: nameFindPerson [name]\n"
           "treeInput        format: input [relation][relationName][name][id][sex][age][spouse]"
           "printTreeNode    format: printTreeNode\n"
           "exit             format: exit\n");
}

/**
 * @description: 在path目录下查找.dat文件
 * @author： liukai
 * @param {type: char*} path
 * @return: void
 * @ver: 2.0 2019/12/21
 */
int ls(char *path)
{
    long hFile = 0;
    struct _finddata_t fileInfo;
    int count = 0;
    if ((hFile = _findfirst(path, &fileInfo)) == -1)
    {
        return 0;
    }
    do
    {
        strcpy(searchFileName[count], fileInfo.name);
        // (fileInfo.attrib & _A_SUBDIR ? "[folder]" : "[file]")
        // 判断文件的属性是文件夹还是文件
        count++;
    } while (_findnext(hFile, &fileInfo) == 0);
    _findclose(hFile);
    return count;
}

/**
 * @description: mk
 * @author： liukai
 * @param {type: char*} path
 * @return: void
 * @ver: 2.0 2019/12/21
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
 * @description: load
 * @author： liukai
 * @param {type: char*} path
 * @return: void
 * @ver: 2.0 2019/12/21
 */
chbrotree *load(chbrotree *root, char *fileName)
{
    FILE *input;
    input = fopen(fileName, "rb");
    if (!input)
    {
        PRINT_FONT_RED
        fprintf(stderr, "%s\n", strerror(errno));
        PRINT_ATTR_REC
        return NULL;
    }
    chbrotree *p, *pre;
    p = (chbrotree *)malloc(sizeof(chbrotree));
    while (fread(p, sizeof(struct chbrotree0), 1, input))
    {
        root = treeInput(root, p->myinfo, "father", p->myinfo.father);
    }
    fclose(input);
    return root;
}

/**
 * @description: save
 * @author： liukai
 * @param {type: char*} path
 * @return: void
 * @ver: 2.0 2019/12/21
 */
bool save(chbrotree *root, char *fileName)
{
    FILE *output;
    chbrotree *p, *pre;
    output = fopen(fileName, "wb");
    if (!output)
    {
        PRINT_FONT_RED
        fprintf(stderr, "%s\n", strerror(errno));
        return false;
    }
    pre = root;
    while (pre)
    {
        p = pre;
        while (p)
        {
            fwrite(p, sizeof(struct chbrotree0), 1, output);
            p = p->rightsibling;
        }
        pre = pre->firstchild;
    }
    fclose(output);
    return true;
}

/**
 * @description: findPerson
 * @author: LiuKai
 * @param: chbrotree *root, int id
 * @return: chbrotree *root
 * @ver: 1.0 2019/12/20
 */
chbrotree *idFindPerson(chbrotree *root, int id)
{
    chbrotree *p, *pre;
    pre = root;
    while (pre)
    {
        p = pre;
        while (p)
        {
            if (p->myinfo.id == id)
            {
                return p;
            }
            p = p->rightsibling;
        }
        pre = pre->firstchild;
    }
    return NULL;
}

/**
 * @description: findPerson
 * @author: LiuKai
 * @param: chbrotree *root, char *name
 * @return: chbrotree *root
 * @ver: 1.0 2019/12/20
 */
// set flag
chbrotree *nameFindPerson(chbrotree *root, char *name)
{
    /* if (root->rightsibling == NULL && root->firstchild == NULL)
    {
        return root;
    } */
    /* if (!strcmp(root->myinfo.name, name))
    {
        return root;
    }
    nameFindPerson(root->rightsibling, name);
    nameFindPerson(root->firstchild, name);
    return NULL; */
    //

    chbrotree *p, *pre;
    chbrotree *address[MAX_STRING];
    pre = root;
    int index = 0;
    while (pre)
    {
        p = pre;
        while (p)
        {
            if (!strcmp(p->myinfo.name, name))
            {
                address[index] = p;
            }
            p = p->rightsibling;
        }
        pre = pre->firstchild;
    }
    if (index == 1)
    {
        return p;
    }
    else if (index > 1)
    {
        printf("+----------+----------+----------+----------+----------+----------+\n"
               "|Name      |ID        |Sex       |Age       |Father    |Spouse    |\n"
               "+----------+----------+----------+----------+----------+----------+\n");
        while (index--)
        {
            printf("|%-10s|%-10d|%-10s|%-10s|%-10s|%-10s|\n", p->myinfo.name, p->myinfo.id, p->myinfo.sex,
                   p->myinfo.age, p->myinfo.father, p->myinfo.spouse);
            printf("+----------+----------+----------+----------+----------+----------+\n");
            index++;
        }
    }
    return NULL;
}

/**
 * @description: treeInput
 * @author: LiuKai
 * @param: chbrotree *root, info myinfo, char *relation, char *relationName
 * @return: chbrotree *root
 * @ver: 2.0 2019/12/21
 */
chbrotree *treeInput(chbrotree *root, info myinfo, char *relation, char *relationName)
{
    chbrotree *node;
    node = mallocTreeNode(node, myinfo);

    if (root == NULL)
    {
        strcpy(node->myinfo.father, relationName);
        root = node;
        return root;
    }
    // 输入节点与该节点的父亲 // 母亲
    chbrotree *pre = nameFindPerson(root, relationName);
    if (pre == NULL)
    {
        PRINT_FONT_RED
        printf("%s %s is not exist and modification cannot be saved\n", relation, relationName);
        PRINT_ATTR_REC
        return root;
    }
    if (!strcmp(relation, "father") || !strcmp(relation, "mother"))
    {
        strcpy(node->myinfo.father, relationName);
        node->myfather = pre;
        chbrotree *next = pre->firstchild;
        pre->firstchild = node;
        node->rightsibling = next;
    }
    // !!!在这里讨论其他的亲属关系
    else if ((relation, "uncle") || (relation, "aunt"))
    {
        chbrotree *gfather = pre->myfather;
    }
    return root;
}

/**
 * @description: 释放除头结点外的所有节点的内存
 * @autor: liuxiaoxia
 * @param {type}
 * @return: head;
 * @ver: 1.0 2019/12/23
 */
chbrotree *delAllTree(chbrotree *root)
{
    if (root)
    {
        delAllTree(root->rightsibling);
        delAllTree(root->firstchild);
        free(root);
    }
    return NULL;
}

/**
 * @description: mallocTreeNode
 * @author: LiuKai
 * @param: chbrotree *root, info myinfo
 * @return: chbrotree *node
 * @ver: 1.0 2019/12/20
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

/**
 * @description: chbrotree *printTreeNode
 * @author: LiuKai
 * @param: chbrotree *root
 * @return: void
 * @ver: 1.0 2019/12/22
 */
chbrotree *printTreeNode(chbrotree *root)
{
    int rowTotal = 0;
    /*     if (root == NULL)
    {
        return NULL;
    } */
    // 对父节点标红
    // linkStack mystack;
    /* if (colorCount == 0)
    {
        PRINT_FONT_RED
    }
    colorCount ++; */
    // 设计输出表格
    /*
    +---------+----------+--------+-------+----------+
    |Name     |ID        |sex     |age    |Spouse    |          
    +---------+----------+--------+-------+----------+
    |1        |2         |3       |4      |5         |
    +---------+----------+--------+-------+----------+
    1 rows in table
    */
    /* printf("%s %d %s %s %s\n", root->myinfo.name, root->myinfo.id, root->myinfo.sex, root->myinfo.age, root->myinfo.spouse);
    printTreeNode(root->rightsibling);
    // PRINT_FONT_RED
    printTreeNode(root->firstchild); */
    // 将代码改为非递归形式
    chbrotree *p, *pre;
    clock_t start, end;
    float timing = 0.0;
    pre = root;
    start = clock();
    PRINT_FONT_RED
    printf(">>>\n");
    PRINT_ATTR_REC
    printf("+----------+----------+----------+----------+----------+----------+\n"
           "|Name      |ID        |Sex       |Age       |Father    |Spouse    |\n"
           "+----------+----------+----------+----------+----------+----------+\n");
    while (pre)
    {
        p = pre;
        while (p)
        {
            printf("|%-10s|%-10d|%-10s|%-10s|%-10s|%-10s|\n", p->myinfo.name, p->myinfo.id, p->myinfo.sex,
                   p->myinfo.age, p->myinfo.father, p->myinfo.spouse);
            printf("+----------+----------+----------+----------+----------+----------+\n");
            rowTotal++;
            p = p->rightsibling;
        }
        pre = pre->firstchild;
    }
    end = clock();
    timing = (float)(end - start) / CLOCKS_PER_SEC;
    printf("%d rows in table <%.2f sec>\n", rowTotal, timing);
}

// 参数param表示输出父系// 母系 // 兄弟
chbrotree namePrintTreeNode(chbrotree root, char name, int generation, char *param)
{
    linkQueue mystack;
    // 用栈暂时保存代数信息
}