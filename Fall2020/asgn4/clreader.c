#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "mytar.h"
#include "clreader.h"

/* put pointers in to a structure */


/* OPTIONAL PATH!!!!!!! WE FORGOT TO CODE FOR THIS! */
void readCommandLine(int argc, char *argv[], Settings *settings){

    int i, j, f;
    f = 0;
    
    i = strlen(argv[1]) - 1;

    while(i > -1){
        if(argv[1][i] == 'c'){
            if(settings->c == 1){
                fprintf(stderr,
                "usage: mytar [ctxvS]f tarfile [ path [ ... ] ]");
                exit(EXIT_FAILURE);
            }
            settings->c = 1;
            i--;
            continue;
        }
        if(argv[1][i] == 't'){
            if(settings->t == 1){
                fprintf(stderr,
                "usage: mytar [ctxvS]f tarfile [ path [ ... ] ]");
                exit(EXIT_FAILURE);
            }
            settings->t = 1;
            i--;
            continue;
        }
        if(argv[1][i] == 'x'){
            if(settings->x == 1){
                fprintf(stderr,
                "usage: mytar [ctxvS]f tarfile [ path [ ... ] ]");
                exit(EXIT_FAILURE);
            }
            settings->x = 1;
            i--;
            continue;
        }
        if(argv[1][i] == 'v'){
            if(settings->v == 1){
                fprintf(stderr,
                "usage: mytar [ctxvS]f tarfile [ path [ ... ] ]");
                exit(EXIT_FAILURE);
            }
            settings->v = 1;
            i--;
            continue;
        }
        if(argv[1][i] == 'S'){
            if(settings->S == 1){
                fprintf(stderr,
                "usage: mytar [ctxvS]f tarfile [ path [ ... ] ]");
                exit(EXIT_FAILURE);
            }
            settings->S = 1;
            i--;
            continue;
        }
        if(argv[1][i] == 'f'){
            if(f == 1){
                fprintf(stderr,
                "usage: mytar [ctxvS]f tarfile [ path [ ... ] ]");
                exit(EXIT_FAILURE);
            }
            f = 1;
            i--;
            continue;
        }
        fprintf(stderr,
                "usage: mytar [ctxvS]f tarfile [ path [ ... ] ]");
        exit(EXIT_FAILURE);
    } /* end of while loop */

    if((settings->c + settings->t + settings->x) != 1){
        fprintf(stderr,
                "usage: mytar [ctxvS]f tarfile [ path [ ... ] ]");
        exit(EXIT_FAILURE);
    }
    if(f != 1){
        fprintf(stderr,
                "usage: mytar [ctxvS]f tarfile [ path [ ... ] ]");
        exit(EXIT_FAILURE);
    }

    i = argc - 2;

    for(j = 0; j < i; j++){
        settings->paths[j] = argv[j + 2];    
        
        /* check that its a valid path for testing   
        if(stat(settings->paths[j], &path) == -1){
            fprintf(stderr, "clreader: Failed to open path: %s",
                     settings->paths[j]);
            exit(EXIT_FAILURE);

        } */
           

    }    


    return;
}







