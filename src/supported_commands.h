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
// figure i/o
// check comments
// add reference in man page
// memory leaks