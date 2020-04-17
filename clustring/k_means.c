#include "cluster.h"


///////// How to adapt k-means to a given scenario
///// By editing:   1. Distance function (fitness function)
/////               2. Stop condition (recursion)
/////               3. Average computation methodS (Must be other ways to define new centroids in each iteration)

unsigned int dist = 0;
int cluster_index=0;

void k_means(unsigned char* data, int dataSize, int means, unsigned char* centroids, int max_iterations, int* point_mapping, unsigned int* avg_dists, int* cluster_members_count)
{
    extern unsigned int dist;
    extern int cluster_index;
    int divided_dist;
    
    if(max_iterations==0)
        return ;
    
    printf(" Iteration n %d\n", max_iterations);
    
    for(int e=0; e<means; e++)
    {
        *(avg_dists+e) = *(cluster_members_count+e)= 0;
    }
    for(int y=0; y<dataSize; y++)
    {
        dist = manhattan(data+y, centroids, 1);

        for(int q=0; q<means; q++)
        {
            if(dist > manhattan((data+y), (centroids+q), 1))
            {
                dist = manhattan((data+y), (centroids+q), 1);
                cluster_index = q;
            }
        }
        
         *(point_mapping+y) = cluster_index;
        (*(avg_dists + cluster_index)) += dist;
        (*(cluster_members_count + cluster_index))++;
        
        cluster_index = 0;
    }

    for(int m=0; m<means; m++)
    {
        if( *(cluster_members_count+m)==0)
        {
            *(centroids+m)= 255;//*(rando(1));
            continue;
        }
        
        divided_dist = *(avg_dists+m) / (*(cluster_members_count+m));
        *(centroids+m) = (unsigned char)divided_dist;
    }

    
    k_means(data, dataSize, means, centroids, max_iterations-1, point_mapping, avg_dists, cluster_members_count);
}

//
//int main(int args, char** argv)
//{
//    int means_size=5;
//    int* mapping = malloc(sizeof(int)*30);//// could be unsigned char
//    unsigned char* centroids = malloc(sizeof(char)*means_size);
//    unsigned char* dat = malloc(sizeof(char)*30);
//    unsigned int* avg_dists = malloc(sizeof(int)*means_size);
//    int* cluster_members_count = malloc(sizeof(int)*means_size);
//    
//    centroids = rando(means_size);
//    
//    for(int e=0; e<means_size; e++)
//    {
//        *(avg_dists+e) = *(cluster_members_count+e)= 1;
//    }
//    
//    *(dat+0) = 192;
//    *(dat+1) = 143;
//    *(dat+2) = 112;
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
////    printf("Char = %d, unsigned char = %d\n", l, absolute(l));
////    double tab[30] = {12, 43, 2, 65, 634, 89, 1020, 32, 43, 3,
////                    302, 120, 27, 6, 166, 101, 77, 555, 18, 20,
////        99, 456, 387, 51, 9, 11, 444, 800, 65, 10 };
//    
//    k_means(dat, 10, means_size, centroids, 22, mapping, avg_dists, cluster_members_count);
//    
////    for (int k=0; k<10; k++) {
////        printf("Mapping %d with %d\n", *(dat+k), *(mapping+k)+1);
////    }
////    for(int l=0; l<5; l++)
////    {
////        printf("Cluster %d's centoid = %d\n", l+1, *(centroids+l));
////    }
////    printf("\n-------\n");
//    for(int t=0; t<means_size; t++)
//    {
//        printf("Avg dist = %d, count = %d , centroid ?= %d \n", *(avg_dists+t), *(cluster_members_count+t), *(centroids+t));
//    }
////    printf("\n");
////    for(int u=0; u<30; u++)
////    {
////        printf("%d \n", *(mapping+u));
////    }
//    return 0;
//}
