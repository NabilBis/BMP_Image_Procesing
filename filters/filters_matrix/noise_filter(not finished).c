#include "../filters.h"


int dynamic_filter(unsigned char pixel, int index_i, int index_j)
{
    int operation;
    for(int k=0; k<3; k++)
    {
        for(int l=0; l<3; l++)
        {
            operation += (int)*(pixel +);
        }
    }
    return 0;
}



void noise_filter(char* file)
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

    
    imageSi = infoHeader.width*infoHeader.height;
    fileSi = imageSi + 54 + palette_size; //// Why 54 : to force the version
    
    concactStr(substractExtension(file), "_noise", &imageCopy);
    concactStr(imageCopy, ".bmp", &imageCopy);
    
    int opn = open(imageCopy, O_CREAT | O_RDWR,0644);
    
    
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
    
    for(int i=0; i<infoHeader.height; i++)
    {
        for(int j=0; j<infoHeader.width; j++)
        {
            if(i==0 || j==0 || i==(infoHeader.height-1) || j==(infoHeader.width-1))
            {
              editByte(opn, (char *)&*(grayImagePixels + i*infoHeader.width + j));
            
            } else {
                //////// CONDITION
              if(dynamic_filter(i, j))
              {
                  editByte(opn, (char *)&*(grayImagePixels + i*infoHeader.width + j));
              } else {
                  editByte(opn, (char*)&reservedHeaderBytes);
              }
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
