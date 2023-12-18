#include "make_arr_bf.h"

int main(void)
{
    int *tar=NULL;
    printf("enter size of arr:");
    scanf("%d",&size);
    printf("enter initialization value:");
    scanf("%d",&value);
    tar=make_arr(size,value);
    show_arr(tar);
    return 0;
}