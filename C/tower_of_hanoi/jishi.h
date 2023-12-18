#include<time.h>

clock_t TIME_ST_;
clock_t TIME_ED_;

#define time_st() TIME_ST_=clock()
#define time_ed() TIME_ED_=clock() 
#define time_show() printf("\nuse time:%lf",((double)(TIME_ED_-TIME_ST_)/CLOCKS_PER_SEC))