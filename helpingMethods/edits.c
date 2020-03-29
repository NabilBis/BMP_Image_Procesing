#include "helpingMethods.h"
//#include <stdio.h>

void editByte(int fileDescriptor,char *newValue){
    ssize_t wf;
        wf = write(fileDescriptor,newValue,1);
        if(wf<1){
            printf("Could not write on file \n");
            return;
        }
    
}

//void editPixel(int fileDescriptor,struct PIXEL pixel){
//    ssize_t wf;
//        wf = write(fileDescriptor,&pixel.blue,1);
//    if(wf<1){
//        printf("Could not write on file \n");
//        return;
//    }
//        wf = write(fileDescriptor,&pixel.green,1);
//    if(wf<1){
//        printf("Could not write on file \n");
//        return;
//    }
//        wf = write(fileDescriptor,&pixel.red,1);
//    if(wf<1){
//        printf("Could not write on file \n");
//        return;
//    }
//}

void editTwoBytes(int fileDescriptor,short *newValue){
    
    ssize_t wf;
    for(int i=0; i<2; i++){
        wf = write(fileDescriptor, (char *)newValue+i, 1);
        if(wf<1){
            printf("Could not write on file \n");
            return;
        }
    }
}

void editFourBytes(int fileDescriptor,int *newValue){
    
    ssize_t wf;
    for(int i=0; i<4; i++){
        wf = write(fileDescriptor, (char *)newValue+i, 1);
        if(wf<1){
            printf("Could not write on file \n");
            return;
        }
    }
}








//void editWidth(int fileDescriptor,int *newWidth){
//
//    lseek(fileDescriptor,18, SEEK_SET);
//
//    editFourBytes(fileDescriptor,newWidth);
//
//}
//
//void editHeight(int fileDescriptor,int *newHeight){
//
//    lseek(fileDescriptor,22, SEEK_SET);
//
//    editFourBytes(fileDescriptor,newHeight);
//
//}
//
//
//void editResolution(int fileDescriptor,int *newResolution){
//
//    lseek(fileDescriptor,38, SEEK_SET);
//
//    editFourBytes(fileDescriptor,newResolution);
//    editFourBytes(fileDescriptor,newResolution);
//
//}



//
//int main(int args,char** argv){
//
//        ssize_t wf;
//        int changeResolutionTo = 2835;
//        int newWidth= 1300;
//
//        int opn = open(argv[1],O_RDWR,0644);
//
//        if(opn<1){
//            printf("Couldnt read nor create file %s\n",argv[1]);
//                return 0;
//        }
//
//        editWidth(opn,&newWidth);
////        editHeight(opn,&newHeight);
////        editResolution(opn,&changeResolutionTo);
//
//        return EXIT_SUCCESS;
//
//}

