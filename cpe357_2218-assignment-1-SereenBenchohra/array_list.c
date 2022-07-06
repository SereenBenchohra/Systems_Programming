#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array_list.h"

// implement an array list holding strings as elements. 

/*
This structure will need to track :
   -a resizable array
   - its length (its capacity )
   - and the number of values currently within the array
   - initial size of resizable array up to you
   */

ArrayList *array_list_new() //initialize array to 20 
{
   ArrayList *arrayList; 
   arrayList = malloc(sizeof(ArrayList));
   arrayList->numEntries = 0; // initializes to zero entries
   arrayList->capacity = 20; // have a capacity default of 20 
   arrayList->stringList = malloc(sizeof(char*) * arrayList->capacity);
   return arrayList;
}

/*
 * This function must take an array list and a string 
 * to add to the end of that list. If there is insufficient 
 * space to hold the string, the underlying array must be 
 * resized (you may use realloc); be sure to properly 
 * track the actual size of this array. The amount by which 
 * the underlying array is increased is up to you, but 
 * consider the cost of allocation vs. the cost of unused 
 * space.
 */

void array_list_add_to_end(ArrayList *list, char *string)
{

   if(list->numEntries == list->capacity) // if entries are approaching capacity
   {
         // resize the array by multiplying itself(does this risk losing the list values since reallocating to itself)
         list->stringList = realloc(list->stringList, sizeof(char*) * (list->capacity + 100)); 
         list->capacity = list->capacity + 100;   // change the capacity accordingly with newly resized array (too big?)
   }
   
   list->stringList[list->numEntries] = string; // add string to the end of the array (use us NumEntries  to index to end )
   list->numEntries++; // increments the number of entries once the string is added 
}

// change to return type to void and pass in a list that way there is no overwrite
void split(char *string, char *delim, ArrayList *list)
{
   char *substring, *local;
   local = string; // have local copy to mutate and not affect original string

   while((substring = strsep(&local, delim)) != NULL)
      array_list_add_to_end(list, substring);

}

// char *drop_quotes(char* s1) 
// {
//    size_t len;
//    //len = strlen(string);
//    // char s1[len];
//    //char *s1;
//    // len = strlen(s1);

//    //strcpy(s1, string);
   
//    if (s1[0] == '"' )
//       memmove (s1, s1+1, len);
//    len = strlen(s1);
//    if(s1[len - 1] == '\"') 
//       s1[len - 1] = '\0';

//    return s1;
// }

char *drop_quotes(char* string) 
{
   size_t len;
   len = strlen(string);
   char s1[len];
   // char *s1;
   strcpy(s1, string);
   
   if (s1[0] == '"' )
      memmove (s1, s1+1, len);
   len = strlen(s1);
   if(s1[len - 1] == '"') 
      s1[len - 1] = '\0';

   return (char *)s1;
}

void free_ArrayList(ArrayList *list)
{
   free(list->stringList);
   free(list);
}