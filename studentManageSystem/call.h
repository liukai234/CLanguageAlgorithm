/*
 * @Description: 
 * @Author: LiuKai
 * @Date: 2019-10-08 20:57:06
 * @Version:
 * @LastEditTime: 2019-11-09 08:42:06
 * @LastEditors: Liu Kai
 */
#ifndef __CALL_H__
#define __CALL_H__
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "regex.h"
#include <io.h>
#include "dataBase.c"

// Ç°ÏòÉùÃ÷¿é
void pmenu();
void make(char *input_fileName);
int dir(char* path);
node_stu* load(node_stu* head, char* fileName);
void save(node_stu* head, char* fileName);
node_stu* init();
node_stu* insert(node_stu* head);
void prints(node_stu* head);
node_stu* findnum(node_stu* head, char* str_num);
node_stu* findname(node_stu* head, char* str_name);
node_stu* modify_num(node_stu* head, char* num, bool modify);
node_stu* modify_name(node_stu* head, char* name, bool modify);
int override_strcmp(char* str1, char* str2);
node_stu* delets(node_stu* head);

#endif
