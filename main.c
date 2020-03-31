#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

# define BUFFER_SIZE 256
# define ARG_BUFFER_SIZE 64
# define SPLIT_CHARS " \t\r\n\a"



char **splitLine(char *line){
	int bufsize = ARG_BUFFER_SIZE;
	int position = 0;

	char **tokens = malloc(bufsize*sizeof(char *)); // POINTER TO POINTER (POINTER FOR STORING POINTERS)
	char *token; // POINTER FOR HOLDING ANY ARG

	token = strtok(line, SPLIT_CHARS); // GET THE FIRST ARGUMENT (NAME OF THE PROGRAM)

	while(token != NULL){
		tokens[position] = token; // ADD POINTER OF ARGUMENT TO ARRAY OF POINTER
		position++;

		if(position >= bufsize){
			bufsize += ARG_BUFFER_SIZE;
			tokens = realloc(tokens, sizeof(char*)*bufsize); // EXTEND THE ALLOCATED MEMORY
		}

		token = strtok(NULL, SPLIT_CHARS); // GET OTHER SPLITTED ARGS 
	}

	tokens[position] = NULL;

	return tokens;
}


char *getLine(void){
	int bufsize = BUFFER_SIZE;
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

		if(position >= bufsize){
			bufsize += BUFFER_SIZE;
			ptr = realloc(ptr, bufsize);
		}
	}
}


void shell_loop(){
	char *line;
	char **args;

	char buf[BUFSIZ];
	char *cwd;

	int position = 0;

	while(1){
		cwd = getcwd(buf, sizeof(buf));
		printf("%s ➜ ",cwd);
		line = getLine();
		args = splitLine(line);
		while(position <=6){
			printf("%d : %s\n",position, args[position]);
			position++;
		}
		position = 0;

		free(line);
		free(args);
	};
}




int main(int argc, char *argv[]){

	shell_loop();
	return 0;
}
