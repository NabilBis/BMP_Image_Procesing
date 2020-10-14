#include "../cluster.h"

void swap_char(unsigned char *n1, unsigned char  *n2)
{
    unsigned char t;
    
    t = *n1;
    *n1 = *n2;
    *n2 = t;
}


int partition(unsigned char *array, int low, int high)
{
    unsigned char pivot = *(array+high);
    int i = low-1;
    
    for(int l=low; l<high; l++)
    {
        if(*(array+l)<=pivot)
        {
            i++;
            swap_char(array+i, array+l);
        }
    }
    
    swap_char(array+i+1, array+high);
    
    return (i+1);
}


void char_QuickSort(unsigned char *arr,int low, int high)
{
    int partitionReturn;
    
    if (low < high)
    {
        partitionReturn = partition(arr, 0, high);
//        printf("---\n");
        char_QuickSort(arr, 0, partitionReturn-1);
        char_QuickSort(arr, partitionReturn+1, high);
    }
}



//int main(int args, char** argv)
//{
//    unsigned char *data = malloc(sizeof(char)*18);
//    
//        *(data+0) = 12;
//        *(data+1) = 37;
//        *(data+2) = 84;
//        *(data+3) = 25;/////// 63
//        *(data+4) = 67;
//        *(data+5) = 5;
//        *(data+6) = 75;
//        *(data+7) = 30;
//        *(data+8) = 9;
//        *(data+9) = 13;
//        *(data+10) = 80;
//        *(data+11) = 69;
//        *(data+12) = 22;
//        *(data+13) = 70;
//        *(data+14) = 7;
//        *(data+15) = 27;
//        *(data+16) = 61;
//        *(data+17) = 1;
//    
//    char_QuickSort(data, 0, 18);
//         for(int i=0; i<18; i++)
//           printf("%d ", *(data+i));
//    printf("\n");
//    return EXIT_SUCCESS;
//}
