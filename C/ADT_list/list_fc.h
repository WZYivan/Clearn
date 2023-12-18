#include "list_def.h"

#ifndef LIST_FC_H_
#define LIST_FC_H_

#define _clear_str()   while(getchar() !='\n') continue; 

char *s_gets(char *st,int siz)
{
    char *flag = fgets(st,siz,stdin);
    char *find;

    if(flag != NULL)
    {
        if((find = strchr(flag,'\n')) != NULL)
            *find = '\0';
        else _clear_str()
    }

    return flag;
}

_LIST *_initialize(_LIST *plist)
{
    plist = NULL;
    return NULL;
}

bool _iflistfull(_LIST *plist)
{
    _LIST *pnew = (_LIST *)malloc(LISTSZI);
    if(pnew == NULL)
        return FULL;
    else 
        free(pnew);
    return EMPTY;
}

bool _iflistempty(_LIST *plist)
{
    if( plist == NULL)
        return _EMPTY;
    else
        _NEMPTY;
}

bool _additem(_ITEM *tem,_LIST *plist)
{
    COUNTER__ ++;
    _LIST *pnew;//buf
    _LIST *scan = plist;

    pnew = (_LIST *)malloc(LISTSZI);
    if(pnew == NULL)
        return ADDFAILURE;
    
    strcpy(pnew->item.title,tem->title);
    pnew->item.score = tem->score;
    pnew->next=NULL;
    pnew->counter=COUNTER__;


    if(scan == NULL)
        plist=pnew;
    else
    {
        while(scan->next != NULL)
            scan = scan->next;
        scan->next = pnew;
    }

    return ADDSUCESS;
}

void _do_to_list(_LIST *plist,void (*fc) (_LIST *plist))
{
    _LIST *node = plist->next;

    while(node != NULL)
    {
        (*fc)(node);
        node = node->next;
    }
}

void _show_list(_LIST *plist)
{
    printf("[%d]:<%s>--%d\t",plist->counter,
        plist->item.title,plist->item.score);
    if(plist->counter % 6 == 5)
        putchar('\n');
}

void _empty_list(_LIST *plist)
{
    _LIST *psave;
    while(plist != NULL)
    {
        psave=(*plist).next;//?
        free(plist);
        plist = psave;
    }
}

#endif