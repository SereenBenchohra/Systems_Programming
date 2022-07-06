#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array_list.h"

/* Write a function named split that takes a string to split
and a character delimiter (i.e., the character used to determine 
where to split the string). Your function must split the string 
into multiple substrings as separated by the provided delimiter
and return an array list (from Task 1) of these substrings
(e.g., "These#are#words" split with a '#' delimiter would 
result in an array list containing "These", "are", "words"). 
You should use the strsep function in your implementation 
(the man page includes an example of its use). */

ArrayList *split(char *string, char *delim)
{
   char *substring, *local;
   ArrayList *list;
   local = string; // have local copy to mutate and not affect original string
   list = array_list_new();

   while((substring = strsep(&local, delim)) != NULL)
      array_list_add_to_end(list, substring);

   return list;
}