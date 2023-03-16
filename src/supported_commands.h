#ifndef SUPPORTED_COMMANDS_H
#define SUPPORTED_COMMANDS_H

//Function prototypes
int shell_cd(char **args);
int shell_clr(char **args);
int shell_dir(char **args);
int shell_environ(char **args);
int shell_echo(char **args);
int shell_help(char **args);
int shell_pause(char **args);
int shell_quit(char **args);
int builtins_count();

extern char *builtin_str[];
extern int (*builtin_func[]) (char **);

#endif


// TODO
// Add in acedemic integrity para
// figure i/o
// check comments
// add reference in man page
// memory leaks