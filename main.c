#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include <sys/wait.h>

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


int spawnProcess(char* program, char* line[]){
	pid_t childProcess = fork();
	int childStatus;
	//process success, inside child process.. 
	if ((int)childProcess == 0){
		printf("Child spawn: %d\n", (int) childProcess);
		execvp (program, line);
		printf("Something went wrong pal..\n");
	} 
	//process fail
	else if ((int) childProcess < 0){
		fprintf(stderr, "Fork failed");
		exit(-1);
	//we inside parent...		
	} else if ((int) childProcess > 0){
		pid_t parent;
		do{
			parent = wait(&childStatus);
			if(parent != childProcess){
				printf("Process is gone to heaven, or something.");
			}
		} while(parent != childProcess);
		return childStatus;
	}

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


void lsh_loop(){
	char *line;
	char **args;
	int position = 0;
	while(1){
		printf("➜ ");
		line = getLine();
		args = splitLine(line);
		while(position <=6){
			printf("%d : %s\n",position, args[position]);
			position++;
		}
		position = 0;
		spawnProcess(line, args);
		free(line);
		free(args);
	};
}




int main(int argc, char *argv[]){

	lsh_loop();
	return 0;
}
