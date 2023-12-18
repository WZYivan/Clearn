#include "treeseekword_def.h"
#include "treeseekword_fc.h"
#include<ctype.h>

#define show_menu()\
    printf("a)show all words and times\n");\
    printf("b)seek word for its times\n");\
    printf("c)quitn\n");\

static _CHOICE get_choice(void)
{
    char tem;
    while(!isalpha(tem=getchar()))
        continue;
    tem=(_CHOICE)(int)((tem>99||tem<97)? 'a':tem);
    return tem;
}
static void showitem(ITEM *pi)
{
    printf("%s appear %d times\n",pi->word,pi->times);
}

int main(void)
{
    TREE tree;   
    ITEM tem;
    FILE *sou;
    _CHOICE ch;
    char word[SLEN];

    puts("enter soufile:");
    s_gets(word,SLEN);
    if((sou=fopen(word,"r+"))!=NULL)
    {
        while(fscanf(sou,"%s",tem.word)==1)
        {
            if(!isalpha(tem.word[0])) continue;
            if(!isalpha(tem.word[strlen(tem.word)-1]))
                tem.word[strlen(tem.word)-1]='\0';
            tem.times=1;
            additem(&tem,&tree);
        }
    }
    else fprintf(stderr,"open %s error",word);

    fclose(sou);
    printf("open file and creat tree over,do choice\n");
    show_menu();
    while((ch=get_choice())!=c)
    {
        switch(ch){
            case a:
                traverse(&tree,showitem);
                break;
            case b:
                
                break;
            default:
                fprintf(stderr,"choice error\n");
                break;
        }
    }
    puts("quit");
    return 0;
}