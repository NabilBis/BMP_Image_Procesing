#include "helpingMethods.h"


void bmpHeader(int fileDescriptor,int *increment,struct BMPHeader* header){
    
    ssize_t rf;
    char *bmpSize[4];
    char *dataOff[4];
    unsigned char uChar;
    char* number = malloc(32*sizeof(char));
    
    number="";
    int i=0;

    lseek(fileDescriptor,0, SEEK_SET);
    
    while(i<14){
        rf = read(fileDescriptor,&uChar,1);
        if(rf<1){
            break; }
        if(i<2){
            header->signature[i] = uChar;
        }
        if(i>1 && i<6){
            *(bmpSize + i-2) = bitsString(uChar);
        }
        if(i>9 && i<14){
            *(dataOff + i-10) = bitsString(uChar);
        }
        (*increment)++;
        i++;
    }

    for(int u=3;u>=0;u--){
                concactStr(number,*(bmpSize+u),&number);
    }
    header->fileSize = bitsToDecimal(number,3);
    concactStr("","",&number);
    for(int u=3;u>=0;u--){
        concactStr(number,*(dataOff+u),&number);
    }
    
    header->dataOffset = bitsToDecimal(number,3);
    /////////////// ??? NULL why
//    number=NULL;
    free(number);
}


