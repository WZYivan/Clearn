#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define MAXTOKENS 100
#define MAXTOKENLEN 64

enum type_tag{ IDENTIFIFER, QUALIFIER, TYPE};

struct token{
    char type;
    char string[MAXTOKENLEN];
};

int top = -1;
struct token stack[MAXTOKENS];
struct token this;

#define pop stack[top--]
#define push(s) stack[++top] = s

enum type_tag classify_string(void)//has change
{
    char *s = this.string;
    int i=0;
    int j=strlen(s);
    int c=-j*('a');
    while(i<j) c+=s[i++];
    switch(c)//case = (int)(every char of str)-strlen*('a')
    {
        case 66://const
            strcpy( s , "read_only");
        case 88://volatile
            return QUALIFIER;
        case 46://void
        case 26://char
        case 52://signed
        case 85://unsigned
        case 75://short
        case 40://int
        case 44://long
        case 49://float & enum
        case 53://double
        case 95://struct
        case 68://union
            return TYPE;
        default:
            return IDENTIFIFER;   
    }
}

int main(void)//for test
{
    char s[] = "void";
    int i=0;
    int j=strlen(s);
    int c=-j*('a');
    while(i<j) c+=s[i++];
    switch(c)//case = (int)(every char of str)-strlen*('a')
    {
        case 66://const
            strcpy( s , "read_only");
        case 88://volatile
            return QUALIFIER;
        case 46://void
        case 26://char
        case 52://signed
        case 85://unsigned
        case 75://short
        case 40://int
        case 44://long
        case 49://float & enum
        case 53://double
        case 95://struct
        case 68://union
            printf("done");
        default:
            return IDENTIFIFER;   
    }
}