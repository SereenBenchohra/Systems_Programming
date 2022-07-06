#ifndef GETINFO
#define GETINFO

#include <stdio.h>



typedef struct {
   char *input;
   char *output;
   int argc;

} Stage;
 

char **getWord(char *token);

void getInputOutput(char **listOfWords, Stage *stage);

#endif
