#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK 80
#define BUFFSIZE 25


char *read_long_line(FILE *file)
{
    char *line;
    int size, current_length, c;
    
    current_length = 0;
    size = CHUNK;

    if(!(line = (char * )malloc(sizeof(char)*CHUNK)))
    {
            fprintf(stderr, "Fail to allocate memory\n");
            exit(EXIT_FAILURE);
    }
    while ((c = fgetc(file)) != EOF) 
    {
        
        if (c == '\n')
            break;
        
        /* if length is approaching designated size */
        if (current_length + BUFFSIZE > size)
        {
            size += CHUNK;
            line = (char *)realloc(line,  sizeof(char) * size);
        }
        line[current_length] = c;
        /* increase the length */ 
        current_length++;
        

    }


    /* terminates string at the end of the newline or EOF */
    line[current_length] = '\0';
    /*increment lenght to account for null ( necessary for realloc) */ 
    current_length++;
    /*realloc appropiate size of the string */ 
    line = (char *)realloc(line,  sizeof(char) * current_length);
    return line;
}
 


int main()
{
    char *prev, *cur;


    /*set prev to NULL initially */
    prev = NULL;

    /*unti an EOF is read, read the lines */
    while((cur = read_long_line(stdin))
    {
       /* if the lines are equal discard the current line, otherwise print it */
       if(strcmp(cur, prev) ==0)
          free(cur);
       else
         printf("%s\n", cur);

       /* set previous line to currently */
       prev = cur;


    }

    free(prev);



    return 0; 
}
