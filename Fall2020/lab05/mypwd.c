#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <limits.h>

int main()
{
    char current[PATH_MAX], path[PATH_MAX], slash[PATH_MAX];  /* folder name */
    DIR *dir;

    ino_t curIno, prevIno;  
    struct stat statBuffer;  
    struct dirent *fileInfo;
    while (1)
    {  
        dir= opendir(".");
        if(dir == NULL) {
            fprintf(stderr, "cannot get current directory.\n");
            exit(EXIT_FAILURE);
        }
        /* read  on current  folder */
        fileInfo = readdir(dir);

        lstat(fileInfo->d_name, &statBuffer);
        curIno = statBuffer.st_ino;
        closedir(dir);

        /* go to previous directory */

        chdir("..");            
        dir = opendir(".");

        fileInfo = readdir(dir);
        lstat(fileInfo->d_name, &statBuffer);
        prevIno = statBuffer.st_ino;

        if(curIno == prevIno) 
            break;
         else 
         {
            strcpy(slash, "/");
            strcpy(current, fileInfo->d_name);
            strcat(slash, current);  
            strcat(slash, path);     

            if(strlen(slash)  >= PATH_MAX) {
                fprintf(stderr, "Error! Path too long!\n");
                exit(EXIT_FAILURE);
            }          
            strcpy(path, slash);
        }
        closedir(dir);
    }

    printf("%s\n", path);
    return 0;
}
