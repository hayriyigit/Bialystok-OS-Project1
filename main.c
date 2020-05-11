#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "writer.h"
#include "buildinfuncs.h"


#define BUFFER_SIZE 256
#define ARG_BUFFER_SIZE 64
#define SPLIT_CHARS " \t\r\n\a"
#define SIGINT 2 
#define SIGQUIT 3
/**
 * Splits a "string" by its spaces, returns char substrings 
 * param: a string separated by spaces
 * out: char array of pointers, a string
 */
char **splitLine(char *line){
	int bufsize = ARG_BUFFER_SIZE;
	int position = 0;

	char **tokens = malloc(bufsize*sizeof(char *)); 
	char *token; 

	token = strtok(line, SPLIT_CHARS); 

	while(token != NULL){
		tokens[position] = token; 
		position++;

		if(position >= bufsize){
			bufsize += ARG_BUFFER_SIZE;
			tokens = realloc(tokens, sizeof(char*)*bufsize);
		}

		token = strtok(NULL, SPLIT_CHARS); // GET OTHER SPLITTED ARGS 
	}

	tokens[position] = NULL;

	return tokens;
}
/**
 * Determines whether there is a blankspace in the provided line.
 * param: a string
 * out: 1 if it finds a space, 0 if not
*/
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

/**
 * Creates child process based on the first arg provided by a line. 
 * params: array of pointers that constructs a string, array of chars.
 * out: int that determines status of child process
*/
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
		 else if(strcmp(args[0],"exit")==0){
			printf("\033[1;31m");
			printf("\nExiting ShellEx\n");
			printf("\033[0m");
			
			int c_pid = getpid();
			int p_pid = getppid();
			kill(p_pid, SIGTERM);
		 	kill(c_pid,SIGTERM);
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

/**
 * constructs an array of chars (null terminated) and allocates memory for it.
 * param: void
 * out: returns array of pointers.
*/
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
/**
 * returns size of array, its size is detrmined until it finds a null pointer.
 * param: char array of pointers
 * out: size of array
*/
int getArrSize(char *arr){
	int counter = 0;
	char elem;
	do{
		counter++;
		
	}while(arr[counter] != 0);

	return counter;
}
/**
 * finds position in a char array of pointers of a substring.
 * param: array of pointers to be searched, starting position, search left to right or right to left, target char
 * out: position in char array of pointers
*/
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
/**
 * custom function to handle signal interrupt.
 * param: pid of process
 * out: void
*/

void handle_sigint(int pid) 
{ 
    printf("\0");
}
/**
 * custom function to handle signal quit
 * param: none
 * out: void
*/
void handle_sigquit(){
	printf("\033[1;31m");
	printf("\nExiting ShellEx\n");
	printf("\033[0m");
	exit(0);
}
  /**
   * prints a substring based on the index given, and prepends char ᐅ to substring
   * params: 
   * offset: starting position of substring
   * target: string to be given a substring
   * size: size of substring to be printed
   * out:
   * void
  */
void getSubstring(int offset, char* string, int size){
	printf(" %.*s ᐅ ", size, string + offset);
}

/**
 * logic lifecycle for terminal. it start an infinite loop until a sigquit is launched by user ctrl+\.
 * params: none
 * out: void
*/
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
		printf("\033[1;32m");
		printf("%s ➜ ", getenv("USER"));
		printf("\033[1;34m");
		getSubstring(firstPosLastDash + 1, cwd, endPos - firstPosLastDash);
		printf("\033[0m");
		
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

/**
 * main process
 * out: integer with status of process
*/
int main(int argc, char *argv[]){
	printf("\033[1;35m");
  	printf("Welcome to the ShellEx shell\n");
	  printf("\n");
	  printf("Type, “help” to see available commands.\n");
	printf("\033[0m");
	shell_loop();
	return 0;
}
