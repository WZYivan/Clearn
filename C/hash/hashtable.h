#ifndef HASHTABLE_H_
#define HASHTABLE_H_ 1

#include <stdbool.h>

#define LEN 64
typedef struct hashnode
{
    int code;
    char str[LEN];
}   HASHNODE;

int Strtohash(char *str, int size);
//string to hash_code

void Initialize_s(HASHNODE *root, int size);
//initialize hashmap
//allot memory already

HASHNODE *MakeNode(char *str, int size);
bool HashAdd(HASHNODE *phash, HASHNODE *root);
//add hashnode to hashmap
//if full, failed, return false
#define HashDelet(root,code) ((root)+(code))->str[0] = '\0'
//delet hashnode by code

bool HashSek(HASHNODE *root , char *str , int size);
//seek string in hashmap, return hash_code or -1 for "not found"

#define HashClear(root, code) memset( (((root) + (code))->str) , '\0', LEN*sizeof(char))
//set all string NULL

#endif