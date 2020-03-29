#include "filters.h"

int* sobel() ///// coefficient = 1
{
    int *filter = malloc(9*sizeof(int));
    
    *(filter+0) = -1;
    *(filter+1) = 0;
    *(filter+2) = 1;
    *(filter+3) = -2;
    *(filter+4) = 0;
    *(filter+5) = 2;
    *(filter+6) = -1;
    *(filter+7) = 0;
    *(filter+8) = 1;
    
    return filter;
}
