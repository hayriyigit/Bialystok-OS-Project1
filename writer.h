#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
/**
 * writes to history file the last 20 commands using stack
 * 
 * out: void
*/
void writeFile(){
    FILE *f = fopen(".file.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for(int i = 0; i < 20; i++){
        
        if(*stack[i] != 0){
            fprintf(f,"%s\n",stack[i]);
        }else{
            break;
        }
        
    }
    
    fclose(f);
}

