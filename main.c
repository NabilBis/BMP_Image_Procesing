#include "imageProcessing.h"


void printHeader(struct BMPHeader header);
void printInfoHeader(struct BMPINFOHEADER infoHeader);
void printImagePixels(struct PIXEL *image);


int main(int args,char** argv){
    clock_t begin = clock();
    int fileSize=0;
    ssize_t rf;
    extern struct BMPHeader header;
    extern struct BMPINFOHEADER infoHeader;
    extern struct PIXEL *imagePixels;
    extern unsigned char  *grayImagePixels;
//    char *chPointer;
    int opn = open(argv[1], O_RDWR, 0644);
    
    if(opn<1){
        printf("Couldnt read nor create file %s\n",argv[1]);
        return 0;
    }
    printf("\n");
    
    bmpHeader(opn, &fileSize, &header);
    bmpInfoHeader(opn, &fileSize, &infoHeader);
    
    printHeader(header);
    printf("-------------- --------- ---------------\n");
    printInfoHeader(infoHeader);

    
    //////////// RGB IMAGE'S PROCESS ////////////////
    imagePixels = malloc(infoHeader.width*infoHeader.height*sizeof(struct PIXEL));
    fillPixel(opn, imagePixels, infoHeader.imageSize, header.dataOffset);
    
    
    //////////// GRAY IMAGE'S PROCESS ////////////////
//    grayImagePixels = malloc(infoHeader.width*infoHeader.height*sizeof(unsigned char));
//    fillGrayPixel(opn, grayImagePixels, header.fileSize - 54, header.dataOffset);

    
//    convertImage(argv[1]);
//    scale_x2(argv[1]);
    
//    applyFilter(argv[1], idd(), 5, 5, 1, "_identity");
//    applyFilter(argv[1], laplacien(), 3, 3, 1, "_identity");
//     applyFilterGray(argv[1], idd(), 5, 5, 1, "_identity");
//    applyFilterGray(argv[1], identity(), 3, 3, 1, "_identity");
//    colorToGray(argv[1]);
    rgbSplit(argv[1]);
//    imageDescriptor(argv[1]);
    
    
    
    ////////////// FREE MEMORY IN HERE ////////////////
    //////                                 ///////////
    //////                                 //////////
    //////                                 /////////
    ///////////////////////////////////////////////
    close(opn);
    printf("\nRead bytes:  %d\n",fileSize);
    
    clock_t end = clock();
    
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nProgram executed in :");
    printf(ANSI_COLOR_YELLOW " %f \n\n" ANSI_COLOR_RESET,time_spent);
    
    return EXIT_SUCCESS;
}




void printHeader(struct BMPHeader header){
    printf("Signature:   %c%c\n", header.signature[0], header.signature[1]);
    printf("Image size:  %u bytes\n", header.fileSize);
    printf("DataOffset:  %u bytes\n", header.dataOffset);
}

void printInfoHeader(struct BMPINFOHEADER infoHeader){
    printf("Info header size:  %u\n", infoHeader.infoHeaderSize);
    printf("Width :  %u\n", infoHeader.width);
    printf("Height :  %u\n", infoHeader.height);
    printf("Planes:  %u\n", infoHeader.planes);
    printf("bitsPerPixel :  %u\n", infoHeader.bitsPerPixel);
    printf("Compression :  %u\n", infoHeader.compression);
    printf("Image size :  %u bytes\n", infoHeader.imageSize);
    printf("XpixelsPerM :  %u\n", infoHeader.xPixelsPerM);
    printf("YpixelsPerM :  %u\n", infoHeader.yPixelsPerM);
    printf("Colors used :  %u\n", infoHeader.colorUsed);
    printf("Important colors :  %u\n", infoHeader.importantColors);
    printf("Pixels per inch: %d\n", infoHeader.xPixelsPerM/39);
}

void printImagePixels(struct PIXEL *image){
    for(int i=0; i<20; i++){
        printf("%d ", (*(image+i)).blue);
    }
}
