#include "filters.h"


struct PIXEL filter(struct PIXEL *pixels, int *filterMatrix, int width, int height, double coefficient)
{
    struct PIXEL new;
    int red, blue, green;
    
    red = blue = green = 0;
    
    for(int w=0; w<width; w++)
    {
        for(int h=0; h<height; h++)
        {
            red += (*(pixels + w*width + h)).red * *(filterMatrix+w*width + h);
            blue += (*(pixels + w*width + h)).blue * *(filterMatrix+w*width + h);
            green += (*(pixels + w*width + h)).green * *(filterMatrix+w*width + h);
        }
    }
    
    new.red = red / coefficient;
    new.green = green / coefficient;
    new.blue = blue / coefficient;
    
    return new;
}

///////// MUST BE IN EDITS FILE
void editPixel(int opn, struct PIXEL p)
{
      editByte(opn, (char*)&p.blue);
      editByte(opn, (char*)&p.green);
      editByte(opn, (char*)&p.red);
}

void applyFilter(char* file, int *filterMatrix, int width, int height, double coefficient, char* filterName)
{
    extern struct BMPHeader header;
    extern struct BMPINFOHEADER infoHeader;
    extern struct PIXEL *imagePixels;
    struct PIXEL *arrPixel;
    struct PIXEL tmpPixel;
    int reservedHeaderBytes = 0;
    int dataOff = 54;
    int infoSize = 40;
    char *imageCopy;
    int imgSize;
    int fileS;
    int filterWidth, filterHeight, filterMid;
    
    filterWidth = filterHeight = 0;
    filterMid = width/2;
    printf("Filer mid = %d \n\n", filterMid);
    arrPixel = malloc(width*height*sizeof(struct PIXEL));
    
    imgSize = infoHeader.width*3*infoHeader.height;
    fileS = imgSize + header.dataOffset;
    
    concactStr(substractExtension(file), filterName, &imageCopy);
    concactStr(imageCopy, ".bmp", &imageCopy);
    
    int opn = open(imageCopy, O_CREAT | O_RDWR,0644);
    
//    free(imageCopy);
    
    if(opn<1){
        printf("Couldnt read nor create file (apply filter RGB)%s\n", file);
        return;
    }
        
    lseek(opn, 0, SEEK_SET);
    
    ///copy header
    editByte(opn, &(header.signature[0]));
    editByte(opn, &(header.signature[1]));
    editFourBytes(opn, (int*)&(header.fileSize));
    editFourBytes(opn, &reservedHeaderBytes);
    editFourBytes(opn, &dataOff);
    
    
    //copy infoHeader
    editFourBytes(opn, &infoSize);
    editFourBytes(opn, &(infoHeader.width));
    editFourBytes(opn, &(infoHeader.height));
    editTwoBytes(opn, (short*)&(infoHeader.planes));
    editTwoBytes(opn,  (short*)&(infoHeader.bitsPerPixel));
    editFourBytes(opn, (int*)&(infoHeader.compression));
    editFourBytes(opn, (int*)&(infoHeader.imageSize));
    editFourBytes(opn, &(infoHeader.xPixelsPerM));
    editFourBytes(opn, &(infoHeader.yPixelsPerM));
    editFourBytes(opn, (int*)&(infoHeader.colorUsed));
    editFourBytes(opn, (int*)&(infoHeader.importantColors));
 
    
    for(int i=0; i<infoHeader.height; i++)   //// h*width+w
    {
        for(int j=0; j<infoHeader.width; j++)
        {
//            if(i==0 || j==0 || i==(infoHeader.width-1) || j==(infoHeader.height-1))
            if(j<filterMid || i<filterMid || j>=(infoHeader.width-filterMid) || i>=(infoHeader.height-filterMid))
            {
                /////// write pixel
                editPixel(opn, *(imagePixels + j*infoHeader.width + i));
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
*(arrPixel + h*width + w) = *(imagePixels + (i-filterHeight-height+1+filterMid)*infoHeader.width + (j-filterWidth-width+1+filterMid));
                        
                        filterHeight++;
                    }
                    
                    filterWidth++;
                }
                tmpPixel = filter(arrPixel, filterMatrix, width, height, coefficient);
                
                editPixel(opn, tmpPixel);
            }
        }
        //////// Padding h*width+w
        for(int p=0; p<(infoHeader.width%4); p++)
        {
            editByte(opn, (char*)&reservedHeaderBytes);
        }
      }
    
//    free(arrPixel);
    close(opn);
}
