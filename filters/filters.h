#ifndef filters_h
#define filters_h

#include "../global.h"
////////// must be in a fliter header

int* laplacien();
int* sobel();
int* lapla();
int* identity();
int* sharpen();
int* edgeDetection();
int* smoothing();
int* idd();
int* rotation();
int* gaussian_blur();

void applyFilter(char* file, int *filterMatrix, int width, int height, double coefficient, char* filterName);

void apply_gray_filter(char* file, int *filterMatrix, int width, int height, double coefficient, char* filterName);

void apply_filter_on_matrix(int opn, int *filterMatrix, int width, int height, double coefficient);
#endif
