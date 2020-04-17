#include "filters.h"

int* rotation() ///// coefficient = 1
{
    int *filter = malloc(4*sizeof(int));
    
    *(filter+0) = 0;
    *(filter+1) = 1;
    *(filter+2) = -1;
    *(filter+3) = 0;
    
    return filter;
}
