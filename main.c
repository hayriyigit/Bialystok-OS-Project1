#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
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


int spawnProcess(char **args){
	printf ("This is the parent. PID=%d\n", getpid());

	pid_t childProcess = fork();
	int childStatus;

	//process success, inside child process.. 
	if ((int)childProcess == 0){
		printf("Child spawn: %d\n", getpid());

		if(execvp (args[0], args) == -1){
			printf("Command Not Found!\n");
			kill(getpid(), SIGTERM);
		}
		
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


void shell_loop(){
	char *line;
	char **args;

	while(1){
		printf("%s ➜ ", getenv("USER"));
		line = getLine();

		if ((int)*line == 0)
		{
			free(line);
			continue;
		}

		args = splitLine(line);
		spawnProcess(args);
		free(line);
		free(args);
	};
}


int main(int argc, char *argv[]){

	shell_loop();
	return 0;
}
