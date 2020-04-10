#include "cluster.h"


void apply_k(char* file, int means_size, int max_iteration)
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
    
//    int  means_size=5;
    int* mapping;
    unsigned char* centroids = malloc(sizeof(char)*means_size);
    unsigned int* avg_dists = malloc(sizeof(int)*means_size);
    int* cluster_members_count= malloc(sizeof(int)*means_size);
    
    
    centroids = rando(means_size);
    
    imageSi = infoHeader.width*infoHeader.height;
    fileSi = imageSi + header.dataOffset;

    mapping = malloc(sizeof(int)*imageSi);
    
    
    concactStr(substractExtension(file), "_kmeans", &imageCopy);
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
    editFourBytes(opn, &reservedHeaderBytes);
    editFourBytes(opn, &(infoHeader.xPixelsPerM));
    editFourBytes(opn, &(infoHeader.yPixelsPerM));
    editFourBytes(opn, (int*)&(infoHeader.colorUsed));
    editFourBytes(opn, (int*)&(infoHeader.importantColors));
    
    
    fillColorPalette(opn);
    
    
    
    k_means(grayImagePixels, imageSi, means_size, centroids, max_iteration, mapping, avg_dists, cluster_members_count);
    

    for(int i=0; i<infoHeader.width; i++)
    {
        for(int j=0; j<infoHeader.height; j++)
        {
            editByte(opn, (char*)(centroids + *(mapping + i*infoHeader.width + j)));
        }
    }
    
    
    close(opn);
}
