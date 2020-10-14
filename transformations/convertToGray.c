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
    
    while (colorPaletteSize<1024)
    {
        readedColor = read(opnPalette, colorBuffer, 1);
        
        if(readedColor<1)
        {
            printf("Error occured while copying color palette values\n");
            return;
        }

        writeColor = write(image, colorBuffer, 1);
        
        if(writeColor<1)
        {
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


void colorToGray(char* file)
{
    int reservedHeaderBytes = 0;
    char *imageCopy;
    char grayByte;

    
    concactStr(substractExtension(file), "_gray.bmp", &imageCopy);
    
    int opn = open(imageCopy, O_CREAT | O_RDWR,0644);
    
    if(opn<1){
        printf("Couldnt read nor create file %s\n", file);
        return;
    }

    write_bmp4_gray_headers(opn);

    
//    printf("Result = %d\n", (infoHeader.width*3)%4);
    
    for(int h=0; h<infoHeader.height; h++)
    {
        for(int w=0; w<infoHeader.width; w++)
        {
           grayByte = (char)toGrayFunc(*(imagePixels+h*infoHeader.width+w));
           editByte(opn, &grayByte);
        }
        
        for(int p=0; p<(infoHeader.width*3)%4; p++)
        {
            editByte(opn, (char*)&reservedHeaderBytes);
        }
    }
    
    close(opn);
}






