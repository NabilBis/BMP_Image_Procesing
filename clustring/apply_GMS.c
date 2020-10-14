#include "cluster.h"

void apply_GMS(char* file, int window)
{
    int reservedHeaderBytes = 0;
    char *imageCopy;
    int imageSi;
    
    unsigned char* clus;
    unsigned char *modes = malloc((256/window + 1)*sizeof(char));
    
    for(int w=0; w<=256/window; w++)
    {
        *(modes+w) = 0;
    }

    imageSi = infoHeader.width*infoHeader.height;
    
    clus = malloc(sizeof(char)*imageSi);
    
    concactStr(substractExtension(file), "_GMS", &imageCopy);
    concactStr(imageCopy, ".bmp", &imageCopy);
    
    int opn = open(imageCopy, O_CREAT | O_RDWR,0644);
    
    if(opn<1){
        printf("Couldnt read nor create file %s\n", file);
        return;
    }
    
    write_bmp4_gray_headers(opn);
    
    gaussian_mean_shift(grayImagePixels, imageSi, clus, modes, window);
    
    
    for(int h=0; h<infoHeader.height; h++)
    {
        for(int w=0; w<infoHeader.width; w++)
        {
            editByte(opn, (char*)(modes +(int)(*(clus+h*infoHeader.width+w))));
        }
        
        for(int p=0; p<(infoHeader.width*3)%4; p++)
        {
            editByte(opn, (char*)&reservedHeaderBytes);
        }
    }

    close(opn);
}
