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
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "utility.h"
#include "io_redirect.h"



int io_red(char **arg) {
    int input = 0;
    int output = 0;
    bool append = false;
    int ipos = 0, opos = 0;
    char* infile = NULL;
    char* outfile = NULL;
    int cut, status, i = 0;

    while(arg[i] != NULL ) {             //loops through array 
        if (strcmp(arg[i], "<") == 0) { // checks for the input symbol
            input = 1;                 //if found sets input to 1 
            ipos = i;                 // records its pos to be cut later
            infile = arg[i+1];       // saves the filename
        }

        else if (strcmp(arg[i], ">") == 0) { //checks for output symbol
            output = 1;                     //sets 1 for output when found 
            opos = i;                      //saves the pos to be cut later
            outfile = arg[i+1];           //saves filename
        }
        
        else if (strcmp(arg[i], ">>") == 0) {  //checks for the append output symbol
            output = 1;                       //sets 1 for output when found 
            append = true;                   //sets append to true so output doesnt overwrite 
            opos = i;                       //saves the pos to be cut later
            outfile = arg[i+1];            //saves filename
        }
        i++;
        
    }

    switch (input * 2 + output) { //swutch case to check for redirection
    case 0:                      // neither input or output redirection
        status = internal_commands(arg);
        break;      //stop the search 
    case 1:                      // output redirection only
        arg[opos] = NULL;       //removes the >> and filename
        status = file_out(arg, outfile, append); //calls output function
        break;
    case 2:                     // input redirection only
        arg[ipos] = NULL;      //removes the < and filename
        status = file_in(arg, infile, NULL, output, append); // passes null since output file doesn't exist
        break;
    case 3:                           // both input and output redirection
        arg[ipos] = NULL;             //removes the < and filename
        status = file_in(arg, infile, outfile, output, append); //calls input function
        break;
    }
    return status;
}

// implementation of freopen and /dev/tty: https://stackoverflow.com/questions/584868/rerouting-stdin-and-stdout-from-c
int file_in(char **arg , char* infile, char * outfile, int output, bool append) {
    FILE *file;
    int status;

    file = freopen(infile, "r", stdin);      //redirect input from the commandline to a file
    if(!file) {                             //check if the file was opened
        printf("Failed to open file\n");   // print error if not 
        exit(EXIT_FAILURE);
    }

    if(output > 0) {                                //check if output is redirected also
        status = file_out(arg, outfile, append);   // calls output function if so
    }
    else {
        status = internal_commands(arg);          //otherwise send arguments to the internal commands
    }
    
    fclose(file);                        //close file 
    freopen("/dev/tty", "r", stdin);    //redirect input back to the commandline
    return status;
}

// implementation of freopen and /dev/tty: https://stackoverflow.com/questions/584868/rerouting-stdin-and-stdout-from-c
int file_out(char **arg, char* outfile, bool append) {
    FILE *file;
    int status;

    if(append) {                                  //check if output was >>
        file = freopen(outfile, "a", stdout);    // if >> redirect output to a file but dont over write whats inside
    }
    else {
        file = freopen(outfile, "w", stdout);   // if > redirect output to a file and write whats inside
    }
    if(!file) {                            //check if the file could be opened
        printf("Failed to open file\n");  //print message if it was unable to be opened
        exit(EXIT_FAILURE);
    }

    status = internal_commands(arg);       //send the arguments to the internal_commands to be executed
    fclose(file);                         //close the file
    freopen("/dev/tty", "a", stdout);    // redirect the output back to the commandline
    
    return status;
}