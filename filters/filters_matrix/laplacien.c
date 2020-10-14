#include "../filters.h"

int* lapla()///// coefficient = 1
{
    int *filter = malloc(9*sizeof(int));
    
    *(filter+0) = 0;
    *(filter+1) = -1;
    *(filter+2) = 0;
    *(filter+3) = -1;
    *(filter+4) = 4;
    *(filter+5) = -1;
    *(filter+6) = 0;
    *(filter+7) = -1;
    *(filter+8) = 0;
    
    return filter;
}
