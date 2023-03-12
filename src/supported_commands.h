#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <dirent.h> 
#include <string.h>
//#include <libgen.h>


//Function prototypes for builtin shell commands:

int shell_cd(char **args);
int shell_clr(char **args);
int shell_dir(char **args);
int shell_environ(char **args);
int shell_echo(char **args);
int shell_help(char **args);
int shell_pause(char **args);
int shell_quit(char **args);

//List of builtin commands, followed by their corresponding functions.

char *builtin_str[] = {
  "cd",
  "clr",
  "dir",
  "environ",
  "echo",
  "help",
  "pause",
  "quit"
};

int (*builtin_func[]) (char **) = {
  &shell_cd,
  &shell_clr,
  &shell_dir,
  &shell_environ,
  &shell_echo,
  &shell_help,
  &shell_pause,
  &shell_quit
};

// design from: https://brennan.io/2015/01/16/write-a-shell-in-c/#shell-builtins
//used to get num of commands to loop through all them
int builtins_count() {
  return sizeof(builtin_str) / sizeof(char *);
}
// C implementation of each command 

//cd:
int shell_cd(char **args) {
    if (args[1] == NULL) {   // this is when cd isn't given a directory to change to 
		printf("%s\n", getenv("PWD")); //returns the current working directory
	}
	else if (chdir(args[1]) != 0) { //chdir should return 0 if successful
		perror("chdir() failed");
	}
	else {
        char* cwd = getcwd(NULL, 0); // if cd given a directory to change to
        setenv("PWD", cwd, 1); //change the PWD to the current directory 
        free(cwd);
	}
    return 1;
}
// how to use chdir: https://www.geeksforgeeks.org/chdir-in-c-language-with-examples/

//clears terminal
int shell_clr(char **args) {
    system("clear");  //TODO fix
    return 1;
}

//DIR
//function below referenced from: https://c-for-dummies.com/blog/?p=3246
//implementation inspired from: https://stackoverflow.com/questions/4204666/how-to-list-files-in-a-directory-in-a-c-program
int shell_dir(char **args) {  
    DIR *folder; //pointer to a directory structure
    struct dirent *dir; //creates a dirent stucture datatype
    if (!args[1]) {
        folder = opendir("."); //opens CWD if no args given
    } else {
        folder = opendir(args[1]); // opens the directory of the given agument 
    }


    if (!folder) { //checks if folder was able to be created
        perror("Unable to read directory");
        return 1; //does not break shell prompt
    }
    while ((dir = readdir(folder)) != NULL) { //reads folder until it returns nulll
      printf("%s\n", dir->d_name); //p  rints names of all directorys in the directory
    }
    closedir(folder); //closes the pointer
  
    return 1;
}

//Environ
//function below inspiration from: https://www.geeksforgeeks.org/c-program-print-environment-variables/
//how to access environ: cchttps://stackoverflow.com/questions/4291080/print-the-environment-variables-using-environ
    int shell_environ(char **args) {
    //origionally tried accessing the char** envp in main as seen in the first link below but was unable 
    extern char** environ;  // now i access the variable environ from the unistd.h library 
    
    while(*environ != NULL ) { //loop through the strings in environ until Null
        printf("%s\n", *environ); //print line by line 
        environ++; //increment through the list
    }
    return 1;
}

//Echo
int shell_echo(char **args) { //TODO : figure out how to add in multiple spaces and tabs
    int i = 1;
    while(args[i] != NULL) {
        printf("%s ", args[i]);
        i++;
    }
    printf("\n");
    return 1;
}

//Help
int shell_help(char **args) { //TODO make it be able to be accessed no matter the dir
    system("cat ../manual/readme.md");  //calls the more function to display the readme in a page by page format
    printf("\n");
    return 1;
}

//Pause
int shell_pause(char **args) { 
    printf("Process has been paused please click 'Enter' to unpause");
    while(getchar()!='\n'); //runs an infinite loop until a newline character is detected
    return 1;
}

//Quit
int shell_quit(char **args) {
    return 0;
}