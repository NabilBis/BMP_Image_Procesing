#include "transformations.h"



void fillColorPalette(int image){
    
    char *colorBuffer= malloc(sizeof(char));
    size_t readedColor, writeColor;
    int colorPaletteSize = 0;
    
    int opnPalette = open("/Users/macos/Desktop/Home/programacion/proyecto/C/my_C_LIBRARY/bmpImage/transformations/colorPalette", O_RDONLY,0644);
    
    if(opnPalette<1){
        printf("Couldnt read nor create file \"ColorPalette\" \n");
        return;
    }

    lseek(opnPalette, 0, SEEK_SET);
    lseek(image, 54, SEEK_SET);
    
    while (colorPaletteSize<1024) {
        
        readedColor = read(opnPalette, colorBuffer,1);
        if(readedColor<1){
            printf("Error occured while copying color palette values\n");
            return; }

        writeColor = write(image, colorBuffer,1);
        if(writeColor<1){
            printf("Error occured while copying color palette values\n");
            return;
        }
        colorPaletteSize++;
    }
//    free(colorBuffer);
}


////// Redondance
unsigned char toGrayFunc(struct PIXEL pixel){
    
    return (0.3*pixel.red + 0.59*pixel.green + 0.11*pixel.blue);
}





void colorToGray(char* file){
    extern struct BMPHeader header;
    extern struct BMPINFOHEADER infoHeader;
    extern struct PIXEL *imagePixels;
    short bitPerPixel = 8;
    int reservedHeaderBytes = 0;
    int dataOff = 1078; // to fix the data offset to 1078(because there is a color palette for the gray image
    int cuarenta = 40; // to fix the infoHeaders size to 40
    char *imageCopy;
    int imageSi;
    int fileSi;
    struct PIXEL neutralPixel = {.blue = 255, .green = 255, .red = 255 };
    
    imageSi = infoHeader.width*infoHeader.height;
    fileSi = imageSi + header.dataOffset;
    
    concactStr(substractExtension(file), "_gray.bmp", &imageCopy);
    
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
    
    
    ///////
    fillColorPalette(opn);
    
    //Convert to gray image
    for(int pixelIterator=0; pixelIterator<(infoHeader.imageSize/3);pixelIterator++){
        char grayByte = (char)toGrayFunc(*(imagePixels+pixelIterator));
        
//        printf("%u\n",toGrayFunc(*(imagePixels+pixelIterator)));
        
        editByte(opn, &grayByte);
    }
    
    close(opn);
}






