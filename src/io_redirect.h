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

#ifndef IO_REDIRECT_H
#define IO_REDIRECT_H

int io_red(char **arg);
int file_in(char **arg, char* infile, char* outfile, bool output, bool append);
int file_out(char **arg, char* outfile, bool append);


#endif