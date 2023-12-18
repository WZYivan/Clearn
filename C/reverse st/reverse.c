#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define STRLEN 512

int main(void)
{
    char str[STRLEN];
    char *pr,*sp;                                       //双指针，一个检索空格，一个打印
    printf("enter sentence:");
    fgets(str,STRLEN,stdin);
    for(sp=str+strlen(str)-1;sp!=str;sp--)
        if(*sp==' ' || (sp-1)==str)
        {
            for(pr=((sp-1)==str)? (sp-1):(sp+1) ;!isspace(*pr);pr++)           
                putchar(*pr);
            if(*sp==' ')
                putchar(*sp);
        }                                
    return 0; 
}