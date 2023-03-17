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

#include "utility.h"
#include "supported_commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include "io_redirect.h"

#define MAX_NUM_ARGUMENTS 64
#define MAX_LEN 1024


void batchMode(char *filename){
    
    FILE *file;   //file pointer
    char arr[MAX_LEN];
    char** commands;

    file = fopen(filename, "r"); // opens batchfile

    if(file != NULL){ //checks if file is empty
        while(fgets(arr, MAX_LEN, file) != NULL){       //while loop gets one line at a time
            char ** commands = tokenise(arr);          //passes line to be tokenised
            io_red(commands);                         // sends the command to be checked for i\o redirection
        }
    } 
    else {                                           //error check
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fclose(file);     
}

//function Implementation found in: https://danishpraka.sh/posts/write-a-shell/#reading-user-commands
char* read_in_lines() {
    int buffsize = MAX_LEN;
    int pos = 0;
    char * buffer = malloc(sizeof(char) * buffsize);
    int c;

    if (!buffer) {  //error check malloc was able to assign memory 
        fprintf(stderr, "First Memory Allocation Failed\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        c = getchar();
        if (c == '\n' || c == EOF) {   //if char is an end of file or newline character
            buffer[pos] = '\0';       //replace it with the NULL value
            return buffer;           //return the line 
        } else {
            //otherwise there is more input 
            buffer[pos] = c;  
        }
        pos++; 
        //increment to prevent an infinite loop

        //if the position increases greater than alocated memory
        if (pos >= buffsize) { 
            buffsize += MAX_LEN;
            buffer = realloc(buffer, buffsize); // use realloc to increase the memory 

            if (!buffer) {  //error check to ensure successfull allocation
                fprintf(stderr, "Second Memory Allocation Failed\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    exit(EXIT_FAILURE); // Placed as a precausion although it should never be triggered
}

 //function referenced from: https://brennan.io/2015/01/16/write-a-shell-in-c/#split-line
 //information on how to apply strtok: https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
char** tokenise(char* line) {

    int buffsize = 1024, position = 0;
    char** tokens = malloc(buffsize* sizeof(char* ));
    char* token;

    if (!tokens) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }
    token = strtok(line, " \r\t\n"); //removes whitespaces, tabs and newline characters
    while (token != NULL) {
        tokens[position] = token;   //
        position++;

        //Checks if the memory is full
        if (position >= buffsize) {
            buffsize += 1024;
            tokens = realloc(tokens, buffsize * sizeof(char * )); //increases the size when full

            //Checks for error assigning memory to tokens
            if (!tokens) {
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \r\t\n");
    }

    tokens[position] = NULL; //adds Null to the end of the array
    return tokens;
}

 int internal_commands(char **args) {
	// if no args, return to prompt
	if (args[0] == NULL) {
		return 1;
	}

	// loop and compare to each builtin function
	for (int i = 0; i < builtins_count(); i++) 
	{
		if (!strcmp(args[0], builtin_str[i])) {
			return (*builtin_func[i])(args);
		}
	}
	
	external_commands(args);
    return 1;
}
 
//the function below was inspired from: https://brennan.io/2015/01/16/write-a-shell-in-c/#How shells start processes
int external_commands(char **args) {
    pid_t pid,wpid; 
    int status;

    //Method to get the last argument to check for & symbol
    int arg_count = 0;
    while (args[arg_count] != NULL) {
        arg_count++;
    }

    //Method checks if the last arg is the & symbol
     bool bg = false; 
    if (args[arg_count - 1] != NULL && strcmp(args[arg_count - 1], "&") == 0) {
        //sets background process to true
        bg = true;                    
        args[arg_count - 1] = NULL;  // removes & symbol so the command can execute 
    } 


    pid = fork();
    if (pid == 0) {
    // Child process
        if (execvp(args[0], args) == -1) {
            perror("Child process failed");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
    // Error forking
        perror("Error forking");
        exit(EXIT_FAILURE);
     } else {
        // Parent process
        //Checks if background processing is set to true
        if (bg) {
            // Background execution
            printf("[%d] %s running in background\n", pid, args[0]); // added in to support background processing 
            return 1;
        } else {
            // Foreground execution
            do {
                wpid = waitpid(pid, &status, WUNTRACED);  //waits for the child process to finish before executing 
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }

    return 1;
}