#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUFSIZ 512

static char tar;
static int count;

int main(int argc,char *argv[])
{
    if(strlen(argv[1])!=1)
    {
        printf("input error,usage:tar_char file_name(null to stdin)");
        exit(EXIT_FAILURE);
    }
    tar=(char)*argv[1];
    if(argc==2)
    {
        char buf[BUFSIZ];
        fgets(buf,BUFSIZ,stdin);
        for(int i=0;i<strlen(buf);i++)
            if(buf[i]==tar)
                count++;
        printf("%d",count);
    }
    else if(argc>2)
    {
        char buf;
        FILE *fp;
        for(int i=2;i<argc;i++)
        {
            if((fp=fopen(argv[i],"r+"))==NULL)
            {
                printf("open %s error",argv[i]);
                exit(EXIT_FAILURE);
            }
            while((buf=getc(fp))!=EOF)
                if(buf==tar)
                    count++;
            printf("%s:%d\n",argv[i],count);
        }       
    }
    else 
    {
        printf("input error,usage:tar_char file_name(null to stdin)");
    }
    return 0;
}