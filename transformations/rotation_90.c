#include "transformations.h"



void rotate_90(char* file)
{
    int reservedHeaderBytes = 0;
    char *imageCopy;
    int new_width, new_height;
    int line, column;
    
    new_width = infoHeader.height;
    new_height = infoHeader.width;
    
    infoHeader.width = new_width;
    infoHeader.height = new_height;
    
    
    concactStr(substractExtension(file), "_rotated.bmp", &imageCopy);
    
    int opn = open(imageCopy,O_CREAT | O_RDWR,0644);
    
    write_bmp4_gray_headers(opn);
    
    
    for(int i=new_height-1; i>=0; i--)
    {
        for(int j=0; j<new_width; j++)
        {
            if(i==new_height-1)
            {
                line = new_height-1;
            } else {
                line = i%(new_height-1);
            }
            
            if(j==new_width-1)
            {
                column = new_width-1;
            } else {
                column = j%(new_width-1);
            }
            
            editByte(opn, (char *)&*(grayImagePixels + column*new_height + line));
        }
        
        for(int p=0; p<(new_width*3)%4; p++)
            {
                editByte(opn, (char*)&reservedHeaderBytes);
            }
        
    }
    
    infoHeader.width = new_height;
    infoHeader.height = new_width;
    
    close(opn);
}
