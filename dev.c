/**
 * @description: dev�汾
 * @file: dev.c
 * @author: LiuKai
 * @ver: 2.0 2019/12/21
 * @lastchange: LiuKai
 */
#include "myhead.h"
#include "exception.h"

/**
 * @description: main
 * @author: LiuKai
 * @param: int args, char *argv[]
 * @return: 0
 * @ver: 2.0 2019/12/21
 * @lastchange: LiuKai
 */
char searchFileName[MAX_FILE_NUM][MAX_FILE_NAME];
int ID = 0; // ȫ�ֱ���IDΪÿһ���˵�Ψһ���
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
    char inputFileName[MAX_FILE_NAME] = "\0";  // �����ļ���
    char outputFileName[MAX_FILE_NAME] = "\0"; // ����ļ���
    bool fileExist = false;                    // �ļ��Ƿ���ڱ�־�� �ļ�����fileExistΪtrue
    int indexSel;                              // �˵�ѡ���±�
    bool exitFlag = false;                     // �˳���־��Ϊ���ʾ�˳�
    chbrotree *mychbrotree = NULL;

    /**
     * @description: У׼countFile and path
     */
    _getcwd(path, MAX_FILE_NAME); // ��ȡ��ǰ����·��
    printf("_getcwd: %s\n", path);
    strcat(path, "\\*.dat");
    int countFile = ls(path);

    char fileName[MAX_STRING];
    char name[MAX_STRING];
    info myinfo;
    char relation[MAX_STRING];
    char relationName[MAX_STRING];

    printf("Input \"help\" for more.\n");
    while (true)
    {
        // ����������ļ�ֵ
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
            // ls
            printf("There are %d files in total\n", countFile);
            for (int i = 0; i < countFile; i++)
            {
                printf("%s\n", searchFileName[i]);
            }
            break;
        case 2:
            // mk
            scanf("%s", fileName);
            mk(fileName);
            countFile = ls(path); // У׼countFile and searchFileName
            break;
        case 3:
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
                    if (mychbrotree != NULL)
                    {
                        printf("Saving previous data file to %s...\n", outputFileName);
                        save(mychbrotree, outputFileName);
                        mychbrotree = NULL;
                        printf("Save finished\n");
                    }
                    strcpy(outputFileName, inputFileName);
                    printf("Initialize memory, load data to memory\n");
                    mychbrotree = load(mychbrotree, inputFileName);
                    printf("Load finished\n");
                    break;
                }
            }
            if (!fileExist)
            {
                printf("File does not exist\n");
            }
            fileExist = false;
            break;
        case 4:
            // close
            save(mychbrotree, outputFileName);
            printf("Save finished\n");
            mychbrotree = NULL;
            break;

        case 5:
            // do idFindPerson
            break;
        case 6:

            scanf("%s", name);
            nameFindPerson(mychbrotree, name);
            break;

        case 7:
            // input
            scanf("%s%s", relation, relationName);
            scanf("%s%s%s%s", myinfo.name, myinfo.sex, myinfo.age, myinfo.spouse);
            mychbrotree = treeInput(mychbrotree, myinfo, relation, relationName);
            break;
        case 8:
            printTreeNode(mychbrotree);
            break;
        case 9:
            exitFlag = true;
            break;
        default:
            printf("Command error or does not exist\n");
            break;
        }
        printf("Execution completed\n");
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
 * @lastchange: LiuKai
 */
void menuPrint()
{
    printf("help             format: help\n"
           "ls               format: ls\n"
           "mk               format: mk [*.dat]\n"
           "open             format: open [*.dat]\n"
           "load             format: laod [*.dat]\n"
           "save             format: save [*.dat]\n"
           "idFindPerson     format: idFindPerson [id]\n"
           "nameFindPerson   format: nameFindPerson [name]\n"
           "treeInput        format: input [relation][relationName][name][id][sex][age][spouse]"
           "printTreeNode    format: printTreeNode\n"
           "exit             format: exit\n");
}

/**
 * @description: ��pathĿ¼�²���.dat�ļ�
 * @author�� liukai
 * @param {type: char*} path
 * @return: void
 * @ver: 2.0 2019/12/21
 * @lastchange: liukai
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
        // �ж��ļ����������ļ��л����ļ�
        count++;
    } while (_findnext(hFile, &fileInfo) == 0);
    _findclose(hFile);
    return count;
}

/**
 * @description: mk
 * @author�� liukai
 * @param {type: char*} path
 * @return: void
 * @ver: 2.0 2019/12/21
 * @lastchange: liukai
 */
void mk(char *inputFileName)
{
    FILE *pFile;

    pFile = fopen(inputFileName, "wb"); // ����ʹ��txt�ļ�
    if (!pFile)
    {
        fprintf(stderr, "%s\n", strerror(errno));
    }
    fclose(pFile);
}
// void del();

/**
 * @description: load
 * @author�� liukai
 * @param {type: char*} path
 * @return: void
 * @ver: 2.0 2019/12/21
 * @lastchange: liukai
 */
chbrotree *load(chbrotree *root, char *fileName)
{
    FILE *input;
    input = fopen(fileName, "rb");
    if (!input)
    {
        PRINT_FONT_RED
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }
    chbrotree *p, *pre;
    p = (chbrotree *)malloc(sizeof(chbrotree));
    while (fread(p, sizeof(struct chbrotree0), 1, input))
    {
        root = treeInput(root, p->myinfo, "����", p->myinfo.father);
    }
    return root;
}

/**
 * @description: save
 * @author�� liukai
 * @param {type: char*} path
 * @return: void
 * @ver: 2.0 2019/12/21
 * @lastchange: liukai
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
 * @ver: 2.0 2019/12/21
 * @lastchange: LiuKai
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
    // ����ڵ���ýڵ�ĸ��� // ĸ��
    chbrotree *pre = nameFindPerson(root, relationName);
    if (pre == NULL)
    {
        PRINT_FONT_RED
        printf("%s%s is not exist and modification cannot be saved\n");
        return root;
    }
    if (!strcmp(relation, "����") || !strcmp(relation, "ĸ��"))
    {
        strcpy(node->myinfo.father, relationName);
        chbrotree *next = pre->firstchild;
        pre->firstchild = node;
        node->rightsibling = next;
    }
    // !!!����������������������ϵ
    else
    {
        chbrotree *next = pre->rightsibling;
        pre->rightsibling = node;
        node->rightsibling = next;
        strcpy(node->myinfo.father, pre->myinfo.father); // ���²����Ը��׹�ϵ���ҵ����˵�father��Ϣ
    }
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

chbrotree *printTreeNode(chbrotree *root)
{
    int rowTotal = 0;
    /*     if (root == NULL)
    {
        return NULL;
    } */
    // �Ը��ڵ���
    // linkStack mystack;
    /* if (colorCount == 0)
    {
        PRINT_FONT_RED
    }
    colorCount ++; */
    // ���������
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
    // �������Ϊ�ǵݹ���ʽ
    chbrotree *p, *pre;
    pre = root;
    printf("+----------+----------+----------+----------+----------+\n"
           "|Name      |ID        |Sex       |Age       |Spouse    |\n"
           "+----------+----------+----------+----------+----------+\n");
    while (pre)
    {
        p = pre;
        while (p)
        {
            printf("|%-10s|%-10d|%-10s|%-10s|%-10s|\n", root->myinfo.name, root->myinfo.id, root->myinfo.sex, root->myinfo.age, root->myinfo.spouse);
            printf("+----------+----------+----------+----------+----------+\n");
            rowTotal++;
            p = p->rightsibling;
        }
        pre = pre->firstchild;
    }
    printf("%d rows in table\n", rowTotal);
}

// ����param��ʾ�����ϵ// ĸϵ // �ֵ�
chbrotree namePrintTreeNode(chbrotree root, char name, int generation, char *param)
{
    linkStack mystack;
    // ��ջ��ʱ���������Ϣ
}