/**
 * @description: ͷ�ļ�
 * @file: myhead.h
 * @author: LiuKai
 * @ver: 1.0 2019/12/26
 * @lastaurhot:LiuKai
 **/
#ifndef __MYHEAD_H__
#define __MYHEAD_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <io.h>

/**
 * @description: printfColor
 * @author: liukai
 * @ver:1.0 2019/12/19
 * @lastchange: liukai
 */ 
/*�������ǰ��ɫ*/
#define PRINT_FONT_BLA  printf("\033[30m"); //��ɫ
#define PRINT_FONT_RED  printf("\033[31m"); //��ɫ
#define PRINT_FONT_GRE  printf("\033[32m"); //��ɫ
#define PRINT_FONT_YEL  printf("\033[33m"); //��ɫ
#define PRINT_FONT_BLU  printf("\033[34m"); //��ɫ
#define PRINT_FONT_PUR  printf("\033[35m"); //��ɫ
#define PRINT_FONT_CYA  printf("\033[36m"); //��ɫ
#define PRINT_FONT_WHI  printf("\033[37m"); //��ɫ
/*�����������ɫ*/ 
#define PRINT_BACK_BLA  printf("\033[40m"); //��ɫ
#define PRINT_BACK_RED  printf("\033[41m"); //��ɫ
#define PRINT_BACK_GRE  printf("\033[42m"); //��ɫ
#define PRINT_BACK_YEL  printf("\033[43m"); //��ɫ
#define PRINT_BACK_BLU  printf("\033[44m"); //��ɫ
#define PRINT_BACK_PUR  printf("\033[45m"); //��ɫ
#define PRINT_BACK_CYA  printf("\033[46m"); //��ɫ
#define PRINT_BACK_WHI  printf("\033[47m"); //��ɫ
/*�����������*/
#define PRINT_ATTR_REC  printf("\033[0m");  //�����������Ե�ȱʡ���� 
#define PRINT_ATTR_BOL  printf("\033[1m");  //���ô��� 
#define PRINT_ATTR_LIG  printf("\033[2m");  //����һ������(ģ���ɫ��ʾ������ɫ) 
#define PRINT_ATTR_LIN  printf("\033[4m");  //�����»���(ģ���ɫ��ʾ������ɫ) 
#define PRINT_ATTR_GLI  printf("\033[5m");  //������˸ 
#define PRINT_ATTR_REV  printf("\033[7m");  //���÷���ͼ�� 
#define PRINT_ATTR_THI  printf("\033[22m"); //����һ���ܶ� 
#define PRINT_ATTR_ULIN  printf("\033[24m");//�ر��»��� 
#define PRINT_ATTR_UGLI  printf("\033[25m");//�ر���˸ 
#define PRINT_ATTR_UREV  printf("\033[27m");//�رշ���ͼ��


//ǰ��������



#endif