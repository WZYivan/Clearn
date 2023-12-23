#include "hashtable.h"
#include "hashmap_fc.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char a[]="wzy";
    HASHNODE root[10];
    HASHNODE *node = MakeNode(a, 10);
    Initialize_s(root, 10);
    HashAdd(node, root);
    HashDelet(root,Strtohash(a, 10));
    return 0;
}