#include "mytar.h"

#ifndef CREATE_ARCHIVE
#define CREATE_ARCHIVE


void createArchive(Settings *settings, int numPaths);

void createHelper(char *parentPath, char *relPath, int verbose);

void writeHeader(char *path, char *relPath); 

void writeFile(char *relPath); 

void createPath(char *relPath, int verbose);

#endif
