#include "helpingMethods.h"

void bmpInfoHeader(int fileDescriptor,int *increment,struct BMPINFOHEADER* infoHeader){
    

    lseek(fileDescriptor,14, SEEK_SET); // positionne the cursor on the 14th position
    
    infoHeader->infoHeaderSize = fourBytesToDecimal(fileDescriptor);
    (*increment)+=4;
    infoHeader->width = fourBytesToDecimal(fileDescriptor);
    (*increment)+=4;
    infoHeader->height = (int)fourBytesToDecimal(fileDescriptor);
    (*increment)+=4;
    infoHeader->planes = twoBytesToDecimal(fileDescriptor);
    (*increment)+=2;
    infoHeader->bitsPerPixel = twoBytesToDecimal(fileDescriptor);
    (*increment)+=2;
    infoHeader->compression = fourBytesToDecimal(fileDescriptor);
    (*increment)+=4;
    infoHeader->imageSize = fourBytesToDecimal(fileDescriptor);
    (*increment)+=4;
    infoHeader->xPixelsPerM = fourBytesToDecimal(fileDescriptor);
    (*increment)+=4;
    infoHeader->yPixelsPerM = fourBytesToDecimal(fileDescriptor);
    (*increment)+=4;
    infoHeader->colorUsed = fourBytesToDecimal(fileDescriptor);
    (*increment)+=4;
    infoHeader->importantColors = fourBytesToDecimal(fileDescriptor);
    (*increment)+=4;
}

