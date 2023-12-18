#include<stdio.h>
#include<math.h>

#define PI 3.14

#define ra_to_polar(args,argv,X,Y) switch(args)\
    {\
        case 'R':\
            argv=sqrt(((X)*(X))+((Y)*(Y)));\
            break;\
\
        case 'A':\
            argv=(atan2(Y,X)*(180.0/PI));\
            break;\
    }

typedef struct{
    float R;
    float A;
}   _polar;

typedef struct{
    double X;
    double Y;
}   _ra;

_ra ra;
_polar polar;

void get_ra(void)
{
    printf("enter (x,y):( , )\b\b\b\b");
    scanf("%lf %lf",&ra.X,&ra.Y);
}

int main(void)
{
    get_ra();
    ra_to_polar('R',polar.R,ra.X,ra.Y);
    ra_to_polar('A',polar.A,ra.X,ra.Y);
    printf("(%lf,%lf)",polar.A,polar.R);
    return 0;
}