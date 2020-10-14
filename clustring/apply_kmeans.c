#include "cluster.h"

void apply_k(char* file, int means_size, int max_iteration)
{
    int reservedHeaderBytes = 0;
    char *imageCopy;
    int* mapping;
    int imageSi;
    unsigned char* centroids = malloc(sizeof(char)*means_size);
    unsigned int* avg_dists = malloc(sizeof(int)*means_size);
    int* cluster_members_count= malloc(sizeof(int)*means_size);
    
    
    centroids = rando(means_size);
    
    mapping = malloc(sizeof(int)*imageSi);
    
    imageSi = infoHeader.width*infoHeader.height;
    
    concactStr(substractExtension(file), "_kmeans", &imageCopy);
    concactStr(imageCopy, ".bmp", &imageCopy);
    
    int opn = open(imageCopy, O_CREAT | O_RDWR,0644);

    if(opn<1){
        printf("Couldnt read nor create file %s\n", file);
        return;
    }
    
    write_bmp4_gray_headers(opn);

    
    k_means(grayImagePixels, imageSi, means_size, centroids, max_iteration, mapping, avg_dists, cluster_members_count);
    


    for(int h=0; h<infoHeader.height; h++)
    {
        for(int w=0; w<infoHeader.width; w++)
        {
            editByte(opn, (char*)(centroids + *(mapping + h*infoHeader.width+w)));
        }
        
        for(int p=0; p<(infoHeader.width*3)%4; p++)
        {
            editByte(opn, (char*)&reservedHeaderBytes);
        }
    }

    close(opn);
}
