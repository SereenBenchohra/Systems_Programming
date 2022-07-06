#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include "functions.h"

void translate( char set1[], char set2[])
{
    
    unsigned int c, i, set1_size; 

    set1_size = strlen(set1);

    while ((c = getchar()) != EOF)
    {
        /* loop set1  */
        for(i = 0; i < set1_size; i++)
        {                   
            
            if(c == set1[i])
            {
                c = set2[i];
                break;
            }
        }
        putchar(c);
    }

}

/* delete all characters from set1 in input */
void my_delete( char set1[])
{
    unsigned int c, set1_size, i, flag;
    set1_size = strlen(set1);

    while ((c = getchar()) != EOF)
    {
        flag = 0;
        for(i = 0; i < set1_size; i++)   
        {   /* if c is not in the set, remove it with '\0' */
            if(c == set1[i])
            {
                flag++;
                break;
            }
            
        }               
        if (flag == 0)
            putchar(c);
        
    }
}

/* delete all complement characters from set1 in input */
/* inverse of delete function */
void delete_complement( char set1[])
{
    unsigned int c, set1_size, i;
    set1_size = strlen(set1);

    while ((c = getchar()) != EOF)
    {
        for(i = 0; i < set1_size; i++)   
            /* if c is not in the set, remove it with '\0' */
            if(c == set1[i])
                putchar(c);
                       
    }
}
