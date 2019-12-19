/**
 * @description: 异常处理机制
 * @author: liukai
 * @ver:1.0 2019/12/19
 * @lastchange: liukai
 */ 
#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__
#include <setjmp.h>
jmp_buf Jump_Buffer;
#define try if (!setjmp(Jump_Buffer))
#define catch else
#define throw longjmp(Jump_Buffer, 1)
#endif
