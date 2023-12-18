#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define NAME 41
#define BUFFER_SIZE 512

int main(void)
{
    FILE *fp;
    char ch;
    int count=0;
    char file[NAME]="sou.txt",buff[BUFFER_SIZE];
    
    
    if((fp=fopen(file,"r+"))==NULL)
    {
        printf("open %s error!",file);
        exit(EXIT_FAILURE);
    }
    while((ch=getc(fp))!=EOF)
    {   
        buff[count++]=toupper(ch);        
    }
    printf("%s",buff);
    fseek(fp,0,SEEK_SET);
    for(count=0;count<strlen(buff);count++)
    {        
        putc(buff[count],fp);
    }
    fclose(fp);
    return 0;
}