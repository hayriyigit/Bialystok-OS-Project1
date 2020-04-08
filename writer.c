#include <stdio.h>


void writeFile(char *line){
    FILE *f = fopen("file.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    /* print some text */
    fprintf(f, "\n", line);
    fclose(f);

}

