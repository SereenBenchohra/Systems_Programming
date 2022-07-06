#ifndef INC_357_FILEHANDLE_H
#define INC_357_FILEHANDLE_H

#define VALID_ARGUMENTS 3
#define BUFFER 4096

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct node{
    char *filename;
    char *URL;
    char *sec; // make into string as well
}Down_Info;


int verify_arguments(int argc, char *argv[]);
FILE *open_file(const char *path, const char *mode);
int get_array_length(FILE *file);
Down_Info **retrieve_data(FILE *file, int array_len );
//void deleteList(Down_Info ** head_ref);
void free_list(Down_Info **list, int len);

#endif //INC_357_FILEHANDLE_H
