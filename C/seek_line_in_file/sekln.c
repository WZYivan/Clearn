#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STRLEN 512

int main(int argc,char *argv[])
{
    FILE *fp;  
    char buf[STRLEN],ch;
    char *ln=buf,*tar=argv[1];
    
    strcpy(tar,argv[1]);
    if(argc<3)
    {
        printf("input error,usage:tar_str sou_file");
        exit(EXIT_FAILURE);
    }
    else if(argc>2)
        for(int i=2;i<argc;i++)
        {
            if((fp=fopen(argv[i],"r+"))==NULL)
            {
                printf("open %s error",argv[i]);
                exit(EXIT_FAILURE);
            }

            fseek(fp,1,SEEK_END);
            putc('\n',fp);
            rewind(fp);

            while((ch=getc(fp))!=EOF)           
            {
                if(ch!='\n')               
                    *(ln++)=ch;
                else 
                {
                    *(ln)='\0';
                    ln=buf;
                }                      
                if(ch == '\n' && strstr(buf,tar)!=NULL)                     
                    printf("%s\n",buf);                                                                                      
            }                                          //获取行输入，可以直接用fgets(),获取行
        }   
    return 0;
}