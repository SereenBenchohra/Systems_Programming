#include "dir_management.h"
#include "stat_file_handle.h"
// concatenates the the proc path/ pid_num/ and/ file to create a path to use
char *get_File_path(char *proc_pid_dir_name, char *proc_path, char *file_name)
{
    // concatenate string
    int proc_pid_len, folder_len, total, stat_len;
    stat_len = strlen(file_name);
    proc_pid_len = strlen(proc_pid_dir_name);
    folder_len = strlen(proc_path);
    total = folder_len + proc_pid_len + stat_len + 2;

    char *path = NULL;
    path = malloc(sizeof(char * )* total);
    sprintf(path, "%s%s%s", proc_path, proc_pid_dir_name, file_name);

    return path;

}
// configures the time to human readable minutes and time
Time configure_time(unsigned long stat_time)
{
    Time time;
    unsigned int totalSec;
    totalSec = stat_time/sysconf(_SC_CLK_TCK);
    time.min = totalSec / 60;
    time.sec = totalSec % 60;

    // divide utime and stime by sysconf(_SC_CLK_TCK)
    return time;
}

// Error: If the stat file cannot be read, then each of the above should be displayed as -.
// prints the State, ppid, utime, and Stime from the stat file
void print_stat_info(Stat_Info *statInfo)
{
    // The utime and stime should be displayed as minutes:seconds. As noted in the documentation, these values are
    // measured in clock ticks, so divide by sysconf(_SC_CLK_TCK) to get the number of seconds.
    Time utime = configure_time(statInfo->utime);
    Time stime = configure_time(statInfo->stime);

    printf("State: %c\n", statInfo->state);
    printf("Parent Process ID : %d\n", statInfo->ppid);
    printf("Utime: %im %is\n", utime.min, utime.sec);
    printf("Stime: %im %is\n", stime.min, stime.sec);

}

void print_null_stat_file()
{
    printf("State: -");
    printf("Parent Process ID : -\n");
    printf("Utime: - \n");
    printf("Stime: - \n");
    printf(" \n");


}

void get_indiv_stat_info(char *proc_pid_dir_name, char *proc_path)
{
    Stat_Info *statInfo = NULL;
    statInfo = malloc(sizeof(Stat_Info));

    // concatenate to open file
    char *stat_path = get_File_path(proc_pid_dir_name, proc_path, STAT);
    printf("%s\n", stat_path);

    printf(" \n");


    // if the stat file cannot be read, then each of the above should be displayed as -
    FILE *file = fopen(stat_path, "r");

    if(file == NULL) // if file doesnt exist print - for the requested entries
        print_null_stat_file();
    else // otherwise retrieve the State, ppid, utime, and stime from the stat file
    {
        fscanf(file, "%*d %*s %c %d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lu %lu",
               &statInfo->state, &statInfo->ppid, &statInfo->utime, &statInfo->stime);

        print_stat_info(statInfo);
        fclose(file);

    }

    free(statInfo);
    free(stat_path);

}

void get_command_name(char *proc_pid_dir_name, char *proc_path)
{
    // concatenate to open file
    char *comm_path = get_File_path(proc_pid_dir_name, proc_path, COMM);
    printf(" \n");

    printf("%s\n", comm_path); // prints path


    // if the stat file cannot be read, then each of the above should be displayed as -
    FILE *file = fopen(comm_path, "r");
    char comm_exec[100];

    if(file == NULL) // if comm file doesnt exist, print -
        printf("Command Name: -\n");
    else
    {   // otherwise , pritn the command name
        fscanf(file, "%s", comm_exec);
        printf("Command Name: %s\n", comm_exec);
        fclose(file);

    }
    printf(" \n");

    free(comm_path);

}

void get_fd_info(char *proc_pid_dir_name, char *proc_path)
{
    // open and concatenate the file path for fd
    char *fd_path = get_File_path(proc_pid_dir_name, proc_path, FD);
    printf("%s\n", fd_path);

    printf(" \n");

    DIR *dir = opendir(fd_path);
    if(dir == NULL) // if fd doesnt exist print unknown
        printf("fd: [unknown]\n");
    else
    {   // print file descriptors from the directory
        struct dirent *entry = NULL;
        while((entry = readdir(dir)))
           if(strcmp(entry->d_name, ".")  && strcmp(entry->d_name, "..") )
                printf("fd: %s\n", entry->d_name); // print if entry is a numerical file descriptor

        closedir(dir);
    }

    printf(" \n");

    free(fd_path);

}
// loops through every pid_num entry and gets the stat info, command name, and fd _info
void print_every_pid_info(int len, struct dirent **entryList, char *proc_path)
{
    int i;
    for(i = 0; i < len; i++)
    {
        get_indiv_stat_info(entryList[i]->d_name, proc_path);
        get_command_name(entryList[i]->d_name, proc_path);
        get_fd_info(entryList[i]->d_name, proc_path);
    }
}
