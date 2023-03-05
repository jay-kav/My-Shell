#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include "supported_commands.h"
#include "utility.h"
//#include "batch.h"

#define MAX_LEN 1024
#define MAX_NUM_ARGUMENTS 64

char shell[1024];

void create_environment(char** argv) {
    //get the path to the shell executable
    realpath(argv[0], shell);
    // set the PWD environment variable
    char* cwd = getcwd(NULL, 0);
    setenv("PWD", cwd, 1);
    free(cwd);
    //set the full path into shell 
    setenv("SHELL", shell, 1); //used for testing purposes
}
// how to use realpath: https://stackoverflow.com/questions/1563168/example-of-realpath-function-in-c

void make_prompt() {
    char prompt[100];
    snprintf(prompt, sizeof(prompt), "%s%s%s >> ", "\e[1;35m", getcwd(NULL, 1024), "\e[1;34m"); //format the prompt
    printf("%s", prompt); //print out the prompt
}

//TODO: Try another method to use envp
int main(int argc, char** argv, char** envp) { 
    
    create_environment(argv);
   
    //testing to ensure environment was set 
    /* char* pwd = getenv("PWD");
    char* shell = getenv("SHELL");
    if (pwd == NULL) {
        printf("PWD environment variable not set\n");
    } else {
        printf("PWD=%s\n", pwd);
    }
    if (shell == NULL) {
        printf("SHELL environment variable not set\n");
    } else {
        printf("SHELL=%s\n", shell);
    }
    return 0;*/

    char *line;
    char **commands;
    int status = 1;
    
    //I have left this if statement outside the while loop as it would never been needed after the program has been run
    if (argc > 1) { //argv should only contain ./myshell unless a file is given which would increase the size from 1
        //batchMode(argv[1]);
    }


     do {
        make_prompt(); 
        // read command line input
        line = read_in_lines();
        //printf("%s\n", line);
        commands = tokenise(line);
        //while ( *commands ) printf( "%s\n", *commands++ );
        status = internal_commands(commands);
        
        free(line);
        free(commands);
        //function inspiration from: https://brennan.io/2015/01/16/write-a-shell-in-c/#basic-loop-of-a-shell
    }while (status);
}
