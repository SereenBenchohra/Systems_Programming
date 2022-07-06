#include "hashTable.h"

#ifndef UI_H
#define UI_H

void printMostFrequent(Node **sortedList, int parseNum, int numEntries);

FILE* fileOpen(const char *fname, int *isValid);

int parseNum(int argc, char *argv[], int *nflag);
 

#endif
