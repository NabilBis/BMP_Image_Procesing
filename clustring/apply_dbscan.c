#include "cluster.h"

void apply_DBSCAN(char* file, int radius, int min_points)
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
    unsigned char* pixels = malloc(sizeof(char)*256);
    
//    unsigned char* clus;
//    unsigned char *modes = malloc((256/window + 1)*sizeof(char));
    
    for(int w=0; w<256; w++)
    {
        *(pixels+w) = 0;
    }
    
    imageSi = infoHeader.width*infoHeader.height;
    fileSi = imageSi + header.dataOffset;
    
//    clus = malloc(sizeof(char)*imageSi);
    
    concactStr(substractExtension(file), "_DBSCAN", &imageCopy);
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
    
    printf("Image size = %d\n", imageSi);
//    printf("Ha houwa dakhel i tsorta\n");
////    char_QuickSort(gray_image_sorted, 0, imageSi-1);
//    printf("Ici ?\n");
    
    dbscan(gray_image_sorted, imageSi/*__sorted_size__*/, radius, min_points, pixels);
    
    printf("DBSCAN DONE \n");
    for(int h=0; h<infoHeader.height; h++)
    {
        for(int w=0; w<infoHeader.width; w++)
        {
            editByte(opn, (char*)(pixels +(int)(*(grayImagePixels+h*infoHeader.width+w))));
        }
        
        for(int p=0; p<(infoHeader.width*3)%4; p++)
        {
            editByte(opn, (char*)&reservedHeaderBytes);
        }
    }
    
    close(opn);
}
