#include<stdio.h>
#include<stdlib.h>

static int size;
static int value=0;

int *make_arr(int size,int n)
{
    int *tar=NULL;
    tar=(int *)malloc(size *sizeof(int));
    for(int i=0;i<size;i++)
        tar[i]=n;
    return tar;
}

void *show_arr(int *ar)
{
    for(int i=0;i<size;i++)
        printf("%d\t",ar[i]);
    free(ar);
    return NULL;
}