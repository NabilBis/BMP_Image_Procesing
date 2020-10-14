#include "helpingMethods.h"


void get_image_pixels(int fileDsc, struct PIXEL *image, unsigned int height, unsigned width, int dataOffset)
{
    size_t rf;
    unsigned char *buffer = malloc(sizeof(char));
    char bgr[3];
    
    lseek(fileDsc, dataOffset, SEEK_SET);
    
    
    for(int h=0; h<height; h++) /// h*width + w
    {
        for(int w=0; w<width; w++)
        {
            for(int b=0; b<3; b++)
            {
              rf = read(fileDsc, buffer, 1);
              if(rf<1){
                printf("Could not read from file at position from fillPixel function\n");
                break;
              }
              switch (b%3) {
                case 0:
                    (*(image+h*width + w)).blue = *buffer;
                    break;
                case 1:
                    (*(image+h*width + w)).green = *buffer;
                    break;
                case 2:
                    (*(image+h*width + w)).red = *buffer;
                    break;
                default:
                    break;
                }
            }
        }
        
        for(int p=0; p<(width%4); p++)
        {
            rf = read(fileDsc, buffer, 1);
        }
    }

    free(buffer);
}



void get_gray_pixels(int fileDsc, unsigned char *image, int *histogram, unsigned int height, unsigned width, int dataOffset)
{
    
    size_t rf;
    unsigned char *buffer = malloc(sizeof(char));
    
    lseek(fileDsc, dataOffset, SEEK_SET);
    
    
    
    for(int h=0; h<height; h++) /// h*width + w
    {
        for(int w=0; w<width; w++)
        {

                rf = read(fileDsc, buffer, 1);
                if(rf<1){
                    printf("Could not read from file at position from fillPixel function\n");
                    break;
                }
                
                *(image + h*width + w) = *buffer;
            //////////// FILL ARRAY TO SORT
                (*(histogram + *buffer))++;
            
        }
        
        for(int p=0; p<(width*3)%4; p++)
        {
            rf = read(fileDsc, buffer, 1);
        }
    }
//    free(buffer);
}

