#include "filters.h"

int* identity() ///// coefficient = 1
{
    int *filter = malloc(9*sizeof(int));
    
    *(filter+0) = 0;
    *(filter+1) = 0;
    *(filter+2) = 0;
    *(filter+3) = 0;
    *(filter+4) = 1;
    *(filter+5) = 0;
    *(filter+6) = 0;
    *(filter+7) = 0;
    *(filter+8) = 0;
    
    return filter;
}
