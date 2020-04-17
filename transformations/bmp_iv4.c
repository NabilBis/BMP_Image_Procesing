#include "transformations.h"

void to_bmp_iv4(char* file)
{
    extern struct BMPHeader header;
    extern struct BMPINFOHEADER infoHeader;
    extern struct PIXEL *imagePixels;
    int reservedHeaderBytes = 0;
    char *imageCopy;
    int dataOff = 54;
    int infoSize = 40;
    int imageSi, fileS;

    
    fileS = header.fileSize;
    imageSi = header.fileSize-dataOff;

    if(header.dataOffset==138)
    {
        fileS -= 70;
        imageSi -= 70;
    }
    
    concactStr(substractExtension(file), "_Iv4.bmp", &imageCopy);
    
    int opn = open(imageCopy,O_CREAT | O_RDWR,0644);
    
    if(opn<1){
        printf("Couldnt read nor create file %s\n", file);
        return;
    }
    
    lseek(opn, 0, SEEK_SET);
    
    ///copy header
    editByte(opn, &(header.signature[0]));
    editByte(opn, &(header.signature[1]));
//    editFourBytes(opn, (int*)&(header.fileSize));
    editFourBytes(opn, &fileS);
    editFourBytes(opn, &reservedHeaderBytes);
    editFourBytes(opn, &dataOff);
    
    
    //copy infoHeader
    editFourBytes(opn, &infoSize);
    editFourBytes(opn, &(infoHeader.width));
    editFourBytes(opn, &(infoHeader.height));
//    editFourBytes(opn, &hh);
    editTwoBytes(opn, (short*)&(infoHeader.planes));
    editTwoBytes(opn, (short*)&(infoHeader.bitsPerPixel));
    editFourBytes(opn, (int*)&(infoHeader.compression));
//    editFourBytes(opn, (int*)&(infoHeader.imageSize));
    editFourBytes(opn, &imageSi);
    editFourBytes(opn, &(infoHeader.xPixelsPerM));
    editFourBytes(opn, &(infoHeader.yPixelsPerM));
    editFourBytes(opn, (int*)&(infoHeader.colorUsed));
    editFourBytes(opn, (int*)&(infoHeader.importantColors));
    
    
    
    for(int i=0; i<infoHeader.height; i++)
    {
        for(int j=0; j<infoHeader.width; j++)
        {
          editByte(opn, (char*)&((*(imagePixels+i*infoHeader.width+j)).blue));
          editByte(opn, (char*)&((*(imagePixels+i*infoHeader.width+j)).green));
          editByte(opn, (char*)&((*(imagePixels+i*infoHeader.width+j)).red));
        }
        
        for(int p=0; p<(infoHeader.width%4); p++)
        {
            editByte(opn, (char*)&reservedHeaderBytes);
        }
    }
    
    close(opn);
}



