#include"fc.h"

int main(void)
{
    printf("enter 0 to USA_std,and 1 to EUR_std(-1 to quit):");
    scanf("%d",&mode);//extern mode
    while(mode>=0)
    {
        get_mode(mode);
        get_info();
        show_info();
        printf("enter 0 to USA_std,and 1 to EUR_std(-1 to quit):");
        scanf("%d",&mode);
    }
    puts("quit");
}

void *get_mode(int mode)
{
    if(mode>2)
        mode=1,puts("input overflow,set mode 1");
    if(mode==1)
        puts("USA_std used");
    else if(mode==0)
        puts("EUR_std used");
    return NULL;
}
void *get_info(void)
{
    while (mode==0)
    {
        printf("enter distance in mile and vol in gallon:");
        if(scanf("%lf %lf",&distance,&vol)!=2)
        {
            printf("input error,enter to retry\n");
            while(getchar()!='\n')
                continue;
            continue;
        }
        break;
    }
    while (mode==1)
    {
        printf("enter distance in km and vol in L:");
        if(scanf("%lf %lf",&distance,&vol)!=2)
        {
            printf("input error,enter to retry");
            while(getchar()!='\n')
                continue;
            continue;
        }
        break;
    }
    return NULL;
}
void *show_info(void)
{
    if(mode==0)
        printf("fuel=%7.2lf\n",distance/vol);
    else if(mode==1)
        printf("fuel=%7.2lf\n",vol/(distance/100));
        return NULL;
}