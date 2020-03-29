#include "transformations.h"

void fillRGBColorPalette(int fileDescriptor, int color){
    
    int cero = 0;
    int blue, green, red;
    int limit = 256;
    
    lseek(fileDescriptor, 54, SEEK_SET);
    
    for(int o=0; o<limit; o++){
        
        blue = color == 1 ? o : 0;
        green = color == 2 ? o : 0;
        red = color == 3 ? o : 0;
        
        editByte(fileDescriptor, (char*)&blue);
        editByte(fileDescriptor, (char*)&green);
        editByte(fileDescriptor, (char*)&red);
        editByte(fileDescriptor, (char*)&cero);
    }
}



void rgbSplit(char* file){
    extern struct BMPHeader header;
    extern struct BMPINFOHEADER infoHeader;
    extern struct PIXEL *imagePixels;
    int opnBlue, opnGreen, opnRed;
    short bitPerPixel = 8;
    int reservedHeaderBytes = 0;
    int dataOff = 1078; // to fix the data offset to 1078(because there is a color palette for the gray image
    int cuarenta = 40; // to fix the infoHeaders size to 40
    char *imageGreen;
    char *imageRed;
    char *imageBlue;
    int desciptors[3];
    int imageSi;
    int fileSi;
    struct PIXEL neutralPixel = {.blue = 255, .green = 255, .red = 255 };
    
    imageSi = infoHeader.width*infoHeader.height;
    fileSi = imageSi + header.dataOffset;
    
    concactStr(substractExtension(file), "_blue.bmp", &imageBlue);
    concactStr(substractExtension(file), "_green.bmp", &imageGreen);
    concactStr(substractExtension(file), "_red.bmp", &imageRed);
    
    
    opnBlue = open(imageBlue, O_CREAT | O_RDWR,0644);
    free(imageBlue);
    
    if(opnBlue<1){
        printf("Couldnt read nor create file %s\n", file);
        return;
    }
    
    opnGreen = open(imageGreen, O_CREAT | O_RDWR,0644);
    free(imageGreen);
    
    if(opnGreen<1){
        printf("Couldnt read nor create file %s\n", file);
        return;
    }
    
    opnRed = open(imageRed, O_CREAT | O_RDWR,0644);
    free(imageRed);
    
    if(opnRed<1){
        printf("Couldnt read nor create file %s\n", file);
        return;
    }
    
    desciptors[0] = opnBlue;
    desciptors[1] = opnGreen;
    desciptors[2] = opnRed;

    
    for(int a=0; a<3; a++){
        
        lseek(desciptors[a], 0, SEEK_SET);
        ///copy header
        editByte(desciptors[a], &(header.signature[0]));
        editByte(desciptors[a], &(header.signature[1]));
        editFourBytes(desciptors[a], &fileSi);
        editFourBytes(desciptors[a], &reservedHeaderBytes);
        editFourBytes(desciptors[a], &dataOff);
    
    
        //copy infoHeader
        editFourBytes(desciptors[a], &cuarenta);
        editFourBytes(desciptors[a], (int*)&(infoHeader.width));
        editFourBytes(desciptors[a], (int*)&(infoHeader.height));
        editTwoBytes(desciptors[a], (short*)&(infoHeader.planes));
        editTwoBytes(desciptors[a], &bitPerPixel);
        editFourBytes(desciptors[a], (int*)&(infoHeader.compression));
        editFourBytes(desciptors[a], &reservedHeaderBytes);
        editFourBytes(desciptors[a], &(infoHeader.xPixelsPerM));
        editFourBytes(desciptors[a], &(infoHeader.yPixelsPerM));
        editFourBytes(desciptors[a], (int*)&(infoHeader.colorUsed));
        editFourBytes(desciptors[a], (int*)&(infoHeader.importantColors));
        
        fillRGBColorPalette(desciptors[a], a+1);
    }
    
    for(int pixelIterator=0; pixelIterator<(infoHeader.imageSize/3);pixelIterator++){
        
        editByte(opnBlue, (char*)&((*(imagePixels+pixelIterator)).blue));
        editByte(opnGreen, (char*)&((*(imagePixels+pixelIterator)).green));
        editByte(opnRed, (char*)&((*(imagePixels+pixelIterator)).red));
    }
    
    
    close(opnBlue);
    close(opnGreen);
    close(opnRed);
    
}






