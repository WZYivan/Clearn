#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

#ifndef LIST_H_
#define LIST_H_

char *s_gets(char *st,int siz);

#define TLEN 41
typedef unsigned long long _COUNTER ;
_COUNTER COUNTER__=0;//计数器
typedef struct{
    char title[TLEN];
    int score;
} _ITEM;
typedef struct _list{
    _ITEM item;
    struct _list *next;
    int counter;
} _LIST;
#define LISTSZI (sizeof(_LIST))

char *s_gets(char *st,int siz);
_LIST *_initialize(_LIST *plist);//初始化

#define FULL  true
#define EMPTY false
bool _iflistfull(_LIST *plist);
#define _EMPTY true
#define _NEMPTY false
bool _iflistempty(_LIST *plist);//检测

#define ADDSUCESS true
#define ADDFAILURE false
bool _additem(_ITEM *tem,_LIST *plist);//添加项目

void _do_to_list(_LIST *plist,void (*fc) (_LIST *plist));
void _show_list(_LIST *plist);//链表行为

void _empty_list(_LIST *plist);

#endif