#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void)
{
    int count[10]={0,0,0,0,0,0,0,0,0,0};
    srand((unsigned int) time(0));
    for(int i=0;i<1000;i++)
        count[rand()%10]++;
    for(int j=0;j<10;j++)
        {
            printf("%d\t",count[j]);
            if(j==4)
                putchar('\n');
        }
    return 0;
}