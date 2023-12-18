#include<stdio.h>
#include<stdlib.h>
#include "jishi.h"

static char tower[3]={'A','B','C'};
static int sum='A'+'B'+'C';
static unsigned long long count=0;

void hanoi(int n,char st,char ed);

int main(void)
{
    int level;
    do{
        printf("enter level if hanoi tower:");
        if(scanf("%d",&level)!=1)
        {
            if(getchar()!='q')
            {
                printf("input error,retry!\n");
                continue;
            }  
            else 
            {
                printf("quit");
                exit(EXIT_SUCCESS);
            }
        }
        time_st();
        hanoi(level,tower[0],tower[2]);
        time_ed();
        time_show(); 
        count=0;
        putchar('\n');
    }while(getchar()!='q');       
    return 0;
}

void hanoi(int n,char st,char ed)
{
    if(n>0)
    {
    hanoi(n-1,st,(char)(sum-st-ed));
    count++;
    printf("[%d]%d:%c->%c\t",count,n,st,ed);
    if(count%6==5)
        putchar('\n');
    hanoi(n-1,(char)(sum-st-ed),ed);
    }      
}
    