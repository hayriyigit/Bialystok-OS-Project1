#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include <ctype.h>
#include<sys/types.h>
#include <sys/wait.h>
#include "writer.h"
#include "buildinfuncs.h"


#define BUFFER_SIZE 256
#define ARG_BUFFER_SIZE 64
#define SPLIT_CHARS " \t\r\n\a"
#define SIGINT 2 
#define SIGQUIT 3

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

int isBlank(char *line)
{
	int n = (int) strlen(line);
	int i;

	for (i = 0; i < n; i++) {
		if (!isspace(line[i]))
			return 0;
	}
	return 1;
}


int spawnProcess(char **args){
	pid_t childProcess = fork();
	int childStatus;

	//process success, inside child process.. 
	if ((int)childProcess == 0){

		if(strcmp(args[0],"history")==0){
		 	readFile();
		 }
		else if(strcmp(args[0],"cd")==0){
		 	cd(args);
		 }
		else if(strcmp(args[0],"help")==0){
		 	help();
		 }
		else if(execvp (args[0], args) == -1){
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
			//addline to stack
			if(!isBlank(ptr)){
        		push(ptr);
				writeFile();
			}
			
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

int getArrSize(char *arr){
	int counter = 0;
	char elem;
	do{
		counter++;
		
	}while(arr[counter] != 0);

	return counter;
}

int getCharPos(char *arr, int position, int reverse, char target){
	if(reverse == 1){
		do{
			position--;
		}while(arr[position] != target);
		return position;
	} else if(reverse == 0){
		do{
			position++;
		}while(arr[position] != target);
		return position;
	} else{
		printf("Unproper use of getDashPos, check params!");
		exit(-1);
	}
	
}

void handle_sigint(int pid) 
{ 
    printf("\0");
}

void handle_sigquit(){

	exit(0);
}
  
void getSubstring(int offset, char* thing, int size){
	printf(" %.*s ᐅ ", size, thing + offset);
}


void shell_loop(){
	char *line;
	char **args;
	char buf[BUFSIZ];
	char *cwd;
	while(1){
		cwd = getcwd(buf, sizeof(buf));
		int size = getArrSize(cwd);
		int firstPosLastDash = getCharPos(cwd, size, 1, '/');

		int endPos = getCharPos(cwd, size, 1, 0);
		
		printf("%s ➜ ", getenv("USER"));
		getSubstring(firstPosLastDash + 1, cwd, endPos - firstPosLastDash);
		
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
		line = getLine();
		
		if (isBlank(line))
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
