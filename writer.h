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
        
        if(stack[i] != 0){
            
            fprintf(f,"%s\n",stack[i]);
        }else{
            printf("Stack is empty");
        }
        
    }
    
    fclose(f);
}

void readFile(){
    
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(".file.txt" , "r");

    if (fp == NULL){
        printf("There is no history file\n");
        exit(EXIT_FAILURE);
    }
    while ((read = getline(&line, &len, fp)) != -1) {
        printf("%s", line);
        line[strlen(line)-1] = '\0';
        push(line);
    }

     fclose(fp);

     if (line)
        free(line);
}

