#include <stdio.h>
#include <stdlib.h>

#define FILENAME "test"
#define TAB 8

int main()
{
   int c, i,column, space;
    
   FILE *in;

   in = stdin;
   column = 0;
   
   /*Check to see if an input file exists */
   if(in == NULL) {   
      perror(FILENAME);
      exit(1);
   }
   while( (c = getchar()) != EOF) /*Gets the char for Stdin */
   {
    
    /* Calculates the spaces needed to reach the tab stop */
    space = (TAB - (column % TAB)); 
    
    /* Adds the appropiate amount of spaces */
    if( c == '\t') 
    { 
        for(i = 0; i < space; i++)  
          putchar(' ');

	column += space;
    }
    else 
    {
        putchar(c); 
        column++;
    }

    if(c == '\n' || c == '\r') /* Resets column */
        column = 0;
    
    /*Backs up the backspace and the letter itself */  
    if(c == '\b') 
      	column-= 2;
         
     
   } 

   return 0;

}
