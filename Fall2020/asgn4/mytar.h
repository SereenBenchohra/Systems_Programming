#ifndef MY_TAR
#define MY_TAR

#define NAME 0
#define MODE 100
#define UID 108
#define GID 116
#define SIZE 124
#define MTIME 136
#define CHKSUM 148
#define TYPEFLAG 156
#define LINKNAME 157
#define MAGIC 257
#define VERSION 263
#define UNAME 265
#define GNAME 297
#define DEVMAJOR 329
#define DEVMINOR 337
#define PREFIX 345
#define BLOCK_SIZE 512
#define PREFIX_LENGTH 155

typedef struct{

    int c;
    int t;
    int x;
    int S;
    int v;
    char **paths;  
    
    } Settings;




void executeCommand(int argc, char **argv, Settings *settings);

int isContained(char *name, char *match);


#endif
