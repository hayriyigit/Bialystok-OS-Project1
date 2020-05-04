#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int MAXSIZE = 19;
int top = -1;

char stack[20][1024];
char line[1024];
/**
 * returns size of stack
 * param: none
 * out: int size
*/
int size(){
    return MAXSIZE;
}
/**
 * determines whether stack is empty or not
 * param: none
 * out: 1 if empty, 0 if not
*/
int isEmpty(){
    if(top == -1){
        return 1;
    } else{
        return 0;
    }
}
/**
 * determines if stack is full or not
 * param: none
 * out: 1 if full, 0 if not
*/
int isFull(){
    if (top == MAXSIZE){
        return 1;
    } else{
        return 0;
    }

}
/**
 * checks top element in stack
 * param: none
 * out: char array of pointers, returns top value.
*/
char *peek(){
    return stack[top];
}
/**
 * adds new element to stack. 
 * param: char array of pointers, element
 * out; one
*/
void push(char *value){
	strcpy(line, value);

    if(isFull() != 1){
        top++;
        strcpy(stack[top],line);
    } else{
        top = 0;
        strcpy(stack[top],line);
    }
    
    
}
/**
 * returns element FIFO style
 * param: none
 * out: char array of pointers, value at top of stack
*/
char *pop(){
    if(isEmpty() != 1){
        strcpy(line, stack[top]);
        top--;
        strcpy(stack[top], NULL);
        return line;
    } else{
        
        return NULL;
    }
  
}