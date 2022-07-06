#include<stdio.h>
#ifndef LAUNCHER_H
#define LAUNCHER_H
typedef struct
{
   int pFlag; /*initialize in main */
   int numProc;
   int procIndex;

} procData;

void inValidInput();

void checkIfP(int argc, char *argv[], procData* data); /* check valid
 * argument* for number  of processes */

void checkNuMArg(int argc);

void checkForChild(int argc, char *argv[], procData *data);

void parseFile(int argc, char *argv[], procData *data);
#endif
