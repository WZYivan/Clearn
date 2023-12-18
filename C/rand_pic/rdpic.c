#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define LEN 30
#define WID 20

static char ch[10]={'!','@','#','$','%','^','&','*','(',')'};

void *rand_ct(int *sou);
void *read_pic(int *sou);

int main(void)
{
    int pic[LEN][WID];
    rand_ct((int *)pic);
    read_pic((int *)pic);
    return 0;
}

void *rand_ct(int *sou)
{
    int *ct=sou;
    srand((unsigned long) time(0));
    for(int i=0;i<LEN*WID;i++)
        *(ct+i)=rand()%10;
    return sou;
}

void *read_pic(int *sou)
{
    int *pr=sou;
    for(int i=0;i<LEN;i++)
    {
        for(int j=0;j<WID;j++)
        {
            switch (*(pr+i+j))
            {
            case 0:
                putchar('!');
                break;
            
            case 1:
                putchar('@');
                break;

            case 2:
                putchar('#');
                break;

            case 3:
                putchar('$');
                break;

            case 4:
                putchar('%');
                break;

            case 5:
                putchar('^');
                break;

            case 6:
                putchar('^');
                break;

            case 7:
                putchar('&');
                break;

            case 8:
                putchar('(');
                break;

            case 9:
                putchar(')');
                break;
            }
        }
        putchar('\n');
    } 
    return sou;   
}