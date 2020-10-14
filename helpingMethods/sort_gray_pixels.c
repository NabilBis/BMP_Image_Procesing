#include "helpingMethods.h"

void sort_gray_pixels(unsigned char *gray_sorted_pixels, int *histogram, int image_size)
{
    int limit;
    int index;
    int k;
    
    k = limit = index = 0;
    
    for(index=0; index<256; index++)
    {
        while (limit < *(histogram+index)) {
            *(gray_sorted_pixels + k) = index;
            limit++;
            k++;
        }
        limit = 0;
    }
}
