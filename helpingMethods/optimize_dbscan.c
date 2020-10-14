#include "helpingMethods.h"

unsigned char* optimize_dbscan(int *histogram)
{
    unsigned char *sorted_gray_array;
    int hist[256];
    
    int limit;
    int index;
    int k;
    
    k = limit = index = 0;
    
    for(int y=0; y<256; y++)
    {
        
        if( *(histogram + y) > __dbscan_min_points__)
        {
            hist[y] = __dbscan_min_points__;
            __optimized_dbscan_sorted_size__ += __dbscan_min_points__;
        }
        else
        {
            hist[y] = *(histogram + y);
            __optimized_dbscan_sorted_size__ += *(histogram + y);
        }
    }
    
    sorted_gray_array = malloc(sizeof(char)*__optimized_dbscan_sorted_size__);
    

    
    
    
    for(index=0; index<256; index++)
    {
        while (limit < hist[index]) {
            *(sorted_gray_array + k) = index;
            limit++;
            k++;
        }
        limit = 0;
    }
    
    return sorted_gray_array;
            
}
