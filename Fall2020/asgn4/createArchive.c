#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "createArchive.h"
#include "mytar.h"
#include "nicoFuncts.h"

static FILE *archive;
static int strict; /* if i had more time I'd make settingss fully global */

void createArchive(Settings *settings, int numPaths){
    int i;
    char emptyBlock[BLOCK_SIZE];

    strict = settings->S;

    /* opens the archive */
    if((archive = fopen(settings->paths[0], "w")) == NULL){
        fprintf(stderr, "createArchive: Failed to open path %s\n",
                         settings->paths[0]);
        exit(EXIT_FAILURE);
    }

    /* iterates through ever cl argument */
    for(i = 1; i < numPaths + 1; i++){
        createPath(settings->paths[i], settings->v);  
    }
    for(i = 0; i < BLOCK_SIZE; i++){
        emptyBlock[i] = '\0';
    }
    
    fwrite(emptyBlock, 1, BLOCK_SIZE, archive);
    fwrite(emptyBlock, 1, BLOCK_SIZE, archive);
}



void createPath(char *relPath, int verbose){ 
    struct stat entreeStat;
    char *path;

    if((lstat(relPath, &entreeStat)) == -1){
        return;
    }

    if((path = (char *)calloc((strlen(relPath) + 2), 1)) == NULL){
            fprintf(stderr, "createArchive-createHelper: failed to malloc");
            exit(EXIT_FAILURE);
    }
    strcpy(path, relPath);

    /* branches dependent on file type */
    if(S_ISLNK(entreeStat.st_mode)){
        if(verbose){
            printf("%s\n", path);
        }
        writeHeader(path, relPath);
    }        
    else if(S_ISREG(entreeStat.st_mode)){
        if(verbose){
            printf("%s\n", path);
        }
        writeHeader(path, relPath);
        writeFile(relPath);
    }               
    else if(S_ISDIR(entreeStat.st_mode)){
        strcpy(path + strlen(path), "/");
        if(verbose){
            printf("%s\n", path);
        }
        writeHeader(path, relPath);
        createHelper(path, relPath, verbose);              
    }

    return;
}


/* this is the recursive function that essential DFS the directory */
void createHelper(char *parentPath, char *relPath, int verbose){
    
    char *path;
    DIR *directory;
    struct dirent *dirEntree;
    struct stat entreeStat;

    if((directory = opendir(relPath)) == NULL){
        fprintf(stderr,
                "createArchive-createHelper: Failed to open directory: %s\n",
                relPath);
            exit(EXIT_FAILURE); 
    }
    if(chdir(relPath) == -1){
        fprintf(stderr,
                "createArchive-createHelper: Failed to change directory\n");
        exit(EXIT_FAILURE);
    }

    while((dirEntree = readdir(directory)) != NULL){
            
        if(strcmp(dirEntree->d_name, ".") == 0){ 
            continue;
        }
        if(strcmp(dirEntree->d_name, "..") == 0){ 
            continue;
        }
            
        if((lstat(dirEntree->d_name, &entreeStat)) == -1){
            fprintf(stderr,
        "createArchive-createHelper: Failed to stat: %s", dirEntree->d_name);
            exit(EXIT_FAILURE);
        }
 
        /*constructs the path */
        if((path = (char *)calloc((strlen(parentPath) +
            strlen(dirEntree->d_name) + 2), 1)) == NULL){
            fprintf(stderr, "createArchive-createHelper: failed to malloc");
            exit(EXIT_FAILURE);
        }
        strcpy(path, parentPath);
        strcpy(path + strlen(path), dirEntree->d_name);
        
        /* links just have a header */ 
        if(S_ISLNK(entreeStat.st_mode)){
            if(verbose){
                printf("%s\n", path);
            }
            writeHeader(path, dirEntree->d_name);
            free(path);
            continue;
        }
        /*regular files just have a header */
        else if(S_ISREG(entreeStat.st_mode)){ 
            if(verbose){
                printf("%s\n", path);
            }
            writeHeader(path, dirEntree->d_name);
            free(path);
            writeFile(dirEntree->d_name);
            continue;
        }           
        /* directories have a header and recursive call */    
        else if(S_ISDIR(entreeStat.st_mode)){
            strcpy((path + strlen(path)), "/");
            if(verbose){
                printf("%s\n", path);
            }
            writeHeader(path, dirEntree->d_name);
            createHelper(path, dirEntree->d_name, verbose);
            free(path);
            continue;
        }   
    }
    if(chdir("..") == -1){
        fprintf(stderr,
            "createArchive-createHelper: Failed to change directory\n");
        exit(EXIT_FAILURE);
    }

}


void writeHeader(char *path, char *relPath){
    
    struct stat entreeStat;
    int i, pathLength, sum, breakPoint;
    struct passwd *pw;
    struct group *gr;
    char block[BLOCK_SIZE];
    unsigned char buff;

    for(i = 0; i < BLOCK_SIZE; i++){
        block[i] = '\0';
    }
    
    if((lstat(relPath, &entreeStat)) == -1){
        fprintf(stderr, "createArchive-writeHeader: Failed to stat");
        exit(EXIT_FAILURE);
    }

    /* name */

    pathLength = strlen(path);;
    
    if(pathLength > MODE){
        if(pathLength > (MODE + PREFIX_LENGTH + 1)){
            fprintf(stderr, "createArchive-writeHeader: Path too long");
            exit(EXIT_FAILURE);
        }
        breakPoint = pathLength - 101;
        while(path[breakPoint] != '/'){
            breakPoint++;
            if(breakPoint > PREFIX_LENGTH){
                fprintf(stderr, "createArchive-writeHeader: Path too long");
                exit(EXIT_FAILURE);
            }
        } /* from 0 to bp-1 is the prefix. bp+1 to pathLength is name */
        path[breakPoint] = '\0';
        strcpy((block + PREFIX), path);
        strcpy((block + NAME), (path + breakPoint + 1));
        path[breakPoint] = '/';
    }
    else{
        strcpy((block + NAME), path);
    }    

    /* mode */
 
    sprintf((block + MODE), "%07o", (int) (entreeStat.st_mode & 0x00000fff));

    /* uid */
    
    if(strict){
        fprintf(stderr, "will create bad tar files with school IDs");
        exit(EXIT_FAILURE);
    }


    if(insert_special_int((block + UID), (GID - UID), entreeStat.st_uid) != 0){
        fprintf(stderr, "createArchive-writeHeader: failed to format uid");
        exit(EXIT_FAILURE);
    }

    /* gid */

    sprintf((block + GID), "%07o", (int) entreeStat.st_gid);
 
    /* size */
        
    if(S_ISLNK(entreeStat.st_mode) || S_ISDIR(entreeStat.st_mode)){

        strcpy((block + SIZE), "00000000000");

    }
    else{

        sprintf((block + SIZE), "%011o", (int) entreeStat.st_size); 
    }

    /* time */
    
    sprintf((block + MTIME), "%011o", (int) entreeStat.st_mtime);  
    
    /* check sum at the end! */

    strcpy((block + CHKSUM), "        ");
        
    /* typeflag */ 

    if(S_ISLNK(entreeStat.st_mode)){

        strcpy((block + TYPEFLAG), "2");
    }
    else if(S_ISDIR(entreeStat.st_mode)){

        strcpy((block + TYPEFLAG), "5");
    }
    else if(S_ISREG(entreeStat.st_mode)){

        strcpy((block + TYPEFLAG), "0");
    }
 
    /* linkname */
        
    if(S_ISLNK(entreeStat.st_mode)){
        
        if(readlink(relPath, (block + LINKNAME), (MAGIC - LINKNAME)) == -1){
            perror("createArchive-writeHeader: readlink error");  
            exit(EXIT_FAILURE);        
        }    
    }

    /* Magic */

    strcpy((block + MAGIC), "ustar");
    
    /* Version */

    strcpy((block + VERSION), "00");

    /* uname */ 

    pw = getpwuid(entreeStat.st_uid);
    strcpy((block + UNAME),pw->pw_name);
   
    /* gname */
 
    gr = getgrgid(entreeStat.st_gid);
    strcpy((block + GNAME),gr->gr_name);

    /* devmajor
    if we were doing special files:
    sprintf((block + DEVMAJOR), "%07o", major(entreeStat.st_dev)); */
    /* devminor
    if we were doing special files:
    sprintf((block + DEVMAJOR), "%07o", major(entreeStat.st_dev)); */

    /* prefix -> look @name */
 
    /* finish size check */

    sum = 0; 
    for(i = 0; i < BLOCK_SIZE; i++){
        buff = block[i]; /* ugly tweek that saves a lot of needed time */
        sum += buff;
    }
    
    sprintf((block + CHKSUM), "%07o", sum);

    fwrite(block, 1, BLOCK_SIZE, archive);

}



void writeFile(char *relPath){
    FILE *input;
    struct stat entreeStat;
    int blocks, i;
    char buffer[BLOCK_SIZE];
    
    for(i = 0; i < BLOCK_SIZE; i++){
        buffer[i] = '\0';
    }

    if((input = fopen(relPath, "r")) == NULL){
        fprintf(stderr, "createArchive-writeFile: Failed to open path: %s\n",
                    relPath);
        exit(EXIT_FAILURE);
    }
 
    if((lstat((relPath), &entreeStat)) == -1){
        fprintf(stderr, "createArchive-writeFile: Failed to stat\n");
        exit(EXIT_FAILURE);
    }

    /* calc num of blocks to be written */
    blocks = (entreeStat.st_size / BLOCK_SIZE);
    
    if((entreeStat.st_size % BLOCK_SIZE) != 0){
        blocks++;
    }
    
    for(i = 0; i < blocks - 1; i++){
        fread(buffer, 1, BLOCK_SIZE, input);
        fwrite(buffer, 1, BLOCK_SIZE, archive);
    }
 
    /* last block is special cause it must be filed with NULLS in left over */
    for(i = 0; i < BLOCK_SIZE; i++){
        buffer[i] = '\0';
    }
    fread(buffer, 1, BLOCK_SIZE, input);
    fwrite(buffer, 1, BLOCK_SIZE, archive);

    fclose(input);

}


