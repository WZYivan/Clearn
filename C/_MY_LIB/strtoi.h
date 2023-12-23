#ifndef STRTOI_H_
#define STRTOI_H_
//function strtoi get a pointer to string and return sum of every char multipy 97('a' in UTF-8)
#ifdef _INC_STRING//#include<string.h>
int strtoi(char *str)
{
    int counter,i,j;
    for(i=0 , j = strlen(str) , counter = -j*97; i < j ; i++)
        counter+=*(str+i);
    return counter;
}
#endif

#ifndef _INC_STRING
int getlen(char *str)
{
    int j = 0;
    for(int i=0;*(str+i)!='\0';++i) 
        ++j;
    return j;
}
int strtoi(char *str)
{
    int counter,i,j;
    for(i=0 , j = getlen(str) , counter = -j*97; i < j ; i++)
        counter+=(int)*(str+i);
    return counter;
}
#endif

#endif 