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


void apply_filter_on_matrix(int opn, int *filterMatrix, int width, int height, double coefficient)
{
    int reservedHeaderBytes = 0;
    int filterWidth, filterHeight, filterMid;
    unsigned char tmpPixel;
    unsigned char *arrPixel;
    int i,j;
    
    filterWidth = filterHeight = 0;
    filterMid = width/2;
    
    arrPixel = malloc(width*height*sizeof(unsigned char));

    
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
}

void apply_gray_filter(char* file, int *filter_matrix, int filter_width, int filter_height, double coefficient, char* filterName)
{
    char *imageCopy;

    concactStr(substractExtension(file), filterName, &imageCopy);
    concactStr(imageCopy, ".bmp", &imageCopy);
    
    int opn = open(imageCopy, O_CREAT | O_RDWR,0644);
    
    if(opn<1){
        printf("Couldnt read nor create file %s\n", file);
        return;
    }
    
    write_bmp4_gray_headers(opn);
    
    apply_filter_on_matrix(opn, filter_matrix, filter_width, filter_height, coefficient);

     ////////////// MEMORY LEAKS
//    free(arrPixel);
    close(opn);
}
