#ifndef EXECCOMMANDS_H
#define EXECCOMMANDS_H

#include <stdio.h>

int checkforPipes(char **parsedLine);

void exec_system(char **parsedLine);


void exec_piped(char ** parsedLine, int npipes);
#endif

