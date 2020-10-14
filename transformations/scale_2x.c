#include "transformations.h"


struct PIXEL sumPixels(struct PIXEL p1, struct PIXEL p2, struct PIXEL p3, struct PIXEL p4)
{
    
    unsigned short res;
    struct PIXEL new;
    
    res = p1.blue + p2.blue + p3.blue + p4.blue;
    new.blue = res/4;
    
    res = p1.green + p2.green + p3.green + p4.green;
    new.green = res/4 ;
    
    res = p1.red + p2.red + p3.red + p4.red;
    new.red = res/4;
    
    return new;
}

///////////// ALready exists somewhere
void editPixell(int fileDescriptor,struct PIXEL pixel)
{
    ssize_t wf;
    
    wf = write(fileDescriptor, &pixel.blue, 1);
    
    if(wf<1){
        printf("Could not write blue pixel on file \n");
        return;
    }
    wf = write(fileDescriptor, &pixel.green, 1);
    
    if(wf<1){
        printf("Could not write green pixel on file \n");
        return;
    }
    
    wf = write(fileDescriptor, &pixel.red, 1);
    
    if(wf<1){
        printf("Could not write red pixel on file \n");
        return;
    }
}


// Routine
struct PIXEL calculX(struct PIXEL *tab, int i, int j, int width)
{
       // The returned value must be computed of a variaty of algorithms
    return sumPixels(
                     *(tab+((i-1)/2)*width+(j-1)/2),
                     *(tab+((i-1)/2)*width+(j+1)/2),
                     *(tab+((i+1)/2)*width+(j-1)/2),
                     *(tab+((i+1)/2)*width+(j+1)/2)
                      );
}



void scale_x2(char* file){
    extern struct BMPHeader header;
    extern struct BMPINFOHEADER infoHeader;
    extern struct PIXEL *imagePixels;
    int reservedHeaderBytes = 0;
    char *imageCopy;
    int imageSi;
    int fileSi;
    int newWidth;
    int newHeight;
    struct PIXEL newPixel;
    
    struct PIXEL neutralPixel = {.blue = 255, .green = 255, .red = 255 };
    
    newWidth = infoHeader.width*2;
    newHeight = infoHeader.height*2;
    imageSi = newWidth*3*newHeight;
    fileSi = imageSi + header.dataOffset;
    
    concactStr(substractExtension(file), "_x2.bmp", &imageCopy);
    int opn = open(imageCopy,O_CREAT | O_RDWR,0644);
    
//    free(imageCopy);
    
    if(opn<1){
        printf("Couldnt read nor create file %s\n", file);
        return;
    }
    
    lseek(opn, 0, SEEK_SET);
    
    ///copy header = 14
    editByte(opn, &(header.signature[0]));
    editByte(opn, &(header.signature[1]));
    editFourBytes(opn, &fileSi);
    editFourBytes(opn, &reservedHeaderBytes);
    editFourBytes(opn, (int*)&(header.dataOffset));
    
    
    //copy infoHeader = 124
    editFourBytes(opn,(int*)&(infoHeader.infoHeaderSize)); //4
    editFourBytes(opn, &newWidth); //4
    editFourBytes(opn, &newHeight); //4
    editTwoBytes(opn, (short*)&(infoHeader.planes)); //2
    editTwoBytes(opn, (short*)&(infoHeader.bitsPerPixel)); //2
    editFourBytes(opn, (int*)&(infoHeader.compression)); //4
    editFourBytes(opn, &imageSi); //4
    editFourBytes(opn, &(infoHeader.xPixelsPerM)); //4
    editFourBytes(opn, &(infoHeader.yPixelsPerM)); //4
    editFourBytes(opn, (int*)&(infoHeader.colorUsed)); //4
    editFourBytes(opn, (int*)&(infoHeader.importantColors)); //4
    
    
    //84
    if(infoHeader.infoHeaderSize == 124)
        for(int y=0; y<21; y++)
            editFourBytes(opn, &reservedHeaderBytes);
    
//    Scale image
    for(int i=0; i<newHeight; i++)
    {
        for(int j=0; j<newWidth; j++)
        {
            if(i%2==0 && j%2==0)
                editPixell(opn, *(imagePixels+(i/2)*(newWidth/2)+j/2));
            
            else if(i%2!=0 && j%2!=0 &&(i!=newHeight-1)&& (j!=newWidth-1))
                editPixell(opn, calculX(imagePixels, i, j, newWidth/2));
            
            else if(i!=0 && j!=0 && j!=newWidth-1 && i%2==0 && j%2!=0)
            {
                newPixel = i==newHeight-2 ? neutralPixel : calculX(imagePixels, i+1, j, newWidth/2);
                
                editPixell(opn, sumPixels(*(imagePixels+(i/2)*(newWidth/2)+(j+1)/2), *(imagePixels+(i/2)*(newWidth/2)+(j)/2), calculX(imagePixels, i-1, j, newWidth/2), newPixel));
            }
            else if(i%2!=0 && j%2==0 && j!=0 && i!=newHeight-1 && j!=newWidth-1)
            {
                newPixel = (j==newWidth-2) ? neutralPixel : calculX(imagePixels, i, j+1, newWidth/2);
                
                editPixell(opn, sumPixels(*(imagePixels+(i/2)*(newWidth/2)+j/2), *(imagePixels+(i+2)/2*(newWidth/2)+j/2), calculX(imagePixels, i, j-1, newWidth/2), newPixel));
            }
            else
                editPixell(opn, neutralPixel);
        }
        ////////// Padding 
        for(int p=0; p<((infoHeader.width*2)%4); p++)
        {
            editByte(opn, (char*)&reservedHeaderBytes);
        }
    }
    
    close(opn);
}


