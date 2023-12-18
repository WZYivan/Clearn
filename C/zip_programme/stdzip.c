#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define FNAME 41

static char buf;

void *zip(FILE *fs,FILE *fa);
int input_er(char file[FNAME]);

int main(void)
{
    FILE* fs,*fa;
    char sou[FNAME],tar[FNAME]="output.txt";

    printf("Usage:sou_file:");
    scanf("%s",sou);

    while((fs=fopen(sou,"r+"))==NULL)
        input_er(sou);
    while((fa=fopen(tar,"w+"))==NULL)
        input_er(tar);

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
    while((buf=getc(fs))!=EOF)
    {
        fseek(fs,2*sizeof(char),SEEK_CUR);
        putc(buf,fa);
    }
}