#include "../filters.h"

int* edgeDetection()
{
    int *filter = malloc(9*sizeof(int));
    
    *(filter+0) = 1;
    *(filter+1) = 0;
    *(filter+2) = -1;
    *(filter+3) = 1;
    *(filter+4) = 0;
    *(filter+5) = -1;
    *(filter+6) = 1;
    *(filter+7) = 0;
    *(filter+8) = -1;
    
    return filter;
}
