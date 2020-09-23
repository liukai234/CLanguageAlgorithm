/*
 * @Description: 学生信息管理程序
 * @Author: LiuKai
 * @Date: 2019-10-08 20:56:51
 * @Version:4
 * @LastEditTime: 2019-11-20 22:12:22
 * @LastEditors: Liu Kai
 */
#include "call.h"
extern int errno;
char FileName[MaxFileName][MaxFileName];
int main(int args, char* argv[]) {
    // system("chcp 936");
    // system("cls");
    FILE* fp;
    node_stu* StuNode = NULL;
    char path[MaxFileName];                    // 当前工作路径
    char input_fileName[MaxFileName] = "\0";   // 输入文件
    char output_fileName[MaxFileName] = "\0";  // 输出文件
    bool exitFlag = false;
    bool filexist = false;
    bool tocls = false;
    int sel;
    char strsel[30];  // switch选择指示
    char num[STR_SIZE];
    char name[STR_SIZE];

    // char* _getcwd(char* buffer, int maxlen);
    _getcwd(path, MaxFileName);
    printf("当前工作目录: %s\n", path);
    // 为dir添加查找筛选
    strcat(path, "\\*.dat");
    int count = dir(path);

    printf("help获取帮助\n");
    while (true) {
        scanf("%s", strsel);
        for (sel = 0; sel < SELATION; sel++) {
            if (!strcmp(strsel, selarr[sel])) {
                break;
            }
        }
        switch (sel) {
            case 0:
                if (StuNode) {
                    StuNode = insert(StuNode);
                } else {
                    printf("当前无打开的数据文件\n");
                }
                break;
            case 1:
                if (StuNode) {
                    prints(StuNode);
                } else {
                    printf("当前无打开的数据文件\n");
                }
                break;
            case 2:
                if (StuNode)
                    scanf("%s", num);
                findnum(StuNode, num);
                break;
            case 3:
                if (StuNode) {
                    scanf("%s", name);
                    findname(StuNode, name);
                } else {
                    printf("当前无打开的数据文件\n");
                }
                break;
            case 4:
                if (StuNode) {
                    scanf("%s", num);
                    StuNode = modify_num(StuNode, num, false);
                } else {
                    printf("当前无打开的数据文件\n");
                }
                break;
            case 5:
                if (StuNode) {
                    scanf("%s", name);
                    StuNode = modify_name(StuNode, name, false);
                } else {
                    printf("当前无打开的数据文件\n");
                }
                break;
            case 6:
                if (StuNode) {
                    scanf("%s", num);
                    StuNode = modify_name(StuNode, num, true);
                } else {
                    printf("当前无打开的数据文件\n");
                }
                break;
            case 7:
                if (StuNode) {
                    scanf("%s", name);
                    StuNode = modify_name(StuNode, name, true);
                } else {
                    printf("当前无打开的数据文件\n");
                }
                break;
            case 8:
                exitFlag = true;
                break;
            case 9:
                printf("初始化数据文件(所有数据将被清除)\n");
                printf("继续?(输入y或Y继续)\n");
                char consel[1];
                scanf("%s", consel);
                if (consel[0] == 'Y' || consel[0] == 'y') {
                    StuNode = init();
                    exitFlag = true;
                    printf("数据文件初始化完成\n");
                } else {
                    printf("操作已放弃\n");
                }
                break;
            case 10:
                pmenu();
                break;
            case 11:
                // dir
                printf("共有%d个数据文件\n", count);
                for (int i = 0; i < count; i++) {
                    printf("%s\n", FileName[i]);
                }
                break;
            case 12:
                // open
                if (StuNode) {
                    printf("正在保存上一个数据文件...\n");
                    save(StuNode, output_fileName);
                    printf("保存完成\n");
                }
                while (true) {
                    // printf("输入数据文件名以操作:\n");
                    scanf("%s", input_fileName);
                    for (int i = 0; i < count; i++) {
                        if (!strcmp(input_fileName, FileName[i])) {
                            filexist = true;
                        }
                    }
                    if (filexist) {
                        break;
                    } else {
                        printf("输入错误或文件不存在\n");
                    }
                }
                // 对同一个文件进行操作
                strcpy(output_fileName, input_fileName);
                printf("初始化内存, 向内存加载数据...\n");
                StuNode = init();
                StuNode = load(StuNode, input_fileName);
                printf("数据加载完成\n");
                break;
            case 13:
                // madir
                scanf("%s", input_fileName);
                madir(input_fileName);
                count = dir(path);
                break;
            case 14:
                // del
                scanf("%s", input_fileName);
                if (!remove(input_fileName)) {
                    printf("删除成功\n");
                    count = dir(path);
                } else {
                    fprintf(stderr, "%s\n", strerror(errno));
                }
                // 如果删除的文件和当前打开的文件是同一个文件则释放StuNode
                if (!strcmp(input_fileName, output_fileName)) {
                    StuNode = delets(StuNode);
                }
                StuNode = NULL;
                break;
            case 15:
                // close
                if (StuNode) {
                    printf("正在保存数据文件...\n");
                    save(StuNode, output_fileName);
                    printf("保存完成\n");
                } else {
                    printf("无需要保存的内容\n");
                }
                break;
            default:
                printf("命令不存在\n");
                break;
        }
        if (exitFlag) {
            break;
        }
    }
    printf("正在将数据写入数据库...\n");
    if (StuNode) {
        save(StuNode, output_fileName);
        printf("数据写入完成,程序即将关闭\n");
    } else {
        printf("无需要保存的内容\n");
    }
    Sleep(2000);
    return 0;
}

void pmenu() {
    printf(
        "dir            查看数据库\n"
        "open           打开数据文件(格式:open [filename])\n"
        "mkdir          建立新数据文件(格式:madir [filename])\n"
        "del            删除数据文件(格式:del [filename])\n"
        "close          保存并关闭当前数据文件\n"
        "insert         插入一个数据\n"
        "print          显示所有成员\n"
        "clear          清空数据文件\n"
        "findnum        查询学号\n"
        "findname       查询姓名\n"
        "delnum         以学号为依据查找并删除\n"
        "delname        以姓名为依据查找并删除\n"
        "modifynum      以学号为依据查找并修改\n"
        "modifyname     以姓名为依据查找并修改\n"
        "exit           退出\n"
        "help           帮助\n");
}

/**
 * @description: 建立新数据文件
 * @param {type} 
 * @return: 
 */
void madir(char* input_fileName) {
    FILE* fp;

    fp = fopen(input_fileName, "wb");
    if (!fp) {
        fprintf(stderr, "%s\n", strerror(errno));
    }
    fclose(fp);
}

/**
 * @description: 在path目录下查找.dat文件
 * @param {type: char*} path
 * @return: void
 */
int dir(char* path) {
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
        strcpy(FileName[count], fileInfo.name);
        // (fileInfo.attrib & _A_SUBDIR ? "[folder]" : "[file]")
        // 判断文件的属性是文件夹还是文件
        count++;
    } while (_findnext(hFile, &fileInfo) == 0);
    _findclose(hFile);
    return count;
}

/**
 * @description: 从.dat数据库加载数据到链表
 * @param {type: node_stu*}  head
 * @param {type: char*}  fileName
 * @return: head
 */
node_stu* load(node_stu* head, char* fileName) {
    FILE* input;
    node_stu *pre, *p;
    input = fopen(fileName, "rb");
    if (!input) {
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }
    pre = head;

    p = (node_stu*)malloc(sizeof(node_stu));
    while (fread(p, sizeof(struct node), 1, input)) {
        p->next = pre->next;
        pre->next = p;
        pre = p;
        p = (node_stu*)malloc(sizeof(node_stu));
    }
    free(p);
    fclose(input);
    return head;
}

/**
 * @description: 将数据库写入.dat文件
 * @param {type: node_stu*}  head
 * @param {type: char*}  fileName
 * @return: void
 */
void save(node_stu* head, char* fileName) {
    FILE* output;
    node_stu* p;
    output = fopen(fileName, "wb");
    if (!output) {
        fprintf(stderr, "%s\n", strerror(errno));
        return;
    }
    p = head;
    p = p->next;
    if (!p) {
        printf("Empty\n");
        return;
    }
    while (p) {
        fwrite(p, sizeof(struct node), 1, output);
        int a = ferror(output);
        p = p->next;
    }
    free(p);
    fclose(output);
}

/**
 * @description: 初始化链表
 * @param {type} void
 * @return: void
 */
node_stu* init() {
    node_stu* head;
    head = (node_stu*)malloc(sizeof(node_stu));
    head->next = NULL;
    return head;
}

/**
 * @description:
 * 链表有序(从小到大)插入(插入时先根据学号排序,学号相同时以年龄排序)
 * @param {type: node_stu*} head
 * @return:head
 */
node_stu* insert(node_stu* head) {
    node_stu *p, *pre, *Lastpos;
    pre = head;
    p = (node_stu*)malloc(sizeof(node_stu));
    // 学号不允许重复
    while (true) {
        printf("输入学号 姓名 年龄 性别 出生年月 地址 E-mail 电话\n");
        scanf("%s %s %s %s %s %s %s %s", p->num_stu, p->name, p->age, p->sex,
              p->birth, p->addr, p->email, p->tele);
        if (findnum(head, p->num_stu)) {
            printf("此学号已存在\n");
        } else {
            break;
        }
    }
    //只有一个头结点
    if (!pre->next) {
        p->next = pre->next;
        pre->next = p;
        return head;
    }
    // 从小到大排序
    Lastpos = pre;
    pre = pre->next;
    while (pre && override_strcmp(pre->num_stu, p->num_stu) < 0) {
        Lastpos = pre;
        pre = pre->next;
    }
    // 在头结点插入
    /* if (head->next == Lastpos) {
        p->next = Lastpos->next;
        Lastpos->next = p;
        return head;
    } */
    // bool premove = false;
    if (pre && (override_strcmp(pre->age, p->age) <= 0)) {
        while (pre && override_strcmp(pre->age, p->age) <= 0 &&
               !override_strcmp(pre->num_stu, p->num_stu)) {
            Lastpos = pre;
            pre = pre->next;
            // premove = true;
        }
    }  // else {
    // premove = true;
    pre = Lastpos;
    p->next = pre->next;
    pre->next = p;
    return head;
}

/**
 * @description: 结点连续输出
 * @param {type: node_stu*} head
 * @return:void
 */
void prints(node_stu* head) {
    node_stu* p;
    p = head;
    p = p->next;
    if (!p) {
        printf("Empty\n");
        return;
    }
    while (p) {
        printf("std:%s %s %s %s %s %s %s %s\n", p->num_stu, p->name, p->age,
               p->sex, p->birth, p->addr, p->email, p->tele);
        p = p->next;
    }
    free(p);
}

/**
 * @description: 单节点输出(弃用)
 * @param {type}
 * @return:
 */
/* void print(node_stu* head) {
    node_stu* p;
    p = head;
    p = p->next;
    if (!p) {
        printf("Empty\n");
        return;
    }
    while (p) {
        printf("std:%s %s %s %s %s %s %s %s\n", p->num_stu, p->name, p->age,
               p->sex, p->birth, p->addr, p->email, p->tele);
        p = p->next;
    }
    free(p);
}*/

/**
 * @description: 按学号查询(学号相同时激发姓名查询)
 * 延迟绑定,这里findnum()的返回值是找到的上一个结点,但是输出不延迟
 * @param {type :node_stu*} head
 * @param {type :char *} str_num
 * @return:pre
 */
int count = 0;
node_stu* findnum(node_stu* head, char* str_num) {
    node_stu *p = head, *pre;
    pre = p;
    p = p->next;
    count = 0;
    while (p && override_strcmp(p->num_stu, str_num)) {
        pre = p;
        p = p->next;
    }
    // bool start = true;
    if (!p) {
        printf("Not found\n");
        return NULL;
    } else {
        while (p && !override_strcmp(p->num_stu, str_num)) {
            printf("num:%s %s %s %s %s %s %s %s\n", p->num_stu, p->name, p->age,
                   p->sex, p->birth, p->addr, p->email, p->tele);
            /*  if (start) {
                 pre = p;
                 start = false;
             } */
            p = p->next;
            count++;
        }
    }
    return pre;
}

/**
 * @description: 按姓名查询(学号相同时激发学号查询)
 * 延迟绑定,这里findname()的返回值是找到的上一个结点,但是输出不延迟
 * @param {type :node_stu*} head
 * @param {type :char *} str_num
 * @return:pre
 */
node_stu* findname(node_stu* head, char* str_name) {
    // 延迟绑定效应
    node_stu *p = head,
             *pre;  // 返回值pre表示找到的第一个结点的上一个结点
    pre = p;
    p = p->next;
    count = 0;
    while (p && override_strcmp(p->name, str_name)) {
        pre = p;
        p = p->next;
    }
    // bool start = true;
    if (!p) {
        printf("Not found\n");
    } else {
        while (p && !override_strcmp(p->name, str_name)) {
            printf("name:%s %s %s %s %s %s %s %s\n", p->num_stu, p->name,
                   p->age, p->sex, p->birth, p->addr, p->email, p->tele);
            /* if (start) {
                pre = p;
                start = false;
            } */
            p = p->next;
            count++;
        }
    }
    return pre;
}

/**
 * @description: 修改结点时modify的第三个变量应为真,删除结点时为假
 * 学号不允许重复
 * @param {type:node_stu* } head
 * @param {type: char *} num
 * @param {type: bool} modify
 * @return: head
 */
node_stu* modify_num(node_stu* head, char* num, bool modify) {
    node_stu *p, *pre, *find;  // pre 为p的上一个结点
    find = findnum(head,
                   num);  // 在findnum中延迟绑定,找到符合条件的结点的上一个结点
    int loop = count;
    pre = find;
    p = find->next;
    printf("The total of num of %s is:%d\n", num, count);
    if (loop > 1) {
        char Tofindname[STR_SIZE];
        printf("输入名字\n");
        scanf("%s", Tofindname);
        p = find->next;
        while (loop--) {
            if (!override_strcmp(p->name, Tofindname))
                break;
            pre = p;
            p = p->next;
        }
    }
    /* if (loop < 1) {
        printf("Not found\n");
    } */

    if (modify) {
        printf("update data:\n");
        /* scanf("%s %s %s %s %s %s %s %s", p->num_stu, p->name, p->age, p->sex,
              p->birth, p->addr, p->email, p->tele); */
        head = insert(head);
    } else {
        pre->next = p->next;
        free(p);
    }
    return head;
}

/**
 * @description: 修改结点时modify的第三个变量应为真,删除结点时为假
 * 重名但学号不同
 * 要解决一个先查找num后, 后在重复num中删除name
 * @param {type:node_stu* } head
 * @param {type: char *} name
 * @param {type: bool} modify
 * @return: head
 */
node_stu* modify_name(node_stu* head, char* name, bool modify) {
    node_stu *p, *pre, *find;
    find = findname(head, name);
    int loop = count;
    pre = find;
    p = find->next;
    printf("The total of name of %s is:%d\n", name, count);
    if (loop > 1) {
        char Tofindnum[STR_SIZE];
        printf("输入学号\n");
        scanf("%s", Tofindnum);
        p = find->next;
        while (loop--) {
            if (!override_strcmp(p->name, Tofindnum))
                break;
            pre = p;
            p = p->next;
        }
    }
    /* if(loop < 1){
        printf("Not found\n");
    } */
    if (modify) {
        printf("update data:\n");
        /* scanf("%s %s %s %s %s %s %s %s", p->num_stu, p->name, p->age, p->sex,
              p->birth, p->addr, p->email, p->tele); */
        head = insert(head);
    } else {
        pre->next = p->next;
        free(p);
    }
    return head;
}

/**
 * @description: 重写strcmp函数,使可以优先判断模拟数组的长度,防止数字2排在10之后
 * @param {type :char*} str1
 * @param {type :char*} str2
 * @return: re
 */
int override_strcmp(char* str1, char* str2) {
    int re;
    int lenstr1 = 0;
    int lenstr2 = 0;
    int i;
    for (i = 0; str1[i] != 0; i++) {
        lenstr1++;
    }
    for (i = 0; str2[i] != 0; i++) {
        lenstr2++;
    }
    if (lenstr1 < lenstr2) {
        re = -1;
    } else if (lenstr1 > lenstr2) {
        re = 1;
    } else {
        re = strcmp(str1, str2);
    }

    return re;
}

/**
 * @description: 释放除头结点外的所有节点的内存
 * @param {type}
 * @return: head;
 */
node_stu* delets(node_stu* head) {
    node_stu *p = head->next, *pre;
    while (p) {
        pre = p;
        p = p->next;
        free(pre);
    }
    return head;
}