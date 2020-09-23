/*
 * @Description: ѧ����Ϣ�������
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
    char path[MaxFileName];                    // ��ǰ����·��
    char input_fileName[MaxFileName] = "\0";   // �����ļ�
    char output_fileName[MaxFileName] = "\0";  // ����ļ�
    bool exitFlag = false;
    bool filexist = false;
    bool tocls = false;
    int sel;
    char strsel[30];  // switchѡ��ָʾ
    char num[STR_SIZE];
    char name[STR_SIZE];

    // char* _getcwd(char* buffer, int maxlen);
    _getcwd(path, MaxFileName);
    printf("��ǰ����Ŀ¼: %s\n", path);
    // Ϊdir��Ӳ���ɸѡ
    strcat(path, "\\*.dat");
    int count = dir(path);

    printf("help��ȡ����\n");
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
                    printf("��ǰ�޴򿪵������ļ�\n");
                }
                break;
            case 1:
                if (StuNode) {
                    prints(StuNode);
                } else {
                    printf("��ǰ�޴򿪵������ļ�\n");
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
                    printf("��ǰ�޴򿪵������ļ�\n");
                }
                break;
            case 4:
                if (StuNode) {
                    scanf("%s", num);
                    StuNode = modify_num(StuNode, num, false);
                } else {
                    printf("��ǰ�޴򿪵������ļ�\n");
                }
                break;
            case 5:
                if (StuNode) {
                    scanf("%s", name);
                    StuNode = modify_name(StuNode, name, false);
                } else {
                    printf("��ǰ�޴򿪵������ļ�\n");
                }
                break;
            case 6:
                if (StuNode) {
                    scanf("%s", num);
                    StuNode = modify_name(StuNode, num, true);
                } else {
                    printf("��ǰ�޴򿪵������ļ�\n");
                }
                break;
            case 7:
                if (StuNode) {
                    scanf("%s", name);
                    StuNode = modify_name(StuNode, name, true);
                } else {
                    printf("��ǰ�޴򿪵������ļ�\n");
                }
                break;
            case 8:
                exitFlag = true;
                break;
            case 9:
                printf("��ʼ�������ļ�(�������ݽ������)\n");
                printf("����?(����y��Y����)\n");
                char consel[1];
                scanf("%s", consel);
                if (consel[0] == 'Y' || consel[0] == 'y') {
                    StuNode = init();
                    exitFlag = true;
                    printf("�����ļ���ʼ�����\n");
                } else {
                    printf("�����ѷ���\n");
                }
                break;
            case 10:
                pmenu();
                break;
            case 11:
                // dir
                printf("����%d�������ļ�\n", count);
                for (int i = 0; i < count; i++) {
                    printf("%s\n", FileName[i]);
                }
                break;
            case 12:
                // open
                if (StuNode) {
                    printf("���ڱ�����һ�������ļ�...\n");
                    save(StuNode, output_fileName);
                    printf("�������\n");
                }
                while (true) {
                    // printf("���������ļ����Բ���:\n");
                    scanf("%s", input_fileName);
                    for (int i = 0; i < count; i++) {
                        if (!strcmp(input_fileName, FileName[i])) {
                            filexist = true;
                        }
                    }
                    if (filexist) {
                        break;
                    } else {
                        printf("���������ļ�������\n");
                    }
                }
                // ��ͬһ���ļ����в���
                strcpy(output_fileName, input_fileName);
                printf("��ʼ���ڴ�, ���ڴ��������...\n");
                StuNode = init();
                StuNode = load(StuNode, input_fileName);
                printf("���ݼ������\n");
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
                    printf("ɾ���ɹ�\n");
                    count = dir(path);
                } else {
                    fprintf(stderr, "%s\n", strerror(errno));
                }
                // ���ɾ�����ļ��͵�ǰ�򿪵��ļ���ͬһ���ļ����ͷ�StuNode
                if (!strcmp(input_fileName, output_fileName)) {
                    StuNode = delets(StuNode);
                }
                StuNode = NULL;
                break;
            case 15:
                // close
                if (StuNode) {
                    printf("���ڱ��������ļ�...\n");
                    save(StuNode, output_fileName);
                    printf("�������\n");
                } else {
                    printf("����Ҫ���������\n");
                }
                break;
            default:
                printf("�������\n");
                break;
        }
        if (exitFlag) {
            break;
        }
    }
    printf("���ڽ�����д�����ݿ�...\n");
    if (StuNode) {
        save(StuNode, output_fileName);
        printf("����д�����,���򼴽��ر�\n");
    } else {
        printf("����Ҫ���������\n");
    }
    Sleep(2000);
    return 0;
}

void pmenu() {
    printf(
        "dir            �鿴���ݿ�\n"
        "open           �������ļ�(��ʽ:open [filename])\n"
        "mkdir          �����������ļ�(��ʽ:madir [filename])\n"
        "del            ɾ�������ļ�(��ʽ:del [filename])\n"
        "close          ���沢�رյ�ǰ�����ļ�\n"
        "insert         ����һ������\n"
        "print          ��ʾ���г�Ա\n"
        "clear          ��������ļ�\n"
        "findnum        ��ѯѧ��\n"
        "findname       ��ѯ����\n"
        "delnum         ��ѧ��Ϊ���ݲ��Ҳ�ɾ��\n"
        "delname        ������Ϊ���ݲ��Ҳ�ɾ��\n"
        "modifynum      ��ѧ��Ϊ���ݲ��Ҳ��޸�\n"
        "modifyname     ������Ϊ���ݲ��Ҳ��޸�\n"
        "exit           �˳�\n"
        "help           ����\n");
}

/**
 * @description: �����������ļ�
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
 * @description: ��pathĿ¼�²���.dat�ļ�
 * @param {type: char*} path
 * @return: void
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
        strcpy(FileName[count], fileInfo.name);
        // (fileInfo.attrib & _A_SUBDIR ? "[folder]" : "[file]")
        // �ж��ļ����������ļ��л����ļ�
        count++;
    } while (_findnext(hFile, &fileInfo) == 0);
    _findclose(hFile);
    return count;
}

/**
 * @description: ��.dat���ݿ�������ݵ�����
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
 * @description: �����ݿ�д��.dat�ļ�
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
 * @description: ��ʼ������
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
 * ��������(��С����)����(����ʱ�ȸ���ѧ������,ѧ����ͬʱ����������)
 * @param {type: node_stu*} head
 * @return:head
 */
node_stu* insert(node_stu* head) {
    node_stu *p, *pre, *Lastpos;
    pre = head;
    p = (node_stu*)malloc(sizeof(node_stu));
    // ѧ�Ų������ظ�
    while (true) {
        printf("����ѧ�� ���� ���� �Ա� �������� ��ַ E-mail �绰\n");
        scanf("%s %s %s %s %s %s %s %s", p->num_stu, p->name, p->age, p->sex,
              p->birth, p->addr, p->email, p->tele);
        if (findnum(head, p->num_stu)) {
            printf("��ѧ���Ѵ���\n");
        } else {
            break;
        }
    }
    //ֻ��һ��ͷ���
    if (!pre->next) {
        p->next = pre->next;
        pre->next = p;
        return head;
    }
    // ��С��������
    Lastpos = pre;
    pre = pre->next;
    while (pre && override_strcmp(pre->num_stu, p->num_stu) < 0) {
        Lastpos = pre;
        pre = pre->next;
    }
    // ��ͷ������
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
 * @description: ����������
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
 * @description: ���ڵ����(����)
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
 * @description: ��ѧ�Ų�ѯ(ѧ����ͬʱ����������ѯ)
 * �ӳٰ�,����findnum()�ķ���ֵ���ҵ�����һ�����,����������ӳ�
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
 * @description: ��������ѯ(ѧ����ͬʱ����ѧ�Ų�ѯ)
 * �ӳٰ�,����findname()�ķ���ֵ���ҵ�����һ�����,����������ӳ�
 * @param {type :node_stu*} head
 * @param {type :char *} str_num
 * @return:pre
 */
node_stu* findname(node_stu* head, char* str_name) {
    // �ӳٰ�ЧӦ
    node_stu *p = head,
             *pre;  // ����ֵpre��ʾ�ҵ��ĵ�һ��������һ�����
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
 * @description: �޸Ľ��ʱmodify�ĵ���������ӦΪ��,ɾ�����ʱΪ��
 * ѧ�Ų������ظ�
 * @param {type:node_stu* } head
 * @param {type: char *} num
 * @param {type: bool} modify
 * @return: head
 */
node_stu* modify_num(node_stu* head, char* num, bool modify) {
    node_stu *p, *pre, *find;  // pre Ϊp����һ�����
    find = findnum(head,
                   num);  // ��findnum���ӳٰ�,�ҵ����������Ľ�����һ�����
    int loop = count;
    pre = find;
    p = find->next;
    printf("The total of num of %s is:%d\n", num, count);
    if (loop > 1) {
        char Tofindname[STR_SIZE];
        printf("��������\n");
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
 * @description: �޸Ľ��ʱmodify�ĵ���������ӦΪ��,ɾ�����ʱΪ��
 * ������ѧ�Ų�ͬ
 * Ҫ���һ���Ȳ���num��, �����ظ�num��ɾ��name
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
        printf("����ѧ��\n");
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
 * @description: ��дstrcmp����,ʹ���������ж�ģ������ĳ���,��ֹ����2����10֮��
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
 * @description: �ͷų�ͷ���������нڵ���ڴ�
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