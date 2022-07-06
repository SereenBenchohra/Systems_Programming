#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashTable.h"
#include "qsort.h"
#include "ui.h"
#include "inreader.h"

#define DEFAULT_SIZE 500

int main(int argc, char *argv[]){

    char *word;
    FILE *file;
    int *nflag, *validFile, numNFlag;
    HashTable *table;
    Node **sortableArray;    
    int getNum, i;
    
    numNFlag = 0;
    validFile = (int *)calloc(1, sizeof(int));

    
    nflag = (int *)calloc(1, sizeof(int));


    getNum = parseNum(argc, argv, nflag);

    parseNum(argc, argv, nflag);
     
    table = createHashTable(DEFAULT_SIZE);

/*check to see if there is any files , if not read from stdin */    
    if((argc - *nflag) == 1 ){

       file = stdin;
       while((word = read_word(file)) != NULL)
         addData(word, table);

    }
    else{ /*if they exit, go through the command line  to get files */
    
      for(i = 1; i < argc; i++)
      {
         
         if(argv[i][0] =='-' &&  argv[i][1] != 'n') { /*check to bad flags */
            fprintf(stderr, "usage [-n]\n");
            exit(EXIT_FAILURE);
         }
         
         /* check to see if there was more than one -n flag */
         if(argv[i][0] =='-' &&  argv[i][1] == 'n'){
            numNFlag++;
            if(numNFlag > 1){
               fprintf(stderr, "usage only one flag\n");
               exit(EXIT_FAILURE);
            }
         }
         
         /*if not an n flag attemp to open file */
         if(strcmp(argv[i],"-n") != 0  &&  strcmp(argv[i -1], "-n") != 0 ) {
        
            file = fileOpen(argv[i], validFile);

            if(*validFile){

               while((word = read_word(file)) != NULL)
                  addData(word, table);
      
               fclose(file);
               *validFile = 0;

           }
         }

      }

    }

    sortableArray = linearArray(table);
    
    qsort(sortableArray, table->numEntries, sizeof(Node *), comparator);
    
    
    printMostFrequent(sortableArray, getNum, table->numEntries);
    
    
    free(sortableArray);
       

    return 0;
}
