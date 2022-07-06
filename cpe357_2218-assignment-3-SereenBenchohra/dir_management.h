//
// Created by sbenchoh on 12/28/21.
//


#ifndef INC_357_DIR_MANAGEMENT_H
#define INC_357_DIR_MANAGEMENT_H

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <sys/types.h>
#include <string.h>


#define PROC_PATH "/proc/"
#define TRUE  1
#define FALSE 0

FILE *open_file(const char *path, const char *mode);
DIR *check_arguments(int argc, char *argv[]); // req 1
int is_integer(char *num_str);
int getLength(DIR *dir);
struct dirent **process_entries(DIR *dir);
char *get_proc_path(int argc, char *argv[]);





#endif //INC_357_DIR_MANAGEMENT_H
