#include "cluster.h"

//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>

double poow(double number, int n)
{
    if(n<2)
        return number;
    
    return number*poow(number, n-1);
}


double absolute(double num)
{
    double tab[2] = {num, -num};
    
    return tab[num<0];
}


double euclidean(double *vectorOne, double *vectorTwo, int vectorSize)
{
    double distance = 0;
    
    for(int v=0; v<vectorSize; v++)
    {
        distance += poow(*(vectorOne + v) - *(vectorTwo + v), 2);
    }
    
    return sqrt(distance);
}

double manhattan(double *vectorOne, double *vectorTwo, int vectorSize)
{
    double distance = 0;
    
    for(int v=0; v<vectorSize; v++)
    {
        distance += absolute(*(vectorOne + v) - *(vectorTwo + v));
    }
    
    return distance;
}



//int main(int args, char** argv)
//{
//    double num;
//    
////    double i=-4;
//    
//    double *vect1, *vect2;
//    
//    vect1 = malloc(2*sizeof(double));
//    vect2 = malloc(2*sizeof(double));
//    
//    *(vect1 + 0) = 2;
//    *(vect1 + 1) = 1;
//    
//    *(vect2 + 0) = 3;
//    *(vect2 + 1) = 2;
//    
//    num = manhattan(vect1, vect2, 2);
//    
//    printf("g = %f\n", num);
////    printf("%f \n", absolute(i));
//    
//    return 0;
//}
