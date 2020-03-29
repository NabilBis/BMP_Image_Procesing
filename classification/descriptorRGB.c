#include "readImageInfos.h"

unsigned char binaryToDecimal(unsigned char arr[])
{
    unsigned char decimal = 0;

    for(int i=0; i<8; i++){
        decimal <<= 1;
        if(arr[i])
         decimal |= 1;
    }
    return decimal;
}

//int stringEquals(char* str1, char* str2){
//    
//    int i=0;
//    
//    while (*(str1 +i) != '\0' || *(str2 +i) != '\0')
//        if(*(str1+i) != *(str2+i))
//            return 0;
//    
//    return 1;
//}

unsigned char toGrayFunc(struct PIXEL pixel)
{
    return (0.3*pixel.red + 0.59*pixel.green + 0.11*pixel.blue);
}


int absoluteValue(int num)
{
    int tab[2] = {num, -num};
    return tab[num<0];
}

int descriptorDistance(unsigned char desUno[], unsigned char desDos[])
{
    int res = 0;
    
    for(int u=0; u<256; u++)
        res+= absoluteValue(((int)desUno[u] - (int)desDos[u]));
    
    return res;
}


//void calculDuTaux(){
//    DIR *dir;
//    struct dirent *dp;
//    char *fileExtension;
//    
//    if ((dir = opendir (argv[1])) == NULL) {
//        perror ("Cannot open .");
//        exit (1);
//    }
//    
//    
//    while ((dp = readdir (dir)) != NULL) {
//        
//        if(stringEquals(dp->d_name, ".") || stringEquals(dp->d_name, ".."))
//            continue;
//        
//        concactStr(substractExtension(dp->d_name), "_descriptor", &imageDescriptor);
//    }
//
//}




void imageDescriptor(char* file)
{
    extern struct BMPINFOHEADER infoHeader;
    extern struct PIXEL *imagePixels;
    unsigned char bytesOccurences[256] = {0};// = malloc(256*sizeof(char));
    unsigned char binary[8];
    int width;
    int opnDesc;
    char *imageDescriptor;
    
    concactStr(substractExtension(file), "_descriptor.txt", &imageDescriptor);
    
    
    opnDesc = open(imageDescriptor, O_CREAT | O_RDWR,0644);
    
    if(opnDesc<1){
        printf("Couldnt read nor create file\n");//, imageDescriptor);
        return;
    }
    
    
    width = infoHeader.width;
    
    
    for(int h=1; h<infoHeader.height-1; h++){
        for(int w=1; w<width-1; w++){
            binary[0] = toGrayFunc(*(imagePixels+ (h-1)*width+w-1)) < toGrayFunc(*(imagePixels+ h*width+w)) ? 1:0;
            binary[1] = toGrayFunc(*(imagePixels+ (h-1)*width+w)) < toGrayFunc(*(imagePixels+ h*width+w)) ? 1:0;
            binary[2] = toGrayFunc(*(imagePixels+ (h-1)*width+w+1)) < toGrayFunc(*(imagePixels+ h*width+w)) ? 1:0;
            binary[3] = toGrayFunc(*(imagePixels+ h*width+w+1)) < toGrayFunc(*(imagePixels+ h*width+w)) ? 1:0;
            binary[4] = toGrayFunc(*(imagePixels+ (h+1)*width+w+1)) < toGrayFunc(*(imagePixels+ h*width+w)) ? 1:0;
            binary[5] = toGrayFunc(*(imagePixels+ (h+1)*width+w)) < toGrayFunc(*(imagePixels+ h*width+w)) ? 1:0;
            binary[6] = toGrayFunc(*(imagePixels+ (h+1)*width+w-1)) < toGrayFunc(*(imagePixels+ h*width+w)) ? 1:0;
            binary[7] = toGrayFunc(*(imagePixels+ h*width+w-1)) < toGrayFunc(*(imagePixels+ h*width+w)) ? 1:0;
            
            bytesOccurences[binaryToDecimal(binary)]++;
        }
    }

    
    for(int v=0; v<256; v++)
        editByte(opnDesc, (char*)&bytesOccurences[v]);
    
    close(opnDesc);
//    return bytesOccurences;
}






