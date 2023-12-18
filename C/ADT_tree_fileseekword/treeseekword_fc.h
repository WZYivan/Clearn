#include "treeseekword_def.h"

#ifndef TREE_FC_H_
#define TREE_FC_H_

#define _clear_str()   while(getchar() !='\n') continue; 
typedef struct 
{
    TRNODE *parent;
    TRNODE *child;
} PAIR;
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
static bool toright(const ITEM *i1,const ITEM *i2);
static bool toleft(const ITEM *i1,const ITEM *i2);
static void addnode(TRNODE *nwenode,TRNODE *root);
static TRNODE *makenode(const ITEM *pi);
static void deletenode(TRNODE **ptr);
static void inorder(const TRNODE *root,void (*fc)(ITEM item));
static PAIR seekitem(const ITEM *pi,const TREE *ptree);

static bool toright(const ITEM *i1,const ITEM *i2)
{
    int comp1;
    if((comp1=strcmp(i1->word,i2->word))>0) return true;
    else return false;
}

static bool toleft(const ITEM *i1,const ITEM *i2)
{
    int comp1;
    if((comp1=strcmp(i1->word,i2->word))<0) return true;
    else return false;
}

static TRNODE *makenode(const ITEM *pi)
{
    TRNODE *pnew;
    pnew=(TRNODE *)malloc(sizeof(TRNODE));
    if(pnew!=NULL)
    {
        pnew->item=*pi;
        pnew->left=NULL;
        pnew->right=NULL;   
    }
    return pnew;
}

static void deletenode(TRNODE **ptr)
{
    TRNODE *temp;
    if((*ptr)->left==NULL)
    {
        temp=*ptr;
        *ptr=(*ptr)->right;
        free(temp);
    }
    else if((*ptr)->right==NULL)
    {
        temp=*ptr;
        *ptr=(*ptr)->left;
        free(temp);
    }
    else{
        for(temp=(*ptr)->left;temp->left!=NULL;temp=temp->right)
            continue;
        temp->right=(*ptr)->right;
        temp=*ptr;
        *ptr=(*ptr)->left;
        free(temp);
    }
}

static void addnode(TRNODE *newnode,TRNODE *root)
{
    if(toleft(&newnode->item,&root->item))
    {
        if(root->left==NULL)
            root->left=newnode;
        else addnode(newnode,root->left);
    }
    else if(toright(&newnode->item,&root->item))
    {
        if(root->right==NULL)
            root->right=newnode;
        else addnode(newnode,root->right);
    }
    else{
        fprintf(stderr,"add onde err!\n");
        exit(2);
    }
}

static PAIR seekitem(const ITEM *pi,const TREE *ptree)
{
    PAIR look;
    look.parent=NULL;
    look.child=ptree->root;

    if(look.child==NULL)
        return look;
    while(look.child!=NULL)
    {
        if(toleft(pi,&(look.child->item)))
        {
            look.parent=look.child;
            look.child=look.child->left;
        }
        else if(toright(pi,&(look.child->item)))
        {
            look.parent=look.child;
            look.child=look.child->right;
        }
        else break;
    }
    return look;
}

static void inorder(const TRNODE *root,void (*fc)(ITEM item))
{
    if(root!=NULL)
    {
        inorder(root->left,fc);
        (*fc)(root->item);
        inorder(root->right,fc);
    }
}

void initialize(TREE *ptree)
{
    ptree->root=NULL;
    ptree->size=0;
}
bool iftreefull(TREE *ptree)
{
    if(ptree->size == MAXITEM)return FULL;
    else return NFULL;
}
bool iftreempty(TREE *ptree)
{
    if(ptree->root==NULL) return EMPTY;
    else return NEMPTY;
}

bool additem(const ITEM *pi,TREE *ptree)
{
    TRNODE *pnew;
    PAIR look;

    if(iftreefull(ptree)==FULL) return ADDFAL;
    if((look=seekitem(pi,ptree)).child!=NULL)
    {
        look.child->item.times++;
        return ADDSUC;
    }
    pnew=makenode(pi);
    if(pnew==NULL)
    {
        fprintf(stderr,"no memory for node\n");
        exit(1);
    }
    ptree->size++;
    if(ptree->root==NULL)
        ptree->root=pnew;
    else 
        addnode(pnew,ptree->root);
    return ADDSUC;
}

bool deleteitem(const ITEM *pi,TREE *ptree)
{
    PAIR look;
    look=seekitem(pi,ptree);
    if(look.child==NULL)
        return DELFAL;
    if(look.parent==NULL) deletenode(&ptree->root);
    else if(look.parent->left==look.child)
        deletenode(&look.parent->left);
    else deletenode(&look.parent->right);
    ptree->size--;
    return DELSUC;
}

bool intree(const TREE *ptree,const ITEM *pi)
{
    return (seekitem(pi,ptree).child==NULL) ? IN : NIN;
}

int countitem(const TREE *ptree)
{
    return ptree->size;
}

void traverse(const TREE *ptree,void (*fc)(TREE *ptree))
{
    if(ptree!=NULL)
        inorder(ptree->root,fc);
}
#endif