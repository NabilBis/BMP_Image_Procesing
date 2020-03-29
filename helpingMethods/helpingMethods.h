
//If a header file happens to be included twice, the compiler will process its contents twice and it will result in an error. The standard way to prevent this is to enclose the entire real contents of the file in a conditional  site:   https://www.tutorialspoint.com/cprogramming/c_header_files.htm
#ifndef helpingMethods_h
#define helpingMethods_h

//#include <stdlib.h>
//#include <sys/types.h>
//#include <unistd.h>
//#include <fcntl.h>
#include "../global.h"

enum DECIMALTYPE {CHAR_TYPE, SHORT_TYPE, INT_TYPE};

unsigned int bitsToDecimal(char *,enum DECIMALTYPE);

void concactStr(char *,const char *,char **);

char* bitsString(int);

char* substractExtension(char* fileName);

unsigned int fourBytesToDecimal(int fileDescriptor);

unsigned short twoBytesToDecimal(int fileDescriptor);

void editByte(int fileDescriptor,char *newValue);

void editTwoBytes(int fileDescriptor,short *newValue);

void editFourBytes(int fileDescriptor,int *newValue);

//void fillPixel(int fileDsc, struct PIXEL *image, unsigned int imageSize,int dataOffset);
//
//void fillGrayPixel(int fileDsc, unsigned char *image, unsigned int imageSize,int dataOffset);
//void editPixel(int fileDescriptor,struct PIXEL pixel);


#endif
