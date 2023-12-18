#include<stdlib.h>
#include<stdio.h>

#define FNAM 512

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

void *num_zip(FILE *fs,FILE *fa,int num)//压缩文件，每num个字节保存头一个
{
    char buf;
    while((buf=getc(fs))!=EOF)
    {
        fseek(fs,num*sizeof(char),SEEK_CUR);
        putc(buf,fa);
    }
}