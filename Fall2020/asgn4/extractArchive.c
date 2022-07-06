#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#include  <stdlib.h>
#include  <stdio.h>
#include  <string.h>
#include  <time.h>
#include <utime.h>

#include "mytar.h"
#include "nicoFuncts.h"
#include "extractArchive.h"

/* stuff global to the file I didnt really feel
 * like passing along as parameters */
static int badFile;
static FILE *archive;
static int progress;

void extractArchive(Settings *settings, int numPaths){
    int sum, expectedSum, j;
    char buff[BLOCK_SIZE], sumBuff[TYPEFLAG - CHKSUM], *end;
    unsigned char uchar;

    badFile = 0;
    progress = 0;
    
    if((archive = fopen(settings->paths[0], "r")) == NULL){
        fprintf(stderr, "extractArchive: failed to open");
            exit(EXIT_FAILURE);
    }

    while((progress = fread(buff, 1, BLOCK_SIZE, archive)) == BLOCK_SIZE){
        
        /* checking CHKSUM */
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
            extractEntry(buff, settings->v, settings->paths, numPaths);
        }
    }
    /* if something fishy is up with the tar file */
    if((progress % BLOCK_SIZE) != 0 && (progress % BLOCK_SIZE) != 1){
        printf("%d\n", progress);
        fprintf(stderr, "bad tar file: incomplete blocks (caller)");
        exit(EXIT_FAILURE);
    }
    if(badFile == 0){
        fprintf(stderr, "bad tar file: no valid headers");
    }  
    fclose(archive);
}


void extractEntry(char *header, int verbose, char **matches, int numPaths){
    FILE *file;
    char mode[UID-MODE + 1], size[MTIME-SIZE + 1], mtime[CHKSUM-MTIME + 1],
    sLinkBuff[MAGIC-LINKNAME + 1], *name, *end, *buff;
    int permissions, sizeVal, mtimeVal, i; 
    struct utimbuf ut;

    /* parese name: Prefix + Name */
        
    if((name = (char *)calloc((PREFIX_LENGTH + (MODE - NAME) + 2), 1)) == NULL){
        fprintf(stderr, "tableArchive-printEntree: failed to calloc");
        exit(EXIT_FAILURE);
    }
    if(strlen(header + PREFIX) != 0){
        strcpy(name, (header + PREFIX));
        strcpy((name + strlen(name)), "/");   
    }
    strncpy((name + strlen(name)), (header + NAME), (MODE - NAME));

    /* validating file -> does the user want it? y/n */

    for(i = 1; i < numPaths; i++){ 
        if(isContained(name, matches[i])){ /* y */
            break;
        }
    }
    if(i == numPaths && i != 1){ /* n */
        free(name);
        return;
    }

    badFile = 1;

    /* parent dir creation -> can prob be moved
       somewhere more efficient*/

    createParentPath(name); 

    /* print verbose here */

    if(verbose){
        printf("%s\n", name);
    }

    /* permissions (execute? y/n) */

    strncpy(mode, (header + MODE), (UID - MODE));
    permissions = strtol(mode, &end, 8); 
    if(*end){
        fprintf(stderr, "tableArchive-extractEntry: Failed to strtol (perm)");
        exit(EXIT_FAILURE);
    }
    permissions = (permissions & 0111?0111:0000); /*is the original executable*/
    
    /* branching out */

    if(header[TYPEFLAG] == '5'){
        mkdir(name, (0666 | permissions));
    }

    else if(header[TYPEFLAG] == '2'){

        sLinkBuff[MAGIC - LINKNAME] = '\0';
        strncpy(sLinkBuff, (header + LINKNAME), (MAGIC - LINKNAME));
        symlink(sLinkBuff, name);
        chmod(name, (0666 | permissions)); 
        return;
    }

    else if(header[TYPEFLAG] == '\0' || header[TYPEFLAG] == '0'){
        
        /* get the size of the file */
        
        strncpy(size, (header + SIZE), (MTIME - SIZE));
        size[12] = '\0';    

        sizeVal = strtol(size, &end, 8); 
        if(*end){
            fprintf(stderr,
                    "extractArchive-extractEntry: Failed to strtol (size)");
            exit(EXIT_FAILURE);
        }
        printf("%s\n", name); 
        if((file = fopen(name, "w")) == NULL){   
            perror("extractArchive-extractFile: Failed to open path: ");
            fprintf(stderr, "%s", name);
            exit(EXIT_FAILURE);
        }
        
        /* taking archive contents in to malloc then to destination */
        
        buff = (char *)malloc((sizeVal + (BLOCK_SIZE - 
                                        (sizeVal % BLOCK_SIZE))));
        if(buff == NULL){
            fprintf(stderr, "failed to malloc");
            exit(EXIT_FAILURE);
        }
        progress = fread(buff, 1,
                (sizeVal + (BLOCK_SIZE - (sizeVal % BLOCK_SIZE))), archive);
        
        /* check for weird tar file */
        if(progress % BLOCK_SIZE != 0){
            fprintf(stderr, "bad tar file: incomplete blocks (inner)");
            exit(EXIT_FAILURE);
        }
    
        fwrite(buff, 1, sizeVal, file);
        free(buff);

        chmod(name, (0666 | permissions)); 
    }
    else{  
        fprintf(stderr,
                "extractArchive.c-extractEntry: file type not supported");
        exit(EXIT_FAILURE);
    }
    
    /* restore the mtime */       
   
    strncpy(mtime, (header + MTIME), (CHKSUM - MTIME)); 
    mtime[12] = '\0';    

    mtimeVal = strtol(mtime, &end, 8); 
    if(*end){
        fprintf(stderr,
        "extractArchive-extractEntry: Failed to strtol (mtime)");
        exit(EXIT_FAILURE);
    }
    
    ut.actime = 0; /* doesnt really matter */
    ut.modtime = mtimeVal;
       
    if(utime(name, &ut) != 0){
        perror("extractArchive-extractFile: Failed to set mtime");
        fprintf(stderr, "path: %s\n", name);
        fprintf(stderr, "mtime: %d\n", (int) mtimeVal);
        exit(EXIT_FAILURE);
    }
    free(name);   
 
}


/* basically ensures a path to the target */
void createParentPath(char *name){
    int ptr, i;
     
    ptr = strlen(name);

    for(i = 0; i < ptr; i++){
        if(name[i] == '/'){
            name[i] = '\0';
            mkdir(name, 0777);
            name[i] = '/';
        }
    }

}


