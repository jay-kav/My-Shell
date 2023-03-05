
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_NUM_ARGUMENTS 64
#define MAX_LEN 1024

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
            buffer[pos] = '\0'; //replace it with the NULL value
            return buffer;  //return the line 
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
//function Implementation found in: https://danishpraka.sh/posts/write-a-shell/#reading-user-commands

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
        tokens[position] = token;
        position++;

        if (position >= buffsize) {
            buffsize += 1024;
            tokens = realloc(tokens, buffsize * sizeof(char * ));

            if (!tokens) {
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \r\t\n");
    }

    tokens[position] = NULL;
    return tokens;
}
 //function referenced from: https://brennan.io/2015/01/16/write-a-shell-in-c/#split-line

 int internal_commands(char **args)
{
	// if no args, return to prompt
	if (args[0] == NULL) {
		return 1;
	}

	// loop and compare to each builtin function
	for (int i = 0; i < builtins_count(); i++)  /*todo */
	{
		if (!strcmp(args[0], builtin_str[i])) {
			return (*builtin_func[i])(args);
		}
	}
	
	return 1;
}
 
int external_commands(char **args) {  //TODO : tailor towards my program 
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
    // Child process
        if (execvp(args[0], args) == -1) {
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
    // Error forking
        perror("lsh");
    } else {
    // Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;

}
//https://brennan.io/2015/01/16/write-a-shell-in-c/#execute 