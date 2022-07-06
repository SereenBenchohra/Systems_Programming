#include <stdio.h>
#include <stdlib.h>
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
   if((list->numEntries + 10) >= list->capacity) // if entries are approaching capacity (make it equals the capacity)
   {
         // resize the array by multiplying itself(does this risk losing the list values since reallocating to itself)
         list->stringList = realloc(list->stringList, sizeof(char*) * (list->capacity + 10)); 
         list->capacity = list->capacity + 10;   // change the capacity accordingly with newly resized array (too big?) ( capacity + 10) (fixed)
   }
   
   list->stringList[list->numEntries] = string; // add string to the end of the array (use us NumEntries  to index to end )
   list->numEntries++; // increments the number of entries once the string is added 
}


