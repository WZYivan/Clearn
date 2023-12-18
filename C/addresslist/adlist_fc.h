#ifndef ADLIST_H
#define ADLIST_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include"list.h"


char *s_gets(char *st,int siz)
{
    char *flag = fgets(st,siz,stdin);
    char *find;

    if(flag != NULL)
    {
        if((find = strchr(flag,'\n')) != NULL)
            *find = '\0';
        else{
            while(getchar()!='\n')
                continue;
        }
    }

    return flag;
}

static ITEM *Makeitem(ITEM *item);
//static LOOKITEM Sekpitem(ITEM *pitem,INDEX *root);
static bool Doforward(char *dest,char *sou);
static bool Dobackwark(char *dest,char *sou);


typedef struct _lookindex
{
    INDEX *parent;
    INDEX *child;      
}  LOOKINDEX;
extern void Initialize(INDEX *root)
{
    root->flag='@';
    root->rootitem=NULL;
    root->backward=NULL;
   
    for(char ch='A';ch<='Z';ch++)
    {
        INDEX *pnew;
        if(( pnew = (INDEX *) malloc(sizeof(INDEX)) ) !=NULL)
        {
            root->forward=pnew;

            pnew->flag=ch;
            pnew->backward=root;
            pnew->forward=NULL;
            pnew->rootitem=NULL;

            root=pnew;
        }
        else{
            fprintf(stderr,"no memery for list");
            exit(1);
        }
    }

    printf("initialize succesfully\n");
}
/*
*
*
*
*/
static ITEM *Makeitem(ITEM *item)
{
    ITEM *pnew;
    if((pnew =(ITEM *)malloc(sizeof(ITEM))) != NULL)
    {
        pnew->number=item->number;
        strcpy(pnew->name,item->name);
    }
    return pnew;
}

static bool Doforward(char *dest,char *sou)
{
    if(strcmp(dest,sou))    return true;
    return false;
}
static bool Dobackwark(char *dest,char *sou)
{
    if(strcmp(dest,sou))    return false;
    return true;
}

static ITEM *Sekpitem(ITEM *pitem,INDEX *root)
{

    for(char ch=toupper(pitem->name[0]);
    ch!=root->flag ; root=root->forward)
        ;

    if(root->rootitem==NULL)//添加根项目
    {
        root->rootitem=pitem;
        return pitem;
    }    
    else{ 
        ITEM *tarp;
        for(tarp=root->rootitem ; tarp->forward!=NULL ; tarp=tarp->forward)
        {
            if(Doforward(pitem->name,tarp->name))
            {
                if(Dobackwark(pitem->name,tarp->forward->name))
                    return tarp;//常规添加
                continue;
            }
            if(strcmp(pitem->name,tarp->name)==0)
                return tarp;//项目已存在
        }
        return tarp;//表尾     
    }
}
/*
*
*/
extern bool Additem(ITEM *pitem,INDEX *root)
{
    ITEM *tarp;
    ITEM *pnew;

    if((pnew=Makeitem(pitem))!=NULL)
    { 
        tarp=Sekpitem(pnew,root);
        if(strcmp(tarp->name,pnew->name)==0 && tarp != pnew)//新增项目名已存在
        {
            printf("already exit!\n");
            printf("q to quit and c to change:");
            while(getchar()!='\n')
                continue;
            char ch[2];
            s_gets(ch,2);
            switch (tolower(ch[0]))
            {
            case 'c':
                tarp->number=pnew->number;
                printf("change over\n");
                return true;

            case 'q':
                printf("quit\n");
                return true;
            
            default:
                fprintf(stderr,"invalid input,quit\n");
                break;
            }
        }
        else if(tarp == pnew)//添加根项目
        {
            pnew->backward=NULL;
            pnew->forward=NULL;
        }
        else{//添加新项目
            if(tarp->forward!=NULL) 
            {
                tarp->forward->backward=pnew;           
            }    
            pnew->forward=tarp->forward;
            tarp->forward=pnew;
            pnew->backward=tarp;
        }
        printf("add over\n");
        return true;
    }
    else 
    {
        fprintf(stderr,"no memory for item");
        return false;
    }
}

extern bool Deletitem(ITEM *pitem,INDEX *root)
{
    ITEM *tarp;
    tarp=Sekpitem(pitem,root);
    if(strcmp(tarp->name,pitem->name)==0)
    {
        if(tarp->backward==NULL)
        {
            for(char ch=toupper(pitem->name[0]) ; ch!=root->flag ; root=root->forward)
                ;
            root->rootitem=tarp->forward;
            tarp->forward->backward=NULL;
            free(tarp);
        }
        else{
            tarp->backward->forward=tarp->forward;
            tarp->forward->backward=tarp->backward;
            free(tarp);
        }
    }
    else{
        fprintf(stderr,"no such file");
        return false;
    }
}
/*
*
*
*
*/
extern void Showlist(INDEX *plist)
{
    printf("{@}______\n");
    for(plist=plist->forward;plist!=NULL;plist=plist->forward)
    {
        printf("\t[%c]______\n",plist->flag);
        bool flag=true;
        if(plist->rootitem!=NULL)
            for(ITEM *pi=plist->rootitem;pi!=NULL  ;pi=pi->forward)
            {
                printf("\t\t|%s:%lld\n",pi->name,pi->number);
                if(!flag)
                    break;
            }
    }
}

extern bool Deletlist(INDEX *root)
{
    while(root!=NULL)
    {
        INDEX *tem1=root;
        ITEM *pi=root->rootitem;
        while(pi!=NULL)
        {
            ITEM *tem2=pi;
            pi=pi->forward;
            free(tem2);
        }
        root=root->forward;
        free(tem1);
    }
}  
/*
*
*
*
*/
extern void Traverse(INDEX *root , void (*pf)(ITEM *pitem))
{
    for(;root!=NULL;root=root->forward)
    {
        for(ITEM *pi=root->rootitem;pi!=NULL;pi=pi->forward)
        {
            (*pf)(pi);
        }
    }
}
/*
*
*/

//void (*pf)(ITEM *pitem)

/*
*
*
*
*/
#endif