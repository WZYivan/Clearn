#include "list_def.h"
#include "list_fc.h"

int main(void)
{
    _LIST list;
    _ITEM tem;

    _initialize(&list);//初始化
    if(_iflistfull(&list) == FULL)//检测内存
    {
        fputs("no memory for list",stderr);
        exit(1);
    }

    puts("enter the first item:");
    while((s_gets(tem.title,TLEN) != NULL) 
        && (tem.title)[0] != '\0')//安全输入
    {
        puts("enter its score <0-10>:");
        while(scanf("%d",&tem.score) != 1)
        {
            fputs("error input\n",stderr);
            _clear_str()
        }
        _clear_str();
        if(_additem(&tem,&list) == ADDFAILURE)//添加项目
        {
            fputs("allot memory error\n",stderr);
            break;
        }
        if(_iflistfull(&list) == FULL) 
        {
            fputs("no memory for list\n",stderr);
            break;
        }
        puts("enter next item.title(enpty line to quit):");    
    }

    if(_iflistempty == _EMPTY) //检测是否有项目
        fputs("no item input\n",stderr);
    else
    {
        printf("here show your list\n");
        _do_to_list(&list,_show_list);//链表行为
    }

    _empty_list(&list);

    puts("done");
    return 0;
}