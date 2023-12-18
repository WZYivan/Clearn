#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#ifndef TREE_DEF_H
#define TREE_DEF_H_

#define SLEN 41
#define MAXITEM 1000
typedef struct 
{
    char word[SLEN];
    int times;
} ITEM;
typedef struct trnode
{
    ITEM item;
    struct trnode *left;
    struct trnode *right;
} TRNODE;
typedef struct 
{
    TRNODE *root;
    int size;
} TREE;
typedef enum {a=(int)'a',b,c} _CHOICE;
_CHOICE choice;

void initialize(TREE *ptree);
#define FULL true
#define NFULL false
#define EMPTY true
#define NEMPTY false
bool iftreefull(TREE *ptree);
bool iftreempty(TREE *ptree);

#define ADDSUC true
#define ADDFAL false
#define DELSUC true
#define DELFAL false
#define IN true
#define NIN false
bool additem(const ITEM *pi,TREE *ptree);
bool deleteitem(const ITEM *pi,TREE *ptree);
bool intree(const TREE *ptree,const ITEM *pi);
int countitem(const TREE *ptree);
void deletetree(TREE *ptree);
void traverse(const TREE *ptree,void (*fc)(TREE *ptree));
#endif