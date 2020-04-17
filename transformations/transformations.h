#ifndef transformations_h
#define transformations_h

#include "../global.h"
void to_bmp_iv4(char* file);
void scale_x2(char* file);
void colorToGray(char* file);
void rgbSplit(char* file);
void fillColorPalette(int image);
#endif
