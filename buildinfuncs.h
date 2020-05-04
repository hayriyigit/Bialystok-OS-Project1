/**
 * Reads file that contains the last 20 commands. reads until eof or null terminated.
 * param: none
 * out: void
*/
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
/**
 * change directory command, expects string. 
 * returns int with status of process
*/
int cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "shell: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("shell");
    }
  }
  return 1;
}
/**
 * prints list of functions!
 * param: none
 * out: none
*/
void help(){
  printf("\033[1;35m");
  printf("Welcome to the ShellEx shell\n");
  printf("There is a list of builtin functions: \n");
  printf("You can use this shell as a normal Linux terminal (hopefully!) \n");
  printf("\033[1;36m");
  printf("history\ncd\nhelp\nexit\n");
  printf("\033[0m");
}