#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUFSIZ 512
#define FNAME 41

static char buf[BUFSIZ];

void *zip(FILE *fs,FILE *fa);
int input_er(char file[FNAME]);

int main(void)
{
    FILE* fs,*fa;
    char sou[FNAME],tar[FNAME];

    printf("Usage:sou_file tar_file:");
    scanf("%s %s",sou,tar);

    while((fs=fopen(sou,"r+"))==NULL)
        input_er(sou);
    while((fa=fopen(tar,"w+"))==NULL)
        input_er(tar);
    while((setvbuf(fs,buf,_IOFBF,BUFSIZ*sizeof(char)))!=0)
    {
        fprintf(stderr,"creat buffer error");
        exit(EXIT_FAILURE);
    }

    zip(fs,fa);
    
    fclose(fs);
    fclose(fa);
    return 0;
}

int input_er(char file[FNAME])
{
        fprintf(stderr,"open %s error\n",file);
        while (getchar()!='\n')
            continue;
        printf("q to quit,or re_enter file name(Usage:_file):");
        if(getchar()=='q')
            exit(EXIT_FAILURE);
        else 
            scanf("%s",file);
    return 1;
}

void *zip(FILE *fs,FILE *fa)
{
    while((fread(buf,sizeof(char),BUFSIZ,fs))>0)
        for(int i=0;i<strlen(buf);i++)
            if(i%3==0 && buf[i]!=EOF)
                putc(buf[i],fa);
}