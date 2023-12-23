#include<stdio.h>
#include<string.h>
#include"strtoi.h"
int main(void)
{
    char list[14][9]={"const","volatile","void","char","signed","unsigned","short","int","long","float","double","struct","union","enum"};
    for(int k=0,s;k<14;++k)
    {
        int counter=0,i,j;
        for(i=0 , j = strlen(list[k]) , counter = -j*97; i < j ; i++)
        {
            counter+=(int)*(list[k]+i);
            
        }    
        printf("%s:%d\n",list[k],strtoi(list[k])); 
    }
        
    return 0;
}