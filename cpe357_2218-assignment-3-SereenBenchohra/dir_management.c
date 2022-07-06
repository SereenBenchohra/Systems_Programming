#define _GNU_SOURCE
#include "dir_management.h"
#include <string.h>


FILE *open_file(const char *path, const char *mode)
{
    FILE *file = fopen(path, mode);
    if(file == NULL)
    {
        perror(path);
        exit(EXIT_FAILURE);
    }

    return file;
}

DIR *check_arguments(int argc, char *argv[]) // req 1
{

    DIR *dir;
    if(argc == 2 ) //   If provided, that argument is the directory to use as the root of the proc filesystem
    {
        dir = opendir(argv[1]);
        if(dir == NULL)
        {
            perror(argv[1]);
            exit(EXIT_FAILURE);
        }

    }
    else // If the argument is not provided, then use /proc
    {
        dir = opendir(PROC_PATH);

        if(dir == NULL)
        {
            perror("/Proc");
            exit(EXIT_FAILURE);

        }
    }

    return dir;
}

/*
   Requirement 2

   Process each process id (pid) entry in the proc directory. There may be additional entries in this directory;
   only those with numeric names should be processed. This entry name gives the pid necessary in the output.

*/

//checks if Directory is a numeric process id by checking if its an integer or not, if it is it returns TRUE
int is_integer(char *num_str)
{
    int isNum = TRUE;
    char *end, *local;
    local = num_str;
    strtol(local, &end, 10);
    // if not an integer return false
    if(end == local)
        isNum = FALSE;

    return isNum;
}

int getLength(DIR *dir)
{
    int len, isNum;
    struct dirent *entry;
    len = 0;

    while ((entry = readdir(dir)))
    {
        // check if its a numeric name
        isNum = is_integer(entry->d_name);
        if(isNum == TRUE)
            len++; // get length for allocation

    }

    rewinddir(dir); // resets the position of the directory stream dirp to the beginning of the directory

    return len;

}
// goes through the proc file and saves the numerical pid entries into a list
struct dirent **process_entries(DIR *dir)
{
    struct dirent *entry = NULL;
    struct dirent **entriesList = NULL;
    int len = getLength(dir);

    int isNum = 0 ;

    entriesList = malloc(sizeof(struct dirent*)* len);

    if(entriesList == NULL)
    {
        perror("entriesList");
        exit(EXIT_FAILURE);
    }

    rewinddir(dir); // resets the position of the directory stream dirp to the beginning of the directory
    int i = 0;

    while ((entry = readdir(dir)))
    {
        // check if its a numeric name
        isNum =  is_integer(entry->d_name);

        if(isNum == TRUE) // checks if entry is num, if so add to entries list
            entriesList[i++] = entry;

    }

    return entriesList;
}
// gets a memory allocated proc path to use for helper functions
char *get_proc_path(int argc, char *argv[])
{

    char *proc_path = NULL;

    if(argc == 2 ) //   If provided, that argument is the directory to use as the root of the proc filesystem
        proc_path = strdup(argv[1]);
    else // If the argument is not provided, then use /proc
        proc_path = strdup(PROC_PATH);

    return proc_path;
}