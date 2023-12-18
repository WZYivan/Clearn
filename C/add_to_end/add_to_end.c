#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define BUFFER_SIZE 512
#define FNAME 81

static char buff[BUFFER_SIZE];

void *add(FILE* sou,FILE* tar);

int main(int argc,char *argv[])
{   
    char sou[FNAME]=argv[1],tar[FNAME]=argv[2];
    FILE *fs,*fa;                                       //creat

    if(argc!=3)
    {
        fprintf(stderr,"input error,Usage:file fil_sou fil_tar!");
        exit(EXIT_FAILURE);
    }                                                    //intput error
    if((fs=fopen(sou,"r"))==NULL)
    {
        fprintf(stderr,"open %s error",argv[1]);
        exit(EXIT_FAILURE);
    }                                                    //sou error
    if((fa=fopen(tar,"a+"))==NULL)
    {
        fprintf(stderr,"open %s error",argv[2]);
        exit(EXIT_FAILURE);
    }                                                    //tar error
    if((setvbuf(fs,buff,_IOFBF,BUFFER_SIZE*sizeof(char)))!=0)
    {
        fprintf(stderr,"creat buffer error");
        exit(EXIT_FAILURE);
    }                                                       //buffer error

    add(fs,fa);

    fclose(fs);
    fclose(fa);

    return 0;
}

void *add(FILE* sou,FILE* tar)
{   
    size_t bytes;
    while((bytes=fread(buff,sizeof(char),BUFFER_SIZE,sou)>0))
        fwrite(buff,sizeof(char),strlen(buff),tar);
    return tar;
}                                                        //core