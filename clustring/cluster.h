#ifndef cluster_h
#define cluster_h

#include "../global.h"

unsigned char* rando(int size);
int absolute(int num);
char euclidean(char *vectorOne, char *vectorTwo, int vectorSize);
unsigned int manhattan(unsigned char* vectorOne, unsigned char* vectorTwo, int vectorSize);
double cosineDis(int dimension, double* x, double* y);

double poww(double number, double n);

//////
double gaussian_kernel(int point);
//////



void char_QuickSort(unsigned char *arr,int low, int high);


////////// CLUSTRING METHODS
void k_means(unsigned char* data, int dataSize, int means, unsigned char* centroids, int max_iterations, int* point_mapping, unsigned int* avg_dists, int* cluster_members_count);

void gaussian_mean_shift(unsigned char* data, int dataSize, unsigned char* clus, unsigned char *modes, int window);

void dbscan(unsigned char* data, int dataSize, int radius, int min_points, unsigned char* pixel_array_256);
///////// APPLICTIONS
void apply_k(char* file, int means_size, int max_iteration);
void apply_GMS(char* file, int window);
void apply_DBSCAN(char* file, int radius, int min_points);


////////////////////// DBSCAN
int __dbscan_radius__;
int __dbscan_min_points__;


struct NODE
{
    unsigned char point;
    struct NODE* leftNode;
    struct NODE* rightNode;
};

struct CLUSTER
{
    unsigned char center;
    unsigned char radius;
    
    struct CLUSTER *left;
    struct CLUSTER *right;
};
#endif
