#include "cluster.h"


////////////// REDONDANCE
double poww(double number, double n)
{
    if(n<2)
        return number;
    
    return number*poww(number, n-1);
}


//double exponentiel(double x, int accuracy)
//{
//    double a = 1.0;
//    double b = 1.0;
//    double e = 1.0;
//    
//    printf("X = %f\n", x);
//    
//    for(int u=1; u<accuracy; u++)
//    {
//        a*=x;
//        b*=u;
//        
//        e += a/b;
//    }
//    
//    return e;
//}

double gaussian_kernel(int point)
{
    double pi = 22.0/7.0;
//    printf("%f \r", exp(-0.5*poww(point, 2)));
    return exp(-0.5*poww(point, 2));
}



//int main(int args, char** argv)
//{
//    double x = 0.5*25;
//    
//    printf("Program running %f\n", gaussian_kernel(0, 3));
//    
//    return 0;
//}
