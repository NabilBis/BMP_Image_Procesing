#include "cluster.h"

int existsInArray(double *tab, double num, int size)
{
    for(int u=0; u<size; u++)
        if(*(tab+u)==num)
            return 1;
    
    return 0;
}


//double* random(int size)
//{
//    double *randoms = malloc(sizeof(double)*size);
//    
//    for(int t=0; t<size; t++)
//    {
//        
//    }
//    
//    return randoms;
//}


int main(int args, char** argv)
{
    printf("Random number %d\n", rand());
    return 0;
}
