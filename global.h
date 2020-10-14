#ifndef global_h
#define global_h

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

#include "./helpingMethods/helpingMethods.h"
#include "./filters/filters.h"
#include "./transformations/transformations.h"
#include "./clustring/cluster.h"

struct BMPHeader {
    char signature[2];
    unsigned int fileSize;
    unsigned int dataOffset;
}header;


struct BMPINFOHEADER {
    unsigned int infoHeaderSize;
    int width;
    int height;
    unsigned short planes;
    unsigned short bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    int xPixelsPerM;
    int yPixelsPerM;
    unsigned int colorUsed;
    unsigned int importantColors;
}infoHeader;

struct PIXEL {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
}*imagePixels;

unsigned char  *grayImagePixels;
unsigned char  *gray_image_sorted;/////// WHY NEW ARRAY : the order of the pixels(image) must remain the same.
int *histogram;


void bmpHeader(int fileDescriptor,int *increment,struct BMPHeader* header);
void bmpInfoHeader(int fileDescriptor,int *increment,struct BMPINFOHEADER* infoHeader);



/////// must delete
//void fillGrayPixel(int fileDsc, unsigned char *image, unsigned int imageSize,int dataOffset);

//////////// MUST DELETE TOO
void get_image_pixels(int fileDsc, struct PIXEL *image, unsigned int height, unsigned width, int dataOffset);
void get_gray_pixels(int fileDsc, unsigned char *image, int *histogram, unsigned int height, unsigned width, int dataOffset);

#endif
