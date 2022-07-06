#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "mytar.h"
#include "clreader.h"
#include "createArchive.h"
#include "tableArchive.h"
#include "extractArchive.h"

int main(int argc, char *argv[]){
    
    Settings settings;
    
    settings.c = 0;
    settings.t = 0;
    settings.x = 0;
    settings.S = 0;
    settings.v = 0;

    if(argc < 3){
        fprintf(stderr, "usage: mytar [ctxvS]f tarfile [ path [ ... ] ]");
        exit(EXIT_FAILURE);
    }

 
    settings.paths = (char **)malloc(sizeof(char *) * (argc - 2)); 
    if(settings.paths == NULL){
        fprintf(stderr, "mytar: Failed to allocate memeory");
        exit(EXIT_FAILURE);
    }



    readCommandLine(argc, argv, &settings);
    
    executeCommand(argc, argv, &settings);


    return 0;

}

void executeCommand(int argc, char **argv, Settings *settings){
        
    if(settings->c == 1){
        createArchive(settings, (argc - 3));
    }
    else if(settings->t == 1){
        tableArchive(settings, (argc - 2));
        return;
    }
    else if(settings->x == 1){
        extractArchive(settings, (argc - 2));
        return;
    }
    else{
        fprintf(stderr,
             "mytar: How did you even get here?? Theoretically Usage");
        exit(EXIT_FAILURE);
    }

    return;
}


int isContained(char *name, char *match){
    int length, i;
    
    length = strlen(match);

    if(strlen(name) < length){
        //printf("messed up lengths: %s - %s\n", name, match);
        return 0;
    }    

    for(i = 0; i < length; i++){
        if(name[i] != match[i]){
            //printf("mismatch: %d: %c - %c\n", i, name[i], match[i]);
            return 0;
        }
    }
    return 1;
}










