#include "transformations.h"


void duplicateFile(char* file){
    extern struct BMPHeader header;
    extern struct BMPINFOHEADER infoHeader;
    extern struct PIXEL *imagePixels;
    int reservedHeaderBytes = 0;
    char *imageCopy;
    int ss;
    int fileS;
    
    
    
    
    ss = infoHeader.width*3*infoHeader.height;
    fileS = ss + header.dataOffset;
    concactStr(substractExtension(file), "_copy.bmp", &imageCopy);
    int opn = open(imageCopy, O_CREAT | O_RDWR,0644);
//    free(imageCopy);
    
    if(opn<1){
        printf("Couldnt read nor create file %s\n", file);
        return;
    }
    
    lseek(opn, 0, SEEK_SET);
    
    ///copy header
    editByte(opn,&(header.signature[0]));
    editByte(opn,&(header.signature[1]));
//    editFourBytes(opn,(int*)&(header.fileSize));
    editFourBytes(opn, &fileS);
    editFourBytes(opn, &reservedHeaderBytes);
    editFourBytes(opn, (int*)&(header.dataOffset));
    
    
    //copy infoHeader
    editFourBytes(opn, (int*)&(infoHeader.infoHeaderSize));
    editFourBytes(opn, &(infoHeader.width));
    editFourBytes(opn, &(infoHeader.height));
    editTwoBytes(opn, (short*)&(infoHeader.planes));
    editTwoBytes(opn, (short*)&(infoHeader.bitsPerPixel));
    editFourBytes(opn, (int*)&(infoHeader.compression));
    editFourBytes(opn, &ss);
//    editFourBytes(opn,(int*)&(infoHeader.imageSize));
    editFourBytes(opn, &(infoHeader.xPixelsPerM));
    editFourBytes(opn, &(infoHeader.yPixelsPerM));
    editFourBytes(opn, (int*)&(infoHeader.colorUsed));
    editFourBytes(opn, (int*)&(infoHeader.importantColors));
    
    
    //copy pixels
    printf("\n\nPixels: %d\n\n", infoHeader.imageSize/3);
    for(int pixelIterator=0; pixelIterator<(infoHeader.imageSize/3);pixelIterator++){
        editByte(opn, (char*)&((*(imagePixels+pixelIterator)).blue));
        editByte(opn, (char*)&((*(imagePixels+pixelIterator)).green));
        editByte(opn, (char*)&((*(imagePixels+pixelIterator)).red));
    }
    
}

void convertImage(char* file){
    extern struct BMPHeader header;
    extern struct BMPINFOHEADER infoHeader;
    extern struct PIXEL *imagePixels;
    int reservedHeaderBytes = 0;
    char *imageCopy;
    int dataOff = 54;
    int infoSize = 40;
    int a,b; //hadi
    struct PIXEL redd = {.blue=0, .green = 0, .red = 255}; //hadi
    
    a = infoHeader.width*infoHeader.height/2;
    b = a + infoHeader.height;
    
    printf("a = %d\n", a);
    printf("b = %d\n", b);
    
    concactStr(substractExtension(file), "_copy.bmp", &imageCopy);
    int opn = open(imageCopy,O_CREAT | O_RDWR,0644);
    
    if(opn<1){
        printf("Couldnt read nor create file %s\n", file);
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
    editTwoBytes(opn, (short*)&(infoHeader.bitsPerPixel));
    editFourBytes(opn, (int*)&(infoHeader.compression));
    editFourBytes(opn, (int*)&(infoHeader.imageSize));
    editFourBytes(opn, &(infoHeader.xPixelsPerM));
    editFourBytes(opn, &(infoHeader.yPixelsPerM));
    editFourBytes(opn, (int*)&(infoHeader.colorUsed));
    editFourBytes(opn, (int*)&(infoHeader.importantColors));
    
    
    //copy pixels
    
    printf("\n\nPixels: %d\n\n",infoHeader.imageSize/3);
    for(int pixelIterator=0;pixelIterator<(infoHeader.imageSize/3);pixelIterator++){
        //hadou
        printf("%d\r", pixelIterator);
        if(a<pixelIterator && pixelIterator<b){
            editByte(opn, (char*)&redd.blue);
            editByte(opn, (char*)&redd.green);
            editByte(opn, (char*)&redd.red);
            continue;
        }
        printf("kifach\r");
        editByte(opn, (char*)&((*(imagePixels+pixelIterator)).blue));
        editByte(opn, (char*)&((*(imagePixels+pixelIterator)).green));
        editByte(opn, (char*)&((*(imagePixels+pixelIterator)).red));
    }
    
}



