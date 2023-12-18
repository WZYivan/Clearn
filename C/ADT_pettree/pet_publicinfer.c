#include"tree.h"
#include"tree_pet.h"

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

char *GetType(void)
{
    char tem[SLEN];
    s_gets(tem,SLEN);
    return tem;
}

int main(void)
{
    char word[SLEN];
    FILE *pf;

    printf("enter sou file:");
    s_gets(word,SLEN);
    if((pf=fopen(word,"r+"))==NULL)
    {
        fprintf(stderr,"open %s error",word);
        exit(3);
    }

    
}