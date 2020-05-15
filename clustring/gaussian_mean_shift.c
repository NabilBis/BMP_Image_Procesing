#include "cluster.h"



double eucl(double *vectorOne,double *vectorTwo, int vectorSize)
{
    double distance = 0;
    
    for(int v=0; v<vectorSize; v++)
        distance += poww(*(vectorOne + v) - *(vectorTwo + v), 2);
    
    return sqrt(distance);
}


////////////// https://towardsdatascience.com/gaussian-mixture-models-explained-6986aaf5a95
/////////////  http://www.cs.cmu.edu/~aarti/SMLRG/miguel_slides.pdf
/////////// The kernel used in this algo is the GAUSSIAN KERNEL, many other kernel are present
void gaussian_mean_shift(unsigned char* data, int dataSize, unsigned char* clus, unsigned char *modes, int window)
{
    double pivot, numerateur, denominateur, unknown, dist, num;
    double condition = 0.001;
    int index;
    
    printf("Clusters dimension  : %d \n", 256/window+1);
    


    for(int y=0; y<dataSize; y++)
    {
        pivot = (double)(*(data +y));
        
        do {
            for(int l=0; l<dataSize; l++)
            {
                num = *(data +l);
                dist = eucl(&pivot, &num, 1);
                numerateur = gaussian_kernel(dist/window);
                unknown += numerateur * (*(data +l));
                denominateur += numerateur;
            }
           
            pivot = unknown/denominateur;
            
            index = (int)(pivot/window);
            if(*(modes+ index) !=0)
            {
                *(modes+ index) = (*(modes+ index) + pivot)/2;
            } else {
                *(modes+ index) = (unsigned char)pivot;
            }
        } while (pivot < condition);
        
//        printf("Index = %d\n", index);
        printf("%d\n", y);
        *(clus + y) = (unsigned char)index;
        dist = numerateur = denominateur = unknown = 0;
    }
    
        printf("\n");

}


//
//int main(int args, char** argv)
//{
//    unsigned char* dat = malloc(sizeof(char)*30);
//    unsigned char* clus = malloc(sizeof(char)*30);
//    int window = 40;
//    unsigned char *modes = malloc((256/window + 1)*sizeof(char));
//
//    for(int w=0; w<=256/window; w++)
//    {
//        *(modes+w) = 0;
//    }
//    
//    *(dat+0) = 14;
//    *(dat+1) = 143;
//    *(dat+2) = 222;
//    *(dat+3) = 165;
//    *(dat+4) = 134;
//    *(dat+5) = 89;
//    *(dat+6) = 202;
//    *(dat+7) = 32;
//    *(dat+8) = 43;
//    *(dat+9) = 3;
//    *(dat+10) = 177;
//    *(dat+11) = 120;
//    *(dat+12) = 27;
//    *(dat+13) = 6;
//    *(dat+14) = 166;
//    *(dat+15) = 101;
//    *(dat+16) = 77;
//    *(dat+17) = 89;
//    *(dat+18) = 18;
//    *(dat+19) = 20;
//    *(dat+20) = 99;
//    *(dat+21) = 156;
//    *(dat+22) = 7;
//    *(dat+23) = 51;
//    *(dat+24) = 9;
//    *(dat+25) = 11;
//    *(dat+26) = 233;
//    *(dat+27) = 220;
//    *(dat+28) = 65;
//    *(dat+29) = 1;
//    
//    
//    gaussian_mean_shift(dat, 30, clus, modes, window);
//    
//   
//    for(int u=0; u<30; u++)
//    {
//        printf("%d -> %d\n", *(dat+u), *(modes +(int)(*(clus+u))));
//    }
//
//    return 0;
//}

