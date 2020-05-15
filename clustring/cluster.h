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

////////// CLUSTRING METHODS
void k_means(unsigned char* data, int dataSize, int means, unsigned char* centroids, int max_iterations, int* point_mapping, unsigned int* avg_dists, int* cluster_members_count);

void gaussian_mean_shift(unsigned char* data, int dataSize, unsigned char* clus, unsigned char *modes, int window);


///////// APPLICTIONS
void apply_k(char* file, int means_size, int max_iteration);
void apply_GMS(char* file, int window);

#endif
