#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include "utility.h"

//remove batch header and move to utility and remake read_file also finsih makefile to bin 

void batchMode(char *filename){ //todo: create a function to determine if batchmode is required
    
    FILE *file;
    char arr[MAX_LEN];
    char** commands;

    file = fopen(filename, "r"); // open the file

    if(file != NULL){
        while(fgets(arr, MAX_LEN, file) != NULL){
            char ** commands = tokenise(arr);         // parse the line using the splitline function as if the command was taken from the shell prompt
            printf("-%s-\n", *commands);                 // show what command you are running
            internal_commands(commands);                 // run the execute function to run the command
        }
    }

    fclose(file); 
}

