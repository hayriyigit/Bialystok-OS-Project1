#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *getLine(void){
	int bufsize = 1024;
	char *ptr = malloc(sizeof(char) * bufsize);
	
	int position = 0;
	int c;

	while(1){
		c = getchar();
		
		if(c == EOF || c == '\n'){
			ptr[position] = '\0';
			return ptr;
		}
		else{
			ptr[position] = c;
		}
		position++;

	}
}

void lsh_loop(){
	char *line;	
	do{
		printf("> ");
		line = getLine();
		printf("Line is : %s\n", line);		
	}while(1);
}




int main(int argc, char *argv[]){

	lsh_loop();
	return 0;
}
