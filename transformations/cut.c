#include "transformations.h"


void cut(char* file, int start_x, int start_y, int end_x, int end_y)
{
    int reservedHeaderBytes = 0;
    char *imageCopy;
    int width, height;
    
    if(start_x<0 || start_y<0 || end_x>infoHeader.width || end_y>infoHeader.height)
    {
        printf("Cannot cut image with these dimensions\n");
        return;
    }
    
    width = infoHeader.width;
    height = infoHeader.height;
    
    infoHeader.width = end_x - start_x;
    infoHeader.height = end_y - start_y;
    
    
    concactStr(substractExtension(file), "_cut.bmp", &imageCopy);
    
    int opn = open(imageCopy, O_CREAT | O_RDWR,0644);
    
    write_bmp4_gray_headers(opn);


        for(int i=start_y; i<end_y; i++)
        {
            for(int j=start_x; j<end_x; j++)
            {
                editByte(opn, (char *)&*(grayImagePixels + i*width + j));
            }
            
            for(int p=0; p<(infoHeader.width*3)%4; p++)
            {
                editByte(opn, (char*)&reservedHeaderBytes);
            }
        }

    infoHeader.width = width;
    infoHeader.height = height;
    
    close(opn);
}






//int main(int args, char** argv)
//{
//    int *mat = malloc(sizeof(int)*15);
//    int height;
//
//    width = 5;
//    height = 6;
//
//    *(mat+0)=1;
//    *(mat+1)=2;
//    *(mat+2)=3;
//    *(mat+3)=4;
//    *(mat+4)=5;
//    *(mat+5)=6;
//    *(mat+6)=7;
//    *(mat+7)=8;
//    *(mat+8)=9;
//    *(mat+9)=10;
//    *(mat+10)=11;
//    *(mat+11)=12;
//    *(mat+12)=13;
//    *(mat+13)=14;
//    *(mat+14)=15 ;
//    *(mat+15)=16;
//    *(mat+16)=17;
//    *(mat+17)=18;
//    *(mat+18)=19;
//    *(mat+19)=20;
//    *(mat+20)=21;
//    *(mat+21)=22;
//    *(mat+22)=23;
//    *(mat+23)=24;
//    *(mat+24)=25;
//    *(mat+25)=26;
//    *(mat+26)=27;
//    *(mat+27)=28;
//    *(mat+28)=29;
//    *(mat+29)=30;
//
//    for(int i=0; i<height; i++)
//    {
//        for(int j=0; j<width; j++)
//        {
//            printf("%d ",*(mat + i*width+j));
//        }
//        printf("\n");
//    }
//    printf("\n\n");
//    cut(mat, 1, 2, 4, 5 );
//    return EXIT_SUCCESS;
//}
