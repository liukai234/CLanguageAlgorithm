/*
 * @Description: 
 * @Author: LiuKai
 * @Date: 2019-10-08 20:59:46
 * @Version:
 * @LastEditTime: 2019-11-20 22:11:23
 * @LastEditors: Liu Kai
 */
#define STR_SIZE 100
#define INFO_SIZE 10
#define MAXSIZE 100
#define MaxFileName 100
#define SELATION 16
typedef char datatype;
typedef struct node {
    datatype num_stu[STR_SIZE];
    datatype name[STR_SIZE];
    datatype birth[STR_SIZE];
    datatype age[STR_SIZE];
    datatype sex[STR_SIZE];
    datatype addr[STR_SIZE];
    datatype email[STR_SIZE];
    datatype tele[STR_SIZE];
    struct node* next;
} node_stu;

char selarr[SELATION][STR_SIZE] = {
    "insert",    "print",      "findnum", "findname", "delnum", "delname",
    "modifynum", "modifyname", "exit",    "clear",    "help",   "dir",
    "open",      "mkdir",       "del",     "close"};
