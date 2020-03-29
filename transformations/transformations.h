#ifndef transformations_h
#define transformations_h

#include "../global.h"
void duplicateFile(char* file);
void convertImage(char* file);
void scale_x2(char* file);
void colorToGray(char* file);
void rgbSplit(char* file);
void fillColorPalette(int image);
#endif
