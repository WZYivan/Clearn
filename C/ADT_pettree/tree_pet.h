#include<string.h>
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>
#include"tree.h"

#ifndef TREE_PET_H_
#define TREE_PET_H_
typedef struct{
    NODE *parent;
    NODE *child;
} PAIR;
static PAIR Seekitem(const TREE *ptree,const ITEM *pi);
static bool Toright(const ITEM *i1,const ITEM *i2);
static bool Toleft(const ITEM *i1,const ITEM *i2);
static bool AddNode(NODE *root,NODE *pnode);
static NODE* MakeNode(const ITEM *pi);
static bool DeletAllNode(NODE *root);
static bool DeletNode(NODE **ppnode);
static void InOrder(const NODE *root,void (*fc)(TREE *ptree));
//-----------------------------------------------------------------------
static bool Toleft(const ITEM *i1,const ITEM *i2)
{
    return (strcmp(i1->name,i2->name)<0)? true:false;
}
static bool Toleft(const ITEM *i1,const ITEM *i2)
{
    return (strcmp(i1->name,i2->name)>0)? true:false;
}

static PAIR Seekitem(const TREE *ptree,const ITEM *pi)
{
    PAIR look;
    look.parent=NULL;
    look.child=ptree->root;
    if(look.child==NULL)
        return look;
    while(look.child!=NULL)
    {
        if(Toleft(pi,&(look.child->item)))
        {
            look.parent=look.child;
            look.child=look.child->left;
        }
        else if(Toright(pi,&(look.child->item)))
        {
            look.parent=look.child;
            look.child=look.child->right;
        }
        else break;
    }
    return look;
}

static NODE* MakeNode(const ITEM *pi)
{
    NODE *pnew=(NODE *)malloc(sizeof(NODE));
    if(pnew!=NULL)
    {
        pnew->item.time++;
        strcpy(pnew->item.name,pi->name);
        strcpy(pnew->item.type[0],pi->type[0]);
    }
    return pnew;
}
static bool AddNode(NODE *root,NODE *pnode)
{
    if(Toleft(&root->item,&pnode->item))
    {
        if(root->left==NULL)
            root->left=pnode;
        else AddNode(root->left,pnode);
    }
    else if(Toright(&root->item,&pnode->item))
    {
        if(root->right==NULL)
            root->right=pnode;
        else AddNode(root->right,pnode);
    }
    else{
        fprintf(stderr,"add node err\n");
        exit(1);
    }
    return true;
}

static bool DeletNode(NODE **ppnode)
{
    NODE *temp;
    if((*ppnode)->left==NULL)
    {
        temp=*ppnode;
        *ppnode=(*ppnode)->right;
        free(temp);
    }
    else if((*ppnode)->right==NULL)
    {
        temp=*ppnode;
        *ppnode=(*ppnode)->left;
        free(temp);
    }
    else{
        for(temp=(*ppnode)->left;temp->left!=NULL;temp=temp->right)
            continue;
        temp->right=(*ppnode)->right;
        temp=*ppnode;
        *ppnode=(*ppnode)->left;
        free(temp);
    }
}
static bool DeletAllNode(NODE *root)
{
    NODE *pright;
    while(root!=NULL)
    {
        pright=root->right;
        DeletAllNode(root->left);
        free(root);
        DeletAllNode(pright);
    }
}

static void inorder(const NODE *root,void (*fc)(ITEM item))
{
    if(root!=NULL)
    {
        inorder(root->left,fc);
        (*fc)(root->item);
        inorder(root->right,fc);
    }
}
//-----------------------------------------------------------------------
extern void Initiallize(TREE *ptree)
{
    ptree->root=NULL;
    ptree->size=0;
}
extern bool Iftreefull(TREE *ptree)
{
    return (ptree->size==MAXSIZ)? true:false;
}
extern bool Iftreeempty(TREE *ptree)
{
    return (ptree->root==NULL)? true:false;
}
extern int Sizeoftree(TREE *ptree)
{
    return ptree->size;
}
extern void traverse(const TREE *ptree,void (*fc)(ITEM item))
{
    if(ptree!=NULL)
        inorder(ptree->root,fc);
}
bool Ifinree(const TREE *ptree,const ITEM *pi)
{
    return (Seekitem(ptree,pi).child==NULL) ? true : false;
}

extern bool Additem(TREE *ptree,ITEM *pi)
{
    NODE *pnew;
    PAIR look;

    if(Iftreefull(ptree)==true) return false;
    if((look=Seekitem(ptree,pi)).child!=NULL)
    {
        look.child->item.time++;
        return true;
    }
    pnew=MakeNode(pi);
    if(pnew==NULL)
    {
        fprintf(stderr,"no memory for node\n");
        exit(2);
    }
    ptree->size++;
    if(ptree->root==NULL)
        ptree->root=pnew;
    else 
        AddNode(pnew,ptree->root);
    return true;
}
extern bool Deleteitem(TREE *ptree,ITEM *pi)
{
    PAIR look;
    look=Seekitem(ptree,pi);
    if(look.child==NULL)
        return false;
    if(look.parent==NULL) DeletNode(&ptree->root);
    else if(look.parent->left==look.child)
        DeletNode(&look.parent->left);
    else DeletNode(&look.parent->right);
    ptree->size--;
    return true;
}
extern bool Delettree(TREE *ptree)
{
    DeletAllNode(ptree->root);
    ptree->root=NULL;
    ptree->size=0;
    return true;
}
#endif