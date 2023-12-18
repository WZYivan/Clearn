#include<stdio.h>
#include<stdlib.h>
#include<time.h>

static int dices=0;
static int sides=0;
static int sets=0;
static int sum=0;
static int total_sum=0;

void *dice(int dices,int sides,int sets)
{
    srand((unsigned int) time(0));
    for(int i=sets;i>0;i--,sum=0)
    {
        for(int j=dices;j>0;j--)
        {
            sum+=rand()%sides+1;
        }
        printf("%d\t",sum);
        if((sets-i+1)%6==5)
            putchar('\n');
        total_sum+=sum;
    }
    printf("\nhere are %d sets of %d %d-sides throws:%d\n",sets,dices,sides,total_sum);
    total_sum=0;
    return NULL; 
} 

void *get_info(void)
{
    int flag=0;
    while (flag!=3)
    {
        printf("enter the num of sets(q to quit):");
        flag+=scanf("%d",&sets);
        if(flag == 0)
        {
            if(getchar()=='q')
                exit(EXIT_SUCCESS);
            else{
                printf("input error,ertry!\n");
            while(getchar()!='\n')
                continue;
            }
        }          
        printf("how many dice and sides?:");
        flag+=scanf("%d %d",&dices,&sides);
        if(flag!=3)
        {
            printf("input error,ertry!\n");
            while(getchar()!='\n')
                continue; 
        }           
    }
    return NULL;
}