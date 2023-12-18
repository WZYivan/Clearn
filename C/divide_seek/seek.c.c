#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>

int comp(const void *a1,const void *a2)
{
    const int *b1=(const int *) a1;
    const int *b2=(const int *) a2;

    if(*b1 > *b2)
        return 1;
    else if (*b1 == *b2)
        return 0;
    else return -1;
}

bool bfind(const int *arr,int siz,int tar)
{
    int low=0,high=siz-1,cur;
    while(low <= high)
    {
        cur=(low+high)/2;
        if(tar == arr[cur]) return true;
        if(tar > arr[cur])
            low=cur+1;
        else high=cur-1;
        if(cur == low) return false;
    }
    return false;
}

int main(void)
{
    int arr[100];
    int input,result;

    srand(time(0));
    for(int i=0,tem=0;i<100;i++)
        arr[i]=((tem=rand())>0)? tem:-tem;
    
    puts("un sorted arr:");
    for(int i=0;i<100;i++)
        printf("%d",arr[i]);
    putchar('\n');

    qsort(arr,100,sizeof(int),comp);
    puts("sorted arr:");
    for(int i=0;i<100;i++)
        printf("%d",arr[i]);
    putchar('\n');

    while((scanf("%d",&input))==1)
    {
        if(bfind(arr,100,input)) printf("Y\n");
        else printf("N\n");
    }
    return 0;
}