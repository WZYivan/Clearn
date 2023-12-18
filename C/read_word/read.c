#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
    int word,length;
    
    char *str;
    char temp[100];

    printf("how many words you enter?");
    scanf("%d",&word);

    char **psi=(char**)malloc(word*sizeof(char*));

    for(int i=0;i<word;i++)
    {
        scanf("%s",temp);
        length=strlen(temp);
        str=(char *)malloc(length*sizeof(char));
        strcpy(str,temp);
        *(psi+i)=str;
    }
    for(int i=0;i<word;i++)
    {
        printf("%s\t",*(psi+i));
    }
    free(psi);
    return 0;
}