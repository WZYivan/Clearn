#include<stdbool.h>

#ifndef TREE_H_
#define TREE_H_

#define SLEN 41
#define MAXSIZ 1000
#define MAXTYP 5
typedef struct{
    char name[SLEN];
    char type[MAXTYP][MAXSIZ];
    int  time;
} ITEM;
typedef struct node{
    ITEM item;
    struct node *left;
    struct node *right;
} NODE;
typedef struct{
    NODE *root;
    int size;
} TREE;

void Initiallize(TREE *ptree);
bool Iftreefull(TREE *ptree);
bool Iftreeempty(TREE *ptree);
int Sizeoftree(TREE *ptree);
void Traverse(TREE *ptree,void (*fc)(ITEM *pi));
bool Ifintree(TREE *ptree,ITEM *pi);
bool Additem(TREE *ptree,ITEM *pi);
bool Deleteitem(TREE *ptree,ITEM *pi);
bool Delettree(TREE *ptree);
#endif