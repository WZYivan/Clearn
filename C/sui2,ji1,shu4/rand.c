#include "rand_fc.h"

int main(int args,char *argv[])
{
    int rand[100];
    for(int i=0;i<100;i++)
    {
        rand[i]=rand_fc(seed);//extern seed
    }
    pr_arr(rand);
    system("pause");
    return 0;
}

extern int rand_fc(int n)
{
    n=n*1103515455+12345;
    seed=n;
    return (n/65536)%32768;
} 

extern void pr_arr(int *rand)
{
    int temp;
    for(int j=0;j<100;j++)//rand[]_key
        for(int k=j+1;k<100;k++)//rand[]_traversal
            if(rand[j]>rand[k])
            {
                temp=rand[j];
                rand[j]=rand[k];
                rand[k]=temp;
            }
    for(int i=0;i<100;i++)
    {
        printf("%d\t",rand[i]);
        if(i % 9==8)
            putchar('\n');
    }    
}