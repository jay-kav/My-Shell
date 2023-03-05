#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include "supported_commands.h"
#include "utility.h"
//remove batch header and move to utility and remake read_file

void batchMode(char *filename){ //todo: create a function to determine if batchmode is required

    char* line;
    char** commands;
    int i = 0;

    line = read_file(filename);

    while(line[i] != NULL) {
        commands = tokenise(line);
        internal_commands(commands);
        i++;
    }

    free(line);
    free(commands);
    exit();
}

char** read_file(char *filname) { //TODO:  //week11 284
    FILE *pfile = NULL;
    pfile = fopen(filename, "r");
    if(!pfile)
        printf("Failed to open %s.\n", filename);

    
    return ;

}