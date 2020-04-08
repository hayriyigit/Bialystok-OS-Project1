#include <stdio.h>
#include<stdlib.h>
#include<string.h>

int MAXSIZE = 1024;
int top = -1;

char stack[20][1024];
char line[1024];

int size(){
    return MAXSIZE;
}

int isEmpty(){
    if(top == -1){
        return 1;
    } else{
        return 0;
    }
}

int isFull(){
    if (top == MAXSIZE){
        return 1;
    } else{
        return 0;
    }

}

char *peek(){
    return stack[top];
}

void push(char *value){
	strcpy(line, value);

    if(isFull() != 1){
        top++;
        strcpy(stack[top],line);
    } else{
        printf("STACK OVERFLOW");
    }
    
    
}

char *pop(){
    if(isEmpty() != 1){
        strcpy(line, stack[top]);
  		printf("%s\n",stack[top]);
        top--;
        strcpy(stack[top], NULL);
        return line;
    } else{
        printf("STACK IS EMPTY");
        return NULL;
    }
  
}
