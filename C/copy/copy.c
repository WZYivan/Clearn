#include<stdio.h>
#include<stdlib.h>
#define BUFFER_SIZE 512

int main(int args,char *argv[])
{
    char buf[BUFFER_SIZE];
    FILE *fp_sou,*fp_tar;
    if(args!=3)
    {
        printf("Usage:%s sou_file_name tar_file_name!",argv[0]);
    }
    else 
    {
        if((fp_sou=fopen(argv[1],"rb"))==NULL)
        {
            printf("error,cant open sou_file:%s",argv[1]);
            exit(EXIT_FAILURE);
        }
        if((fp_tar=fopen(argv[2],"wb"))==NULL)
        {
            printf("error,cant open tar_file:%s",argv[2]);
            exit(EXIT_FAILURE);
        }
    }
    size_t bytes;
    while((bytes=fread(buf,sizeof(char),BUFFER_SIZE,fp_sou))>0)
        fwrite(buf,sizeof(char),bytes,fp_tar);
    fclose(fp_sou);
    fclose(fp_tar);
    printf("done\n");
    return 0;
}