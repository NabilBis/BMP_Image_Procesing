#include "imageProcessing.h"


void printHeader(struct BMPHeader header);
void printInfoHeader(struct BMPINFOHEADER infoHeader);
void printImagePixels(struct PIXEL *image);


int main(int args,char** argv)
{
    clock_t begin = clock();
    int fileSize=0;
    ssize_t rf;
    extern struct BMPHeader header;
    extern struct BMPINFOHEADER infoHeader;
    extern struct PIXEL *imagePixels;
    extern unsigned char  *grayImagePixels;
    
    int start_x, start_y;
    
    char gray_scale = 10;
    
    int opn = open(argv[1], O_RDWR, 0644);
    
    if(opn<1){
        printf("Couldnt read nor create file %s\n",argv[1]);
        return 0;
    }
    
    bmpHeader(opn, &fileSize, &header);
    bmpInfoHeader(opn, &fileSize, &infoHeader);
    
    printf("\n");
    printHeader(header);
    printf("-------------- --------- ---------------\n");
    printInfoHeader(infoHeader);

    
    if(gray_scale) //////////// GRAY IMAGE'S PROCESS ////////////////
    {
        grayImagePixels = malloc(infoHeader.width*infoHeader.height*sizeof(unsigned char));
        
            ///////////////////
        gray_image_sorted = malloc(infoHeader.width*infoHeader.height*sizeof(unsigned char));
        
        histogram = calloc(256, sizeof(int));

        
        get_gray_pixels(opn, grayImagePixels, histogram, infoHeader.height, infoHeader.width, header.dataOffset);
        
        start_x = infoHeader.height/3;
        start_y = infoHeader.height/3;
//        gray_image_sorted = optimize_dbscan(histogram);
        
//        printf("Image size = %d\n", infoHeader.width*infoHeader.height);
//        sort_gray_pixels(gray_image_sorted, histogram, infoHeader.width*infoHeader.height);
//            apply_gray_filter(argv[1] , identity(), 3, 3, 1, "_identity");
//            rotate_90(argv[1]);
        mask(argv[1], argv[2], start_x, start_y);
//        cut(argv[1], start_x, start_y, start_x*2, start_y*2);
//            apply_gray_filter(argv[1], gaussian_blur(), 5, 5, 0.0039, "_blurred");
//            apply_gray_filter(argv[1], smoothing(), 3, 3, 1, "_smoothing");
//            apply_gray_filter(argv[1], edgeDetection(), 3, 3, 1, "_edgeDetect");
//            apply_gray_filter(argv[1], rotation(), 2, 2, 1, "_rotation");
        
//            for(int y=0; y<256; y++)
//                printf("Case = %d ---> %d\n",y, *(histogram+y));
        
//            apply_k(file, clusters, max_iteration);
//            apply_k(argv[1], 5, 25);
//            apply_GMS(argv[1], 44);
//             apply_DBSCAN(argv[1], 2, 440);
    }//////////// RGB IMAGE'S PROCESS ////////////////
    else {
        
        imagePixels = malloc(infoHeader.width*infoHeader.height*sizeof(struct PIXEL));
        get_image_pixels(opn, imagePixels, infoHeader.height, infoHeader.width, header.dataOffset);
        
//        to_bmp_iv4(argv[1]);
//            scale_x2(argv[1]);
//         applyFilter(argv[1], gaussian_blur(), 5, 5, 0.0039, "_blurred");
//            applyFilter(argv[1], identity(), 3, 3, 1, "_identity");
//            applyFilter(argv[1], rotation(), 2, 2, 1, "_rotation");
            colorToGray(argv[1]);
//            rgbSplit(argv[1]);
    }
    
    ////////////// FREE MEMORY IN HERE ////////////////
    //////                                 ///////////
    //////               ICI               //////////
    //////                                 /////////
    ///////////////////////////////////////////////
    close(opn);
    printf("\nRead bytes:  %d\n", fileSize);
    
    clock_t end = clock();
    
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nProgram executed in :");
    printf(ANSI_COLOR_YELLOW " %f \n\n" ANSI_COLOR_RESET,time_spent);
    
    return EXIT_SUCCESS;
}




void printHeader(struct BMPHeader header)
{
    printf("Signature:   %c%c\n", header.signature[0], header.signature[1]);
    printf("File size:  %u bytes\n", header.fileSize);
    printf("DataOffset:  %u bytes\n", header.dataOffset);
}

void printInfoHeader(struct BMPINFOHEADER infoHeader)
{
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

