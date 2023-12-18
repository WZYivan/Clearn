#ifndef LIST_H
#define LIST_H

#include<stdbool.h>

typedef struct _ex
{
    ;
}   EX;
#define NMAX 41
typedef struct _item
{
    char name[NMAX];
    long long number;
    struct _item *forward;
    struct _item *backward;  
    EX *extra;
}   ITEM;
typedef struct _index
{
    struct _index *forward;
    struct _index *backward;
    char flag;
    ITEM *rootitem;
} INDEX;

void Initialize(INDEX *root);
bool Additem(ITEM *pitem,INDEX *root);
bool Deletitem(ITEM *pitem,INDEX *root);
void Showlist(INDEX *plist);
bool Deletlist(INDEX *root);
void Traverse(INDEX *root , void (*pf)(ITEM *pitem));
#endif