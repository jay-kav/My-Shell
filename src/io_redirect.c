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
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "utility.h"
#include "io_redirect.h"



int io_red(char **arg) {
    bool input = false;
    bool output = false;
    bool append = false;
    int ipos = 0, opos = 0;
    char* infile = NULL;
    char* outfile = NULL;
    int cut, status, i = 0;

    while(arg[i] != NULL ) {
        if (strcmp(arg[i], "<") == 0) {
            input = true;
            ipos = i;
            infile = arg[i+1];
            // printf("%s\n", infile);
            // printf("%d\n", ipos);
        }
        else if (strcmp(arg[i], ">") == 0) {
            output = true;
            opos = i;
            outfile = arg[i+1];
        }
        
        else if (strcmp(arg[i], ">>") == 0) {
            output = true;
            append = true;
            opos = i;
            outfile = arg[i+1];
        }
        i++;
        
    }

    if(!input && output) {
        cut = opos;
    } else if (input) {
        cut = ipos;
        // printf("%d\n", ipos);
        // printf("%d\n", cut);
    }

    if(input || output) {
        arg[cut] = NULL;
    }

    if (input) {
        if (output) {
            status = file_in(arg, infile, outfile, output, append);
            // int j = 0;
            // while (arg[j] != NULL) {
		    //     printf("%s\n", arg[j]);
            //     ++j;
	        // }
        }
        else{
            status = file_in(arg, infile, NULL, output, append);
            // int j = 0;
            // while (arg[j] != NULL) {
		    //     printf("%s\n", arg[j]);
            //     j++;
	        // }
        }
    }
    else if (output && !input) {
        status = file_out(arg, outfile, append);
        // int j = 0;
        //     while (arg[j] != NULL) {
		//         printf("%s\n", arg[j]);
        //         ++j;
	    //     }
    }
    else if (!output && !input) {
        status = internal_commands(arg);
    }
    return status;
}

int file_in(char **arg , char* infile, char * outfile, bool output, bool append) {
    return 1;
}

// implementation of freopen and /dev/tty: https://stackoverflow.com/questions/584868/rerouting-stdin-and-stdout-from-c
int file_out(char **arg, char* outfile, bool append) {
    FILE *file;
    int status;

    if(append) {
        file = freopen(outfile, "a", stdout);
    }
    else {
        file = freopen(outfile, "w", stdout);
    }
    status = internal_commands(arg);
    fclose(file);
    freopen("/dev/tty", "a", stdout);
    
    return status;
}