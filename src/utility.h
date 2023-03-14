#ifndef UTILITY_H
#define UTILITY_H

char* read_in_lines();
char** tokenise(char* line);
int internal_commands(char **args);
int external_commands(char **args);
void batchMode(char *filename);

#endif
