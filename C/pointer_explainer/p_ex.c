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

enum type_tag classify_string(void)//has change in line 48 and line 23 in (file)p_ec_change.c
{
    char *s = this.string;
    if(!strcmp( s , "const" ))
    {
        strcpy( s , "read_only");
        return QUALIFIER;
    }    
    if(!strcmp( s , "volatile" )) return QUALIFIER;
    if(!strcmp( s , "void" )) return TYPE;
    if(!strcmp( s , "char" )) return TYPE;
    if(!strcmp( s , "signed" )) return TYPE;
    if(!strcmp( s , "unsigned" )) return TYPE;
    if(!strcmp( s , "short" )) return TYPE;
    if(!strcmp( s , "int" )) return TYPE;
    if(!strcmp( s , "long" )) return TYPE;
    if(!strcmp( s , "float" )) return TYPE;
    if(!strcmp( s , "double" )) return TYPE;
    if(!strcmp( s , "struct" )) return TYPE;
    if(!strcmp( s , "union" )) return TYPE;
    if(!strcmp( s , "enum" )) return TYPE;
    return IDENTIFIFER;
}

/*
#include "strtoi.h"
enum type_tag classify_string(void)//has change
{
    char *s = this.string;
    int sig = strtoi(s);
    switch(sig)//case = (int)(every char of str)-strlen*('a')
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
*/

void gettoken(void)
{
    char *p = this.string;

    while((*p = getchar()) == ' ')  ;

    if(isalnum(*p))//char can be print
    {
        while(isalnum(*++p = getchar()))    ;           
        ungetc(*p,stdin);
        *p = '\0';
        this.type=classify_string();
        return;
    }
    if(*p == '*')
    {
        strcpy(this.string,"pointer to ");
        this.type = '*';
        return;
    }
    this.string[1] = '\0';
    this.type = *p;
    return;
}

void read_to_first_identifer(void)
{
    gettoken();
    while(this.type != IDENTIFIFER)
    {
        push(this);
        gettoken();
    }
    printf("%s is ",this.string);
    gettoken();
}

void deal_with_arrays(void)
{
    while(this.type == '[')
    {
        printf("array ");
        gettoken();
        if(isdigit(this.string[0]))
        {
            printf("0..%d ",atoi(this.string)-1);
            gettoken();
        }   
        gettoken();
        printf("of ");
    }
}
void deal_with_function_args(void)
{
    while(this.type != ')')
        gettoken();
    gettoken();
    printf("function returnung ");
}

void deal_with_pointers(void)
{
    while(stack[top].type == '*')
        printf("%s",pop.string);
}

void deal_with_declarator(void)
{
    switch (this.type)
    {
    case '[':   
        deal_with_arrays(); 
        break;
    case '(':   
        deal_with_function_args();
    }

    deal_with_pointers();

    while(top >= 0)
    {
        if(stack[top].type == '(')
        {
            pop;
            gettoken();
            deal_with_declarator();  
        }
        else{
            printf("%s",pop.string);
        }
    }
}

int main(void)
{
    read_to_first_identifer();
    deal_with_declarator();
    printf("\n");
    return 0;
}