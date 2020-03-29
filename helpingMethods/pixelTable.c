#include "helpingMethods.h"


//void fillPixel(int fileDsc, struct PIXEL *image, unsigned int imageSize,int dataOffset){
//    static int k=0;
//    size_t rf;
//    unsigned char *buffer = (unsigned char*)malloc(sizeof(char));
//    lseek(fileDsc,138+dataOffset*k, SEEK_SET);
//    for(int i=0;i<imageSize;i++){
//        rf = read(fileDsc,buffer,1);
//        if(rf<1){
//            printf("Could not read from file at position %d\n",i);
//            break;
//        }
//        switch (i%3) {
//            case 0:
//                (*(image+(i/3))).blue = *buffer;
//                break;
//            case 1:
//                (*(image+(i/3))).green = *buffer;
//                break;
//            case 2:
//                (*(image+(i/3))).red = *buffer;
//                break;
//            default:
//                break;
//        }
//    }
//    printf("k == %d\n",k);
//    k++;
//}


void fillPixel(int fileDsc, struct PIXEL *image, unsigned int imageSize, int dataOffset){
    size_t rf;
    unsigned char *buffer = malloc(sizeof(char));
    
    lseek(fileDsc, dataOffset, SEEK_SET);
    
    for(int i=0; i<imageSize; i++){
        rf = read(fileDsc,buffer,1);
        if(rf<1){
            printf("Could not read from file at position %d\n",i);
            break;
        }
        switch (i%3) {
            case 0:
                (*(image+(i/3))).blue = *buffer;
                break;
            case 1:
                (*(image+(i/3))).green = *buffer;
                break;
            case 2:
                (*(image+(i/3))).red = *buffer;
                break;
            default:
                break;
        }
    }
    free(buffer);
}


void fillGrayPixel(int fileDsc, unsigned char *image, unsigned int imageSize,int dataOffset)
{
    size_t rf;
    unsigned char *buffer = malloc(sizeof(char));
    
    lseek(fileDsc, dataOffset, SEEK_SET);
    
    for(int i=0; i<imageSize; i++){
        rf = read(fileDsc,buffer,1);
        if(rf<1){
            printf("Could not read from file at position %d\n",i);
            break;
        }
    
        *(image+i) = *buffer;
    }
//    free(buffer);
}

