#ifndef ARCHIVELIST_H
#define ARCHIVELIST_H

#define PERMISSIONS 0
#define OWNER 10
#define GROUP 27
#define E_SIZE 44
#define E_MTIME 52
#define E_LENGTH 68

void tableArchive(Settings *setting, int numPaths);

void printEntry(char *header, int verbose, char **matches, int numPaths);

#endif
