#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define FNAM 41

int main(void)
{
    FILE *fp;
    int input;
    char name[FNAM];
    char ch;

    printf("enter  file name:");
    scanf("%s",name);
    if((fp=fopen(name,"r+"))!=NULL)
    {
        printf("enter (int)set poision(q to break):");
        while(scanf("%ld",&input)==1)
        {
            printf("done\n");
            fseek(fp,(input-1)*sizeof(char),SEEK_CUR);
            while((ch=getc(fp))!='\n'&& ch!=EOF)
                putchar(ch);
            putchar('\n');
            rewind(fp);
            printf("enter (int)set poision(q to break):");
        }
    }    
    else
        printf("open %s error",name);
    return 0;
}