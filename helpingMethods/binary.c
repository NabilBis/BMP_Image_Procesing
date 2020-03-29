#include "helpingMethods.h"


char*   bitsString(int num){
    
    int k;
    char *string = (char*)malloc(9*sizeof(char));
    for (int c = 7; c >= 0; c--)
    {
        // it like dividing n by 2 pow c
        k = num >> c;
        if (k & 1)
            *(string+7-c) = '1';
        else
            *(string+7-c) = '0';
    }
    
    *(string+8) = '\0';
    return string;
}


unsigned int bitsToDecimal(char *string,enum DECIMALTYPE g){
    
    unsigned int decimal=0;
    int i=0;
    int k;
    
    switch(g){
        case CHAR_TYPE: k =7; break;
        case SHORT_TYPE: k=15; break;
        default: k=31;
    }
    
    while(i<=k && *(string+i)!='\0' ){
        if(*(string+i)=='1'){
            decimal+=1<<(k-i);}
        i++;
    }
    return decimal;
}


unsigned int fourBytesToDecimal(int fileDescriptor){
    
    char *intBytes[4];
    unsigned char buffer;
    ssize_t readBytes;
    int i=0;
    char* number = malloc(32*sizeof(char));
    number="";
    
    while(i<4){
        readBytes = read(fileDescriptor,&buffer,1);
        if(readBytes<1)
            break;
        *(intBytes+i) = bitsString(buffer);
        i++;
    }
    
    for(int u=3;u>=0;u--){
        concactStr(number,*(intBytes+u),&number);
    }
    
    return bitsToDecimal(number,3);
}


unsigned short twoBytesToDecimal(int fileDescriptor){
    
    char *intBytes[2];
    unsigned char buffer;
    ssize_t readBytes;
    int i=0;
    char* number = malloc(16*sizeof(char));
    number="";
    
    while(i<2){
        readBytes = read(fileDescriptor,&buffer,1);
        if(readBytes<1)
            break;
        *(intBytes+i) = bitsString(buffer);
        i++;
    }
    for(int u=1;u>=0;u--){
        concactStr(number,*(intBytes+u),&number);
    }
    
    return (unsigned short) bitsToDecimal(number, SHORT_TYPE);
}
