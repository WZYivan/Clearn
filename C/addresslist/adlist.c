#include"list.h"
#include"adlist_fc.h"

void Showchoice(void)
{
    printf("A)Add item\n");
    printf("D)Delete item\n");
    printf("C)Change item\n");
    printf("Q)Quit and delet list\n");
    printf("S)Show list\n");
    printf("H)Help:show choice\n");
    printf("enter choice:");
}

void Getname(char *ch)
{
    printf("enter name:");
    s_gets(ch,NMAX);
}

int main(void)
{
    ITEM *pi;
    INDEX *root=(INDEX *)malloc(sizeof(INDEX));
    Initialize(root);
    Showchoice();

    char ch[NMAX];
    while(s_gets(ch,2)!=NULL)
    {   
        switch (toupper(ch[0]))
        {
        case 'A':
        case 'C':
            Getname(ch);
            pi=(ITEM *)malloc(sizeof(ITEM));
            printf("enter number:\n");
            scanf("%lld",&(pi->number));
            if(pi!=NULL && ch!=NULL && pi->number>0)
            {
                strcpy(pi->name,ch);
                Additem(pi,root);
            }
            free(pi);
            break;
        
        case 'D':
            Getname(ch);
            pi=(ITEM *)malloc(sizeof(ITEM));
            if(pi!=NULL && ch[0]!='\0')
            {
                strcpy(pi->name,ch);
                Deletitem(pi,root);
            }
            free(pi);
            break;

        case 'S':
            Showlist(root);
            break;

        case 'Q':
            Deletlist(root);
            printf("delete over,quit");
            exit(EXIT_SUCCESS);
            break;

        case 'H':
            Showchoice();
            break;
        
        default:
            fprintf(stderr,"inivoda input\n");
            break;
        }
        while(getchar()!='\n')
                continue;
        Showchoice();
    }    
        
    return 0;
}