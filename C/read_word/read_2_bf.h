#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static int word;
static int length;

char ** get_word(int word)
{
    printf("how many words you enter?");
    scanf("%d",&word);
    char **psi=(char**)malloc(word*sizeof(char*));
    for(int i=0;i<word;i++)
    {   
        char temp[100];
        scanf("%s",temp);
        length=strlen(temp);
        char *str=(char *)malloc(word*length);
        strcpy(str,temp);
        *(psi+i)=str;
    }
    return psi;
}

void *pr(char **psi)
{
    for(int i=0;i<word;i++)
    {
        printf("%s\t",*(psi+i));
    }
    free(psi);
    return NULL;
}