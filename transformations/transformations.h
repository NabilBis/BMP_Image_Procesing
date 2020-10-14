#ifndef transformations_h
#define transformations_h

#include "../global.h"
void to_bmp_iv4(char* file);
void scale_x2(char* file);
void colorToGray(char* file);
void rgbSplit(char* file);
void fillColorPalette(int image);
void rotate_90(char* file);
void cut(char* file, int start_x, int start_y, int end_x, int end_y);
void mask(char* file, char* mask, int start_x, int start_y);
#endif
