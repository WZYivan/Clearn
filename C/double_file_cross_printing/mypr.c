#include<stdio.h>
#include<stdlib.h>
#define FNAM 41

static char buf1,buf2;
static int count=0;

void *pr(FILE *tar,FILE *f1,FILE *f2);
int input_er(char file[FNAM]);

int main(void)
{   
    FILE *fa,*fb,*fo;
    char f1[FNAM],f2[FNAM],f3[FNAM]="output.txt";

    printf("Usage-file file:");
    scanf("%s %s",f1,f2);

    while((fa=fopen(f1,"r+"))==NULL)
        input_er(f1);
    while((fb=fopen(f2,"r+"))==NULL)
        input_er(f2);
    while((fo=fopen(f3,"w+"))==NULL)
        input_er(f3);

    pr(fo,fa,fb);

    fclose(fa);
    fclose(fb);
    fclose(fo);
    return 0;
}

void *pr(FILE *tar,FILE *f1,FILE *f2)
{
    while((buf1=getc(f1))!='\n' && buf1 != EOF)
        fputc(buf1,tar);
    if(buf1 == '\n')            //
        fputc('\n',tar);        //删去此模块，将无视file1的换行
    if(count==0 && (buf1 == EOF || buf2 == EOF))
        putc('\n',tar),count++;

    while((buf2=getc(f2))!='\n' && buf2 != EOF)
        fputc(buf2,tar);
    if(buf2 == '\n')
        fputc('\n',tar);
    if(count==0 && (buf1 == EOF || buf2 == EOF))
        putc('\n',tar),count++;

    if(buf1==EOF && buf2==EOF)
        return NULL;

    pr(tar,f1,f2);
}

int input_er(char file[FNAM])//检测文件打开，若失败，重新输入文件名
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