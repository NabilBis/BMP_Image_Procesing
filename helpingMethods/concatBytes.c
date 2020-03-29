#include "helpingMethods.h"

void concactStr(char *first,const char *second,char **result)
{
    char *new;///////// KANE NULL = NULL;
	int fl,sL;
	int length;

       fl=sL=0;
    
	while(*(first+fl)!='\0'){
		fl++;
	}
   	while(*(second+sL)!='\0'){
                sL++;
        }
    
	length= sL+fl;
    
    //////// HNA KANT 32 fblast legnth
	new = malloc((length+1)*sizeof(char));

	for(int i=0; i<(length); i++)
    {
		if(i<fl){
		  *(new+i) = *(first+i);
		}else {
		  *(new+i) = *(second+(i+sL-length));
		}	
	}
    
	*(new+length) = '\0';
	*result = new;
    
    ///free(new);
}
