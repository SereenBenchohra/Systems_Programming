#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

/*  The strrchr() function returns a pointer to the last  occurrence  of  the
  character c in the string s. */



/* Write robust code (even though the library version is fragile). That is, return NULL on failure, but do
not crash. Do not use any of the C library’s string functions. Think before you write anything. */

int mystrlen( const char *s )
{
    int length;
    
    for(length = 0; s[length] != '\0'; length++ );
    
    return length;
}
char *strrchr(const char *s, int c)
{
    const char *last;
    int length, i;
    last = NULL;
    length = mystrlen(s); /* includes the null terminator into length */

    for ( i = length; i >= 0 ; i--) /* goes backware to get the last occurance of the char */
        if (c == s[i])
        {
            last = &s[i];
            return (char*)last;
        }

    /* return NULL if char is not found */ 
    if(last == NULL)
        return ""; /* return empty string  go back to it later */ 
    
    

}

