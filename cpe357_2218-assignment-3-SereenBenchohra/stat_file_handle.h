//
// Created by sbenchoh on 12/28/21.
//

#ifndef INC_357_STAT_FILE_HANDLE_H
#define INC_357_STAT_FILE_HANDLE_H

#define STAT "/stat"
#define COMM "/comm"
#define FD   "/fd"

typedef struct
{
    unsigned int min;
    unsigned int sec;
}Time;


typedef struct
{
    char state;
    int ppid; // parent process id
    unsigned long stime;
    unsigned long utime;
} Stat_Info;

char *get_stat_File_path(char *proc_pid_dir_name, char *proc_path);
void print_every_pid_info(int len, struct dirent **entryList, char *proc_path);

#endif //INC_357_STAT_FILE_HANDLE_H
