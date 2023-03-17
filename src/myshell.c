// Jamie Kavanagh
// ID: 21403382
// Acknowledgement of the DCU Academic Integrity Policy:
// I understand that the University regards breaches of academic integrity and plagiarism as grave 
// and serious. I have read and understood the DCU Academic Integrity and Plagiarism Policy. I accept
// the penalties that may be imposed should I engage in practice or practices that breach this policy. 
// I have identified and included the source of all facts, ideas, opinions and viewpoints of others
// in the assignment references. Direct quotations, paraphrasing, discussion of ideas from books,
// journal articles, internet sources, module text, or any other source whatsoever are acknowledged
// and the sources cited are identified in the assignment references. I declare that this material,
// which I now submit for assessment, is entirely my own work and has not been taken from the work of
// others save and to the extent that such work has been cited and acknowledged within the text of my
// work. I have used the DCU library referencing guidelines and/or the appropriate referencing system
// recommended in the assignment guidelines and/or programme documentation.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include "supported_commands.h"
#include "utility.h"
#include "io_redirect.h"

#define MAX_LEN 1024
#define MAX_NUM_ARGUMENTS 64

char shell[1024];

// how to use realpath: https://stackoverflow.com/questions/1563168/example-of-realpath-function-in-c
void create_environment(char** argv) {
    //get the path to the shell executable
    realpath(argv[0], shell);
    // set the PWD environment variable
    char* cwd = getcwd(NULL, 0);
    setenv("PWD", cwd, 1);
    setenv("HELP", cwd, 1); // use later for my help function
    free(cwd);
    //set the full path into shell 
    setenv("SHELL", shell, 1);
}

void make_prompt() {
    char prompt[100];
    snprintf(prompt, sizeof(prompt), "%s%s%s >> ", "\e[1;35m", getcwd(NULL, 1024), "\e[1;34m"); //format the prompt
    printf("%s", prompt); //print out the prompt
}

int main(int argc, char** argv) { 
    
    create_environment(argv);
   

    char *line;
    char **commands;
    int status = 1;
    
    //I have left this if statement outside the while loop as it would never been needed after the program has been run
    if (argc > 1) { //argv should only contain ./myshell unless a file is given which would increase the size from 1
        batchMode(argv[1]);
        exit(0);
    }

    

    //while loop inspiration from: https://brennan.io/2015/01/16/write-a-shell-in-c/#basic-loop-of-a-shell
     do {
        make_prompt(); 
        // read command line input
        line = read_in_lines(); //reads in the line from stdin
        
        commands = tokenise(line);   // seperates all the spaces and creates tokens for the line
        status = io_red(commands);  // sends to internal commands to check for i/o redirection
        
        free(line);
        free(commands);
    }while (status);
}
