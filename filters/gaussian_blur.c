#include "filters.h"


int* gaussian_blur()///// coefficient 1/273
{
    int* filter = malloc(25*sizeof(int));
    
    *(filter+0) = 1;
    *(filter+1) = 4;
    *(filter+2) = 7;
    *(filter+3) = 4;
    *(filter+4) = 1;
    *(filter+5) = 4;
    *(filter+6) = 16;
    *(filter+7) = 26;
    *(filter+8) = 16;
    *(filter+9) = 4;
    *(filter+10) = 7;
    *(filter+11) = 26;
    *(filter+12) = 41;
    *(filter+13) = 26;
    *(filter+14) = 7;
    *(filter+15) = 4;
    *(filter+16) = 16;
    *(filter+17) = 26;
    *(filter+18) = 16;
    *(filter+19) = 4;
    *(filter+20) = 1;
    *(filter+21) = 4;
    *(filter+22) = 7;
    *(filter+23) = 4;
    *(filter+24) = 1;
    
    return filter;
}
