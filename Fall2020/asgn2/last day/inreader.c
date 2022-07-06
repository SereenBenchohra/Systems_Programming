#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *read_word(FILE *file){

    int current_length = 0;
    int max_length = 4; /* default length is 8 chars */
    char *word = NULL; 
    /* allocating 7 + /0 characters */
    char current_char;
   
    if(!feof(file))
      current_char = fgetc(file);
    else
       return NULL;

    /* skips all the spaces in the loop check back on style */
    while(!feof(file) && !isalpha(current_char))
       current_char = fgetc(file);
    
    
    while(!feof(file) && isalpha(current_char)){
     /* while we arent at EOF or end of word */
        current_char = tolower(current_char);
        
        /*if memory allocation was full */
        if(current_length + 3 >=  max_length || current_length == 0){ 
            max_length *= 2; /* double its size */
            word = (char *)realloc(word, sizeof(char) * max_length);
        }
        word[current_length] = current_char; /* fill allocated memory */
        current_length++;
        current_char = fgetc(file);
    }

    if(feof(file) && isalpha(current_char)){
       
      current_char = tolower(current_char);
      
      /*if memory allocation was full */
      if(current_length + 3 >=  max_length || current_length == 0){ 
          max_length *= 2; /* double its size */
          word = (char *)realloc(word, sizeof(char) * max_length);
      }
      word[current_length] = current_char; /* fill allocated memory */
      current_length++;
      
    }


    if(feof(file) && current_length == 0){ /* when at end of input */
         /* frees final input */
        return NULL;
    }
    
    word[current_length] = '\0'; /* add null char */
    current_length++;
    word = (char *)realloc(word, sizeof(char) * (strlen(word)+ 1));
    return word;
}



