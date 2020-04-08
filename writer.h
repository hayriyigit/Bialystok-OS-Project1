#include <stdio.h>
#include "stack.h"

void writeFile(){
    FILE *f = fopen("file.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    char *line;
    line = stack[0];
    
    

    
    fclose(f);
   printf("haha");


}

