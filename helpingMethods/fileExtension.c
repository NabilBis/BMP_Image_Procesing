#include "helpingMethods.h"


char* substractExtension(char* fileName){
    int strSize, extension, i;
    char* strT;
    strSize = extension = i =0;
        // i used both strSize and i so i can later be able to identify the lenght of string + extension
    while (*(fileName+i) != '\0') {
        if(*(fileName+i)=='.' && strSize == i){
            extension=1;
        }
        if(!extension){
            strSize++;
        }
        i++;
    }
    
    strT = (char*) malloc((strSize+1)*sizeof(char));
    
    for(int u=0; u<strSize; u++){
        *(strT+u)= *(fileName+u);
    }
    
    *(strT+strSize) = '\0';
    return strT;
}



