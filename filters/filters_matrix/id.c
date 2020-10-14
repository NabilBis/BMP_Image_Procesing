#include "../filters.h"


int* idd() ///// coefficient = 1
{
    int *filter = malloc(25*sizeof(int));
    
    *(filter+0) = 0;
    *(filter+1) = 0;
    *(filter+2) = 0;
    *(filter+3) = 0;
    *(filter+4) = 0;
    *(filter+5) = 0;
    *(filter+6) = 0;
    *(filter+7) = 0;
    *(filter+8) = 0;
    *(filter+9) = 0;
    *(filter+10) = 0;
    *(filter+11) = 0;
    
    *(filter+12) = 1;
    
    *(filter+13) = 0;
    *(filter+14) = 0;
    *(filter+15) = 0;
    *(filter+16) = 0;
    *(filter+17) = 0;
    *(filter+18) = 0;
    *(filter+19) = 0;
    *(filter+20) = 0;
    *(filter+21) = 0;
    *(filter+22) = 0;
    *(filter+23) = 0;
    *(filter+24) = 0;
    
    return filter;
}
