#include "transformations.h"

//int width;

void mask(char* file, char* mask, int start_x, int start_y)
{
    int reservedHeaderBytes = 0;
    char *imageCopy;
    
    int fileSize=0;
    ssize_t rf;
    struct BMPHeader mask_header;
    struct BMPINFOHEADER mask_infoHeader;
    unsigned char  *mask_grayImagePixels;
    int *mask_histogram;
    unsigned char mask_pixel=0;
    
    int mask_descriptor = open(mask, O_RDWR, 0644);
    
    if(mask_descriptor<1){
        printf("Couldnt read nor create file %s\n",mask);
        return;
    }
    
    /////////////// This mask works only when the images have the same dimensions
    //////////// 3 cases are present
    ///////// mask greater than the image   X we don't take this in consideration this case
    /////// mask smaller
    ////// mask equal
    bmpHeader(mask_descriptor, &fileSize, &mask_header);
    bmpInfoHeader(mask_descriptor, &fileSize, &mask_infoHeader);
    
    
    if(mask_infoHeader.width>infoHeader.width || mask_infoHeader.height>infoHeader.height)
    {
        printf("Mask's dimensions are bigger than the image\n");
        return;
    }
    
    mask_grayImagePixels = malloc(mask_infoHeader.width*mask_infoHeader.height*sizeof(unsigned char));
    
    mask_histogram = malloc(sizeof(int)*256);
    
    get_gray_pixels(mask_descriptor, mask_grayImagePixels, mask_histogram, mask_infoHeader.height, mask_infoHeader.width, mask_header.dataOffset);
    
    close(mask_descriptor);
    
    concactStr(substractExtension(file), "_mask.bmp", &imageCopy);
    
    int opn = open(imageCopy, O_CREAT | O_RDWR, 0644);
    
    printf("Mask width = %u, height = %u\n",mask_infoHeader.width, mask_infoHeader.height);
    ///////////// change width and height
    write_bmp4_gray_headers(opn);
    
    
    for(int i=0; i<infoHeader.height; i++)
    {
        for(int j=0; j<infoHeader.width; j++)
        {
            if(i>=start_x && j>=start_y &&  (i-start_x)<mask_infoHeader.width && (j-start_y)<mask_infoHeader.height)
            {
                if(*(mask_grayImagePixels + (i-start_x)*mask_infoHeader.width + j-start_y)==mask_pixel){
                        editByte(opn, (char *)&*(grayImagePixels + i*infoHeader.width + j));
                } else {
                        editByte(opn, (char *)&*(mask_grayImagePixels + (i-start_x)*mask_infoHeader.width + j-start_y));
                }
            } else {
                editByte(opn, (char *)&*(grayImagePixels + i*infoHeader.width + j));
            }
        }
        
        for(int p=0; p<(infoHeader.width*3)%4; p++)
        {
            editByte(opn, (char*)&reservedHeaderBytes);
        }
//        printf("%d\n", i-start_x);
    }

    free(mask_grayImagePixels);
    close(opn);
}
