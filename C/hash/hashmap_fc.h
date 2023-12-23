#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

extern int Strtohash(char *str, int size)
{
    int len,code;
    len = strlen(str);
    code = 0;
    if(len == 1) return (str[0]-'a'+1)%size;
    for(int i = 0 ; i <= len/2 ; ++i)
        code += (str[i]%str[len-i-1] + str[i]%len);
    return (code + len)%size;
}

extern void Initialize_s(HASHNODE *root, int size)
{
    for(int i = 0; i < size; ++i)
    {
        (root + i)->code = i;
        strcpy((root + i)->str , "\0");
    }
}

extern HASHNODE *MakeNode(char *str, int size)
{
    HASHNODE *hash=(HASHNODE *)malloc(sizeof(HASHNODE));
    if(hash != NULL)
    {
        hash->code=Strtohash(str, size);
        strcpy(hash->str,str);
    }
    return hash;
}

extern bool HashAdd(HASHNODE *phash, HASHNODE *root)
{
    if((root+phash->code)->str[0] == '\0')
        if(strcpy((root+phash->code)->str,phash->str)) return true;
    else return false;
}

extern bool HashSek(HASHNODE *root , char *str, int size)
{
    if(!strcmp(str, (root + Strtohash(str, size))->str))  return true;
    else return false;
}