#include "../cluster.h"




////////// Redondance
unsigned char poow(unsigned char number, unsigned char n)
{
    if(n<2)
        return number;
    
    return number*poow(number, n-1);
}


int absolute(int num)
{
    int tab[2] = {num, -num};
    
    return tab[num<0];
}

int substraction(unsigned char a, unsigned char b)
{
    int aa = a;
    int bb = b;
    
    return aa-bb;
}


char euclidean(char *vectorOne,char *vectorTwo, int vectorSize)
{
    int distance = 0;

    for(int v=0; v<vectorSize; v++)
        distance += poow(*(vectorOne + v) - *(vectorTwo + v), 2);
    
    return sqrt(distance);
}

unsigned int manhattan(unsigned char* vectorOne, unsigned char* vectorTwo, int vectorSize)
{
    unsigned int distance = 0;
    
    for(int v=0; v<vectorSize; v++)
    {
        distance += absolute(substraction(*(vectorOne + v), *(vectorTwo + v)));
    }
    
    return distance;
}

//Cosine distance for positive numbers
double cosineDis(int dimension, double* x, double* y)
{
    double numerator;
    double x_2, y_2;
    
    numerator = x_2 = y_2 = 0;
    
    for(int q=0; q<dimension; q++)
    {
        numerator += *(x+q) * (*(y+q));
        x_2 += pow(*(x+q), 2);
        y_2 += pow(*(y+q), 2);
    }
    
    return numerator/(sqrt(x_2)*sqrt(y_2));
    
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
