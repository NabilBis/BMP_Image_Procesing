#include "cluster.h"

int existsInArray(unsigned char *tab, unsigned char num, int size)
{
    for(int u=0; u<size; u++)
        if(*(tab+u)==num)
            return 1;
    
    return 0;
}


unsigned char* rando(int size)
{
    unsigned char *rands = malloc(sizeof(char)*size);
    
    srand(time(NULL));
    for(int t=0; t<size; t++)
    {
        do{
            *(rands+t) = (unsigned char)(rand()%255);
        }while(existsInArray(rands, rand(), t+1));
    }
    
    return rands;
}
