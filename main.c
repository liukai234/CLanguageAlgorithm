/**
 * @description: dev版本
 * @file: dev.c
 * @author: LiuKai
 * @ver: 3.0 2019/12/21
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
    int IdFind;
    int generation;
    char direction[MAX_STRING];
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
            if (fileOpenFlag)
            {

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
            }
            else
            {
                PRINT_FONT_RED
                printf("No file is opening\n");
                PRINT_ATTR_REC
            }
            break;
        case ID_FIND_PERSON:
            if (fileOpenFlag)
            {
                scanf("%d", &IdFind);
                idFindPerson(mychbrotree, IdFind);
            }
            else
            {
                PRINT_FONT_RED
                printf("No file is opening\n");
                PRINT_ATTR_REC
            }
            break;
        case NAME_FIND_PERSON:
            if (fileOpenFlag)
            {
                scanf("%s", name);
                if (!nameFindPerson(mychbrotree, name, MAX_FIND_DEEPTH))
                {
                    PRINT_FONT_RED
                    printf("Not fount\n");
                    PRINT_ATTR_REC
                }
            }
            else
            {
                PRINT_FONT_RED
                printf("No file is opening\n");
                PRINT_ATTR_REC
            }
            break;
        case MODIFY:
            if (fileOpenFlag)
            {
                scanf("%s", name);
                mychbrotree = modify(mychbrotree, name);
            }
            else
            {
                PRINT_FONT_RED
                printf("No file is opening\n");
                PRINT_ATTR_REC
            }
            break;
        case INPUT:
            // input
            if (fileOpenFlag)
            {
                scanf("%s%s", relation, relationName);
                scanf("%s%s%s%s", myinfo.name, myinfo.sex, myinfo.birth, myinfo.spouse);
                mychbrotree = treeInput(mychbrotree, myinfo, relation, relationName);
            }
            else
            {
                PRINT_FONT_RED
                printf("No file is opening\n");
                PRINT_ATTR_REC
            }
            break;
        case PRINT_TREE_NODE:
            if (fileOpenFlag)
            {
                printTreeNode(mychbrotree);
            }
            else
            {
                PRINT_FONT_RED
                printf("No file is opening\n");
                PRINT_ATTR_REC
            }
            break;
        case GENERAT:
            if (fileOpenFlag)
            {
                // 向下查找只能向下查找1代， 向上查找可以查找父系generation代
                scanf("%s%s", name, direction);
                if (!strcmp(direction, "before"))
                {
                    scanf("%d", &generation);
                }
                else if (!strcmp(direction, "after"))
                {
                    generation = 1;
                }
                printCondition(mychbrotree, name, direction, generation);
            }
            else
            {
                PRINT_FONT_RED
                printf("Not save, retry\n");
                PRINT_ATTR_REC
            }
            break;
        case EXIT:
            exitFlag = true;
            // 保存文件
            if (fileOpenFlag)
            {
                if (save(mychbrotree, outputFileName))
                {
                    printf("Save finished\n");
                    // 释放内存
                    mychbrotree = delAllTree(mychbrotree);
                    mychbrotree = NULL;
                    fileOpenFlag = false;
                }
                else
                {
                    PRINT_FONT_RED
                    printf("Not save, retry\n");
                    PRINT_ATTR_REC
                }
            }
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
           "save and close   format: close\n"
           "load             format: laod [*.dat]\n"
           "del              format: del [*.dat]\n"
           "clear all date   format: clear\n"
           "idFindPerson     format: idFindPerson [id]\n"
           "nameFindPerson   format: nameFindPerson [name]\n"
           "modify           format: modify [searchName]\n"
           "treeInput        format: input [relation][relationName][name][sex][birth][spouse]\n"
           "printTreeNode    format: printTree\n"
           "printGenerat     fotmat:  printGenert [name][after] or printGenert [name][before][generat]\n"
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
        PRINT_ATTR_REC
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
 * @param: chbrotree *root, char *name, int deepth (deepth参数表示查找深度)
 * 当查找深度deepth设置为MAX_FIND_DEEPTH时默认为最大深度
 * @return: chbrotree *root
 * @ver: 1.0 2019/12/20
 */
// ！！！查找配偶
chbrotree *nameFindPerson(chbrotree *root, char *name, int deepth)
{
    chbrotree *p, *pre;
    chbrotree *address[MAX_STRING];
    pre = root;
    int index = 0;
    while (pre && (deepth--))
    {
        p = pre;
        while (p)
        {
            if (!strcmp(p->myinfo.name, name))
            {
                address[index] = p;
                index++;
            }
            p = p->rightsibling;
        }
        pre = pre->firstchild;
    }
    if (index == 1)
    {
        return address[0];
    }
    else if (index > 1)
    {
        // 调用条件输出
        printf("+----------+----------+----------+----------+----------+----------+\n"
               "|Name      |ID        |Sex       |Birth     |Father    |Spouse    |\n"
               "+----------+----------+----------+----------+----------+----------+\n");
        for (int i = 0; i < index; i++)
        {
            printf("|%-10s|%-10d|%-10s|%-10s|%-10s|%-10s|\n", address[i]->myinfo.name, address[i]->myinfo.id, address[i]->myinfo.sex,
                   address[i]->myinfo.birth, address[i]->myinfo.father, address[i]->myinfo.spouse);
            printf("+----------+----------+----------+----------+----------+----------+\n");
        }
        printf("Input id to find:\n");
        int myIdFind;
        scanf("%d", &myIdFind);
        for (int i = 0; i < index; i++)
        {
            if (address[i]->myinfo.id == myIdFind)
            {
                return p;
            }
        }
    }
    return NULL;
}

chbrotree *modify(chbrotree *root, char *name)
{
    info myinfo;
    printf("enter the name to modify:\n");
    chbrotree *p;
    p = nameFindPerson(root, name, MAX_FIND_DEEPTH);
    if (p == NULL)
    {
        printf("ERROR!This person doesn't exist in the family tree!");
        return NULL;
    }
    else
    {
        printf("Enter the new info:\n");
        scanf("%s%s%s%s%s", p->myinfo.name, p->myinfo.sex,
              p->myinfo.birth, p->myinfo.father, p->myinfo.spouse);
        return root;
    }
}

/**
 * @description: addChildToFather
 * @author: LiuXiaoxia
 * @param: chbrotree *Father, chbrotree *Child
 * @return: void
 * @ver: 1.0 2019/12/24
 */
chbrotree *addChildToFather(chbrotree *Father, chbrotree *Child)
{
    strcpy(Child->myinfo.father, Father->myinfo.name);
    Child->myfather = Father;
    chbrotree *next = Father->firstchild;
    Father->firstchild = Child;
    Child->rightsibling = next;
    return Father;
}

/**
 * @description: treeInput 输入节点与该节点father or mather or others
 * @author: LiuXiaoxia
 * @param: chbrotree *root, info myinfo, char *relation, char *relationName
 * @return: chbrotree *root
 * @ver: 3.0 2019/12/24
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

    chbrotree *pre = nameFindPerson(root, relationName, MAX_FIND_DEEPTH);
    if (pre == NULL)
    {
        PRINT_FONT_RED
        printf("%s %s is not exist and modification cannot be saved\n", relation, relationName);
        PRINT_ATTR_REC
        return root;
    }
    if (!strcmp(relation, "father") || !strcmp(relation, "mother"))
    {
        pre = addChildToFather(pre, node);
    }
    else if (!strcmp(relation, "uncle") || !strcmp(relation, "aunt"))
    {
        chbrotree *newfather = pre->myfather;
        generationPrintTreeNode(newfather->firstchild, 1);
        //根据输出的信息找到myinfo的父亲的ID并输入
        int myinfoFatherID;
        scanf("%d", &myinfoFatherID);
        chbrotree *p = idFindPerson(newfather->firstchild, myinfoFatherID);
        p = addChildToFather(p, node);
    }
    else if (!strcmp(relation, "grandfather") || !strcmp(relation, "grandmother"))
    {
        generationPrintTreeNode(pre->firstchild, 1);
        //根据输出的信息找到myinfo的父亲的ID并输入
        int myinfoFatherID;
        scanf("%d", &myinfoFatherID);
        chbrotree *p = idFindPerson(pre->firstchild, myinfoFatherID);
        p = addChildToFather(p, node);
    }
    else if (!strcmp(relation, "son") || !strcmp(relation, "daughter"))
    {
        chbrotree *newfather = pre->myfather->myfather;
        newfather = addChildToFather(newfather, node);
        node = addChildToFather(node, pre);
    }
    else if (!strcmp(relation, "grandson") || !strcmp(relation, "granddaughter"))
    {
        chbrotree *newfather = pre->myfather->myfather->myfather;
        newfather = addChildToFather(newfather, node);
        node = addChildToFather(node, pre->myfather);
    }
    return root;
}

/**
 * @description: 释放除头结点外的所有节点的内存
 * @autor: liuXiaoxia
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
    node->myfather = NULL;
    node->myinfo.id = ID;
    ID++;
    return node;
}

/**
 * @description: printTreeNode
 * @author: LiuKai
 * @param: chbrotree *root
 * @return: void
 * @ver: 1.0 2019/12/22
 */
void printTreeNode(chbrotree *root)
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
    |Name     |ID        |sex     |Birth  |Spouse    |          
    +---------+----------+--------+-------+----------+
    |1        |2         |3       |4      |5         |
    +---------+----------+--------+-------+----------+
    1 rows in table
    */
    /* printf("%s %d %s %s %s\n", root->myinfo.name, root->myinfo.id, root->myinfo.sex, root->myinfo.birth, root->myinfo.spouse);
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
           "|Name      |ID        |Sex       |Birth     |Father    |Spouse    |\n"
           "+----------+----------+----------+----------+----------+----------+\n");
    while (pre)
    {
        p = pre;
        while (p)
        {
            printf("|%-10s|%-10d|%-10s|%-10s|%-10s|%-10s|\n", p->myinfo.name, p->myinfo.id, p->myinfo.sex,
                   p->myinfo.birth, p->myinfo.father, p->myinfo.spouse);
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

/**
 * @description: generationPrintTreeNode
 * @author: LiuXiaoxia
 * @param: chbrotree *root, int generation
 * @return: void
 * @ver: 1.0 2019/12/24
 */
void generationPrintTreeNode(chbrotree *root, int generation)
{
    int rowTotal = 0;
    chbrotree *p, *pre;
    pre = root;
    clock_t start, end;
    float timing = 0.0;
    start = clock();
    PRINT_FONT_RED
    printf(">>>\n");
    PRINT_ATTR_REC
    printf("+----------+----------+----------+----------+----------+----------+\n"
           "|Name      |ID        |Sex       |Birth     |Father    |Spouse    |\n"
           "+----------+----------+----------+----------+----------+----------+\n");
    while (generation)
    {
        p = pre;
        while (p)
        {
            printf("|%-10s|%-10d|%-10s|%-10s|%-10s|%-10s|\n", p->myinfo.name, p->myinfo.id, p->myinfo.sex,
                   p->myinfo.birth, p->myinfo.father, p->myinfo.spouse);
            printf("+----------+----------+----------+----------+----------+----------+\n");
            rowTotal++;
            p = p->rightsibling;
        }
        pre = pre->firstchild;
        generation--;
    }
    end = clock();
    timing = (float)(end - start) / CLOCKS_PER_SEC;
    printf("%d rows in table <%.2f sec>\n", rowTotal, timing);
}

// add printcondition
/**
 * @description: printCondition
 * @author: LiuXiaoxia
 * @param: chbrotree *root, int generation
 * @return: void
 * @ver: 1.0 2019/12/24
 */
void printCondition(chbrotree *root, char *name, char *direction, int generation)
{
    int i = 0;
    generation++;
    bool moveDown = true;
    chbrotree *pre = nameFindPerson(root, name, MAX_FIND_DEEPTH);
    if (pre == NULL)
    {
        PRINT_FONT_RED
        printf("%s is not exist and modification cannot be saved\n", name);
        PRINT_ATTR_REC
    }
    PRINT_FONT_RED
    printf(">>>\n");
    PRINT_ATTR_REC
    printf("+----------+----------+----------+----------+----------+----------+\n"
           "|Name      |ID        |Sex       |Birth     |Father    |Spouse    |\n"
           "+----------+----------+----------+----------+----------+----------+\n");
    while (generation && pre != NULL)
    {
        printf("|%-10s|%-10d|%-10s|%-10s|%-10s|%-10s|\n", pre->myinfo.name, pre->myinfo.id, pre->myinfo.sex,
               pre->myinfo.birth, pre->myinfo.father, pre->myinfo.spouse);
        printf("+----------+----------+----------+----------+----------+----------+\n");
        if (!strcmp("after", direction))
        {
            if (moveDown)
                pre = pre->firstchild;
            moveDown = false;
            pre = pre->rightsibling;
        }
        else if (!strcmp("before", direction))
        {
            pre = pre->myfather;
            generation--;
        }
    }
}

/*
void isSpouse (char *s, chbrotree *person, char *name)
{
    if (person->myinfo.name == name)
    {
        strcpy(s, person->myinfo.sex);
    }
    else
    {
        if (person->myinfo.sex == "female")
        {
            strcpy(s, "male");
        }
        else if (person->myinfo.sex == "male")
        {
            strcpy(s, "female");
        }
    }
}*/

/**
 * @description: conGeneration
 * @author: LiuXiaoxia
 * @param: chbrotree *firstPerson, chbrotree *secondPerson
 * @return: chbrotree *
 * @ver: 1.0 2019/12/25
 */
chbrotree *conGeneration (chbrotree *firstPerson, chbrotree *secondPerson)
{
    chbrotree *p = firstPerson->myfather->firstchild;
    while (p)
    {
        if (p->myinfo.name == secondPerson->myinfo.name || p->myinfo.spouse == secondPerson->myinfo.name)
        {
            return p;
        }
        p = p->rightsibling;
    }
    return NULL;
}

struct Relation
{
    char relation;
    char name[200];
}rela[200];

/**
 * @description: modifyRelation
 * @author: LiuXiaoxia
 * @param: chbrotree *p, int *idx, chbrotree *pp, chbrotree *secondPerson
 * @return: bool
 * @ver: 1.0 2019/12/25
 */
bool modifyRelation  (chbrotree *p, int *idx, chbrotree *pp, chbrotree *secondPerson)
{
    int id = idx;
    if (p->myinfo.sex == "male")
    {
        rela[id].relation = 's';
        strcpy(rela[id ++].name, p->myinfo.name);
    }
    else
    {
        rela[id].relation = 'd';
        strcpy(rela[id ++].name, p->myinfo.name);
    }

    if (pp)
    {
        if (pp->myinfo.sex != secondPerson->myinfo.sex)
        {
            rela[id].relation = 'p'; //p为配偶
            strcpy(rela[id ++].name, pp->myinfo.name);
        }
        return true;
    }
    return false;
}

/**
 * @description: difGeneration
 * @author: LiuXiaoxia
 * @param: chbrotree *root, char *firstName, char *secondName
 * @return: int
 * @ver: 1.0 2019/12/25
 */
int difGeneration (chbrotree *root, char *firstName, char *secondName)
{
    chbrotree *firstPerson = nameFindPerson(root, firstName, MAX_FIND_DEEPTH);
    chbrotree *secondPerson = nameFindPerson(root, secondName, MAX_FIND_DEEPTH);
    //char firstSex[100], secondSex[100];
    //isSpouse(firstSex, firstPerson, firstName);
    //isSpouse(secondSex, secondPerson, secondName);
    
    int idx = 0;
    chbrotree *p;
    bool flag = false;

    chbrotree *grandfather = firstPerson->myfather->myfather;
    rela[idx].relation = 'g';
    strcpy(rela[idx ++].name, grandfather->myinfo.name);
    while (grandfather)
    {
        p = conGeneration(grandfather, secondPerson);
        if (p)
        {
            if (p->myinfo.sex != secondPerson->myinfo.sex)
            {
                rela[idx].relation = 'p';
                strcpy(rela[idx ++].name, p->myinfo.name);
            }
            break;
        }

        chbrotree *father = grandfather->firstchild;
        while (father)
        {
            p = conGeneration(father, secondPerson);
            flag = modifyRelation(father, idx, p, secondPerson);
            if (flag) break;

            chbrotree *brother = father->firstchild;
            while (brother)
            {
                p = conGeneration(brother, secondPerson);
                flag = modifyRelation(brother, idx, p, secondPerson);
                if (flag) break;

                chbrotree *son = brother->firstchild;
                while (son)
                {
                    p = conGeneration(son, secondPerson);
                    flag = modifyRelation(son, idx, p, secondPerson);
                    if (flag) break;

                    chbrotree *grandson = son->firstchild;
                    while (grandson)
                    {
                        p = conGeneration(grandson, secondPerson);
                        flag = modifyRelation(grandson, idx, p, secondPerson);
                        if (flag) break;
                        grandson = grandson->rightsibling;
                    }
                    if (flag) break;
                    idx -= 2;
                    son = son->rightsibling;
                }
                if (flag) break;
                idx -= 2;
                brother = brother->rightsibling;
            }
            if (flag) break;
            idx -= 2;
            father = father->rightsibling;
        }
        if (flag) break;
        idx -= 2;
        break;
    }
    return --idx;
}
void transToAppellation(char *relationStr)
{
    char appellation[MAX_FIND_DEEPTH][MAX_STRING];
    char prefix[MAX_STRING];
    int indexStr = 0; // relationStr下标
    int top = 0;      // 栈顶
    for (indexStr = 0; relationStr[indexStr] != '\''; indexStr++)
    {
        prefix[indexStr] = relationStr[indexStr];
    }
    prefix[indexStr] = '\n';
    for (int indexAppe = 0; relationStr[indexStr] != '\0'; indexStr++, indexAppe++)
    {
        if (relationStr[indexStr] == '\'' && relationStr[indexStr + 1] == 's')
        {
            indexStr += 3;
        }
        appellation[top][indexAppe] = relationStr[indexStr];
        top++;
    }
    char *top;
    top = appellation[0];
    return;
}
