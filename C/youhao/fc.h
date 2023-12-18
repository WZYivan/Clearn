#include<stdio.h>
#include<ctype.h>

static int mode=0;
static double distance=0;
static double vol=0;

void *get_mode(int mode);
void *get_info(void);
void *show_info(void);