#include <stdio.h>
#include <string.h>

#define STRL 101

int main(void) 
{
    char str1[STRL],str2[STRL];
    int min = 1;

    printf("enter str1:");
    fgets(str1,STRL,stdin);
    printf("enter str2:");
    fgets(str2,STRL,stdin);

    for(int count = 0 ; count < min ; count++)
    {
        int i = 0 , j = 0 , k = 0 ;
        for(int L1 = strlen(str1);i < ((min > 2) ? L1 : L1-1) ; i++ , k++)
        {
            if(str1[i] == str2[j])
            {
                int tem = i,L2=strlen(str2);
                for (  ;j < (L2-1) && str1[tem] == str2[j]; tem++,j++)
                    ;
                if( j == L2 - 1 )
                    i += L2 - 1,min++;
                j = 0;
            }
            str1[k] = str1[i] ;
        }
        while(k < i)
            str1[k++] = '\0';printf("\n%s",str1); 
    }
    
    return 0;
}