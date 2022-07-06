#include <stdio.h>
#include "part7.h"
#include <ctype.h>
#include <string.h>

// change teration over the string arguments is done with
//  pointers and dereferencing instead of indexing

void str_lower(char *old, char *lower)
{  
    int i;
    while(*old != '\0')   
        *lower++ =  tolower(*old++);
       
    *lower = '\0'; // null terminate string
}

void str_lower_mutate(char *lower)
{
    int length = strlen(lower);
    // char string[length];
    char *beg = lower;
    int i;
    while (*lower != '\0')
    {
        *lower = tolower(*lower);
        *lower++;
    } 
    
}