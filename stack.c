#include <stdio.h>

int MAXSIZE = 1024;
int top = -1;
char* stack[1024];


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

char* peek(){
    return stack[top];
}

void push(char* value){
    if(isFull() != 1){
        top++;
        stack[top] = value;
    } else{
        printf("STACK OVERFLOW");
    }
    
    
}

char* popStack(){
    if(isEmpty() != 1){
        char *value = stack[top];
        top--;
        stack[top] = NULL;
        return value;
    } else{
        printf("STACK IS EMPTY");
        return NULL;
    }
    
}
