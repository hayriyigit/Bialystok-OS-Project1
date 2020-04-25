#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

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
            printf("Stack is empty");
            break;
        }
        
    }
    
    fclose(f);
}

