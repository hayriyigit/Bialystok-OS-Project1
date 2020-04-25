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

void help(){
  printf("Welcome to the example shell\n");
  printf("There is a list of builtin functions: \n");
  printf("history\ncd\nhelp\nexit\n");
}