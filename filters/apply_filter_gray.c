#include "filters.h"

unsigned char gray_filter(unsigned char *pixels, int *filterMatrix, int width, int height, double coefficient)
{
    int newPixel = 0;

    for(int w=0; w<width; w++)
    {
        for(int h=0; h<height; h++)
        {
            newPixel += (*(pixels + w*width + h) * *(filterMatrix+w*width + h));
        }
    }
    

    return newPixel / coefficient;
}


void applyFilterGray(char* file, int *filterMatrix, int width, int height, double coefficient, char* filterName)
{
    extern struct BMPHeader header;
    extern struct BMPINFOHEADER infoHeader;
    extern unsigned char  *grayImagePixels;
    short bitPerPixel = 8;
    int reservedHeaderBytes = 0;
    int dataOff = 1078; // to fix the data offset to 1078(because there is a color palette for the gray image
    int cuarenta = 40; // to fix the infoHeaders size to 40
    char *imageCopy;
    int imageSi;
    int fileSi;
    int palette_size = 1024;
    unsigned char *arrPixel;
    unsigned char tmpPixel;
    unsigned char gray_byte;
    int filterWidth, filterHeight, filterMid;
    int i,j;
    
    filterWidth = filterHeight = 0;
    filterMid = width/2;
    
    arrPixel = malloc(width*height*sizeof(unsigned char));
    
    imageSi = infoHeader.width*infoHeader.height;
    fileSi = imageSi + 54 + palette_size; //// Why 54 : to force the version
    
    concactStr(substractExtension(file), filterName, &imageCopy);
    concactStr(imageCopy, ".bmp", &imageCopy);
    
    int opn = open(imageCopy, O_CREAT | O_RDWR,0644);
    

//    free(imageCopy);
    
    if(opn<1){
        printf("Couldnt read nor create file %s\n", file);
        return;
    }
    
    
    lseek(opn, 0, SEEK_SET);
    
    ///copy header
    editByte(opn, &(header.signature[0]));
    editByte(opn, &(header.signature[1]));
    editFourBytes(opn, &fileSi);
    editFourBytes(opn, &reservedHeaderBytes);
    editFourBytes(opn, &dataOff);
    
    
    //copy infoHeader
    editFourBytes(opn, &cuarenta);
    editFourBytes(opn, (int*)&(infoHeader.width));
    editFourBytes(opn, (int*)&(infoHeader.height));
    editTwoBytes(opn, (short*)&(infoHeader.planes));
    editTwoBytes(opn, &bitPerPixel);
    editFourBytes(opn, (int*)&(infoHeader.compression));
    editFourBytes(opn, &imageSi);
    editFourBytes(opn, &(infoHeader.xPixelsPerM));
    editFourBytes(opn, &(infoHeader.yPixelsPerM));
    editFourBytes(opn, (int*)&(infoHeader.colorUsed));
    editFourBytes(opn, (int*)&(infoHeader.importantColors));
    
    
    fillColorPalette(opn);
    
    for( i=0; i<infoHeader.height; i++)
    {
        for( j=0; j<infoHeader.width; j++)
        {
            if(i<filterMid || j<filterMid || i>=(infoHeader.height-filterMid) || j>=(infoHeader.width-filterMid))
            {
                editByte(opn, (char *)&*(grayImagePixels + i*infoHeader.width + j));
            } else {
                
                for(int w=0; w < width; w++)
                {
                    if(filterWidth==width){
                        filterWidth=0;
                    }
                    for(int h=0; h < height; h++)
                    {
                        if(filterHeight==height){
                            filterHeight=0;
                        }
                        *(arrPixel + w*width + h) = *(grayImagePixels + (i-filterWidth-width+1+filterMid)*infoHeader.width + (j-filterHeight-height+1+filterMid));
                        filterHeight++;
                    }
                    filterWidth++;
                }
                
                tmpPixel = gray_filter(arrPixel, filterMatrix, width, height, coefficient);

                editByte(opn, (char *)&tmpPixel);
            }
        }
        
        for(int p=0; p<(infoHeader.width*3)%4; p++)
        {
            editByte(opn, (char*)&reservedHeaderBytes);
        }
    }

     ////////////// MEMORY LEAKS
//    free(arrPixel);
    close(opn);
}
