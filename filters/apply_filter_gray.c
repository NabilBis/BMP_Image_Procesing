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


void applyFilterGray(char* file, int *filterMatrix, int width, int height, double coefficient, char* filterName){
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
    unsigned char *arrPixel;
    unsigned char tmpPixel;
    unsigned char gray_byte;
    int filterWidth, filterHeight, filterMid;
    
    filterWidth = filterHeight = 0;
    filterMid = width/2;
    
    arrPixel = malloc(9*sizeof(unsigned char));
    
    imageSi = infoHeader.width*infoHeader.height;
    fileSi = imageSi + header.dataOffset;
    
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
    editFourBytes(opn, &reservedHeaderBytes);
    editFourBytes(opn, &(infoHeader.xPixelsPerM));
    editFourBytes(opn, &(infoHeader.yPixelsPerM));
    editFourBytes(opn, (int*)&(infoHeader.colorUsed));
    editFourBytes(opn, (int*)&(infoHeader.importantColors));
    
    
    fillColorPalette(opn);
    
    for(int i=0; i<infoHeader.width; i++){
        for(int j=0; j<infoHeader.height; j++){
            if(i==0 || j==0 || i==(infoHeader.width-1) || j==(infoHeader.height-1))
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
    }
     ////////////// MEMORY LEAKS
//    free(arrPixel);
    close(opn);
}
