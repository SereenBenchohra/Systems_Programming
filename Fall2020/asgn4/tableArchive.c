#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#include  <stdlib.h>
#include  <stdio.h>
#include  <string.h>
#include  <time.h>

#include  "mytar.h"
#include  "tableArchive.h"

static int badFile;

void tableArchive(Settings *settings, int numPaths){
    FILE *archive;
    int sum, j, expectedSum, qCheck;
    char buff[BLOCK_SIZE], sumBuff[(TYPEFLAG - CHKSUM)], *end;
    unsigned char uchar;
    
    badFile = 0;
    if((archive = fopen(settings->paths[0], "r")) == NULL){
        fprintf(stderr, "tableArchive: failed to open");
        exit(EXIT_FAILURE);
    }
       
    while((qCheck = fread(buff, 1, BLOCK_SIZE, archive)) == BLOCK_SIZE){
        
        /* verifying the chksum */
        strncpy(sumBuff, (buff + CHKSUM), (TYPEFLAG - CHKSUM));
        expectedSum = strtol(sumBuff, &end, 8); 
        if(*end){
            continue;
        }
        if(expectedSum == 0){
            continue;
        }
        sum = ' ' * 8;
        for(j = 0; j < CHKSUM; j++){
            uchar = buff[j];
            sum += uchar;
        }
        for(j = TYPEFLAG; j < BLOCK_SIZE; j++){
            uchar = buff[j];
            sum += uchar;
        
        }   
        /* Strict Compliance */
        if(settings->S){
            /* check magic number */
            j = strlen(buff + MAGIC);
            if(j > 5 || j == 0){
                fprintf(stderr, "Not strict compliant");
                exit(EXIT_FAILURE);
            }
            if(buff[MAGIC + j] != '\0'){
                fprintf(stderr, "Not strict compliant");
                exit(EXIT_FAILURE);
            }
            /* check version number */    
            if(buff[VERSION] != '0' || buff[VERSION + 1] != '0'){
                fprintf(stderr, "Not strict compliant");
                exit(EXIT_FAILURE);
            }
        }
 
        if(sum == expectedSum){   
            printEntry(buff, settings->v, settings->paths, numPaths);
        }
    }
    /* checks that the tar file is legit */
    if(qCheck != 0){
        fprintf(stderr, "bad tar file: incomplete blocks");
        exit(EXIT_FAILURE);
    }
    fclose(archive);

    if(badFile == 0){
        fprintf(stderr, "bad tar file: no valid headers");
    }  
}

void printEntry(char *header, int verbose, char **matches, int numPaths){
    char mode[8], *end, *name;
    char perms[11], owgr[34], size[13], mtime[17];
    int permissions, i, split, sizeVal;
    struct tm *date;
    time_t time;
   
    /* Prefix + Name */
        
    if((name = (char *)calloc(PREFIX_LENGTH + (MODE - NAME) + 2, 1)) == NULL){
        fprintf(stderr, "tableArchive-printEntree: failed to calloc");
        exit(EXIT_FAILURE);
    }
    if(strlen(header + PREFIX) != 0){
        strcpy(name, (header + PREFIX));
        strcpy((name + strlen(name)), "/");   
    }
    strncpy((name + strlen(name)), (header + NAME), (MODE - NAME));

    for(i = 1; i < numPaths; i++){
        /* makes sure that it should be printed, in the path */
        if(isContained(name, matches[i])){
            break;
        }
    }
    if(i == numPaths && i != 1){
        return;
    }

    badFile = 1;
    /* permissions */
    
    strncpy(mode, (header + MODE), (UID - MODE));
    permissions = strtol(mode, &end, 8);
 
    if(*end){
        fprintf(stderr, "tableArchive-printEntry: Failed to strtol (perm)");
        exit(EXIT_FAILURE);
    }
    
    if(header[TYPEFLAG] == '5'){
        perms[0] = 'd';
    }
    else if(header[TYPEFLAG] == '2'){
        perms[0] = 'l';
    }
    else if(header[TYPEFLAG] == '\0' || header[TYPEFLAG] == '0'){
        perms[0] = '-';
    }
    else{  
        fprintf(stderr, "tableArchive.c-printEntry: file type not supported");
        exit(EXIT_FAILURE);
    }

    /* pretty simple bitwise logic to set the characters */
    perms[1] = (permissions & S_IRUSR) ? 'r' : '-';
    perms[2] = (permissions & S_IWUSR) ? 'w' : '-';
    perms[3] = (permissions & S_IXUSR) ? 'x' : '-';
    perms[4] = (permissions & S_IRGRP) ? 'r' : '-';
    perms[5] = (permissions & S_IWGRP) ? 'w' : '-';
    perms[6] = (permissions & S_IXGRP) ? 'x' : '-';
    perms[7] = (permissions & S_IROTH) ? 'r' : '-';
    perms[8] = (permissions & S_IWOTH) ? 'w' : '-';
    perms[9] = (permissions & S_IXOTH) ? 'x' : '-';
    perms[10] = '\0';
    
    /* owner */ 
    
    for(i = 0; i < 34; i++){
        owgr[i] = '\0';
    }

    split = strlen(strcpy(owgr, (header + UNAME)));
    strcpy((owgr + strlen(owgr)), "/");  
    split++;
    
    /* group */

    strncpy((owgr + split), (header + GNAME), (34 - split));

    /* Size (E_SIZE) MTIME*/

    strncpy(size, (header + SIZE), (MTIME - SIZE));
    size[12] = '\0';    

    sizeVal = strtol(size, &end, 8); 
    if(*end){
        fprintf(stderr, "tableArchive-printEntry: Failed to strtol (time)");
        exit(EXIT_FAILURE);
    }
    /* sprintf(size, "%s", sizeVal); */


    /* Mtime */
    
    strncpy(mtime, (header + MTIME), (CHKSUM - MTIME)); 
    mtime[CHKSUM - MTIME] = '\0';

    time = (time_t) strtol(mtime, &end, 8); 
    if(*end){
        fprintf(stderr, "tableArchive-printEntry: Failed to strtol (time)");
        exit(EXIT_FAILURE);
    }
    
    date = localtime(&time);
       
    strftime(mtime, (E_LENGTH - E_MTIME + 1), "%Y-%m-%d %H:%M", date);

    mtime[E_LENGTH] = '\0';    

        
    /* print */
    
    if(verbose){   
        printf("%s %s %14d %s %s\n", perms, owgr, sizeVal,
        mtime, name);
    }
    else{
        printf("%s\n", name);
    }
    free(name);
    return;
}


