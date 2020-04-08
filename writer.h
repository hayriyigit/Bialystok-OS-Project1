#include <stdio.h>
#include "stack.h"

void writeFile(){
    FILE *f = fopen("file.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    do{
    	char line[1024];
    	strcpy(line,pop());
    	printf("%s\n",line);
    }while(isEmpty() != 1);

    
    fclose(f);
}

