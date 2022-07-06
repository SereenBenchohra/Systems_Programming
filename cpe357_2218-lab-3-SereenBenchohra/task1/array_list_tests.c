#include <stdio.h>
#include <stdlib.h>
#include "array_list.h"
#include "checkit.h"

// test under normal conditions
void test_add_to_end1()
{
   ArrayList *list;
   list = array_list_new();
   array_list_add_to_end(list, "hello");
   checkit_string(list->stringList[list->numEntries - 1], "hello");
   checkit_int(list->numEntries, 1);

   array_list_add_to_end(list, "testing");
   checkit_string(list->stringList[list->numEntries - 1], "testing");
   checkit_int(list->numEntries, 2);
   
   array_list_add_to_end(list, "lab3");
   checkit_string(list->stringList[list->numEntries - 1], "lab3");
   checkit_int(list->numEntries, 3);

   array_list_add_to_end(list, "hello");
   checkit_string(list->stringList[list->numEntries - 1], "hello");
   checkit_int(list->numEntries, 4);

   array_list_add_to_end(list, "task1");
   checkit_string(list->stringList[list->numEntries - 1], "task1");
   checkit_int(list->numEntries, 5);

   array_list_add_to_end(list, "under");
   checkit_string(list->stringList[list->numEntries - 1], "under");
   checkit_int(list->numEntries, 6);

   array_list_add_to_end(list, "normal");
   checkit_string(list->stringList[list->numEntries - 1], "normal");
   checkit_int(list->numEntries, 7);


   array_list_add_to_end(list, "conditions");
   checkit_string(list->stringList[list->numEntries - 1], "conditions");
   checkit_int(list->numEntries, 8);

   array_list_add_to_end(list, "then");
   checkit_string(list->stringList[list->numEntries - 1], "then");
   checkit_int(list->numEntries, 9);

   array_list_add_to_end(list, "test");
   checkit_string(list->stringList[list->numEntries - 1], "test");
   checkit_int(list->numEntries, 10);

   array_list_add_to_end(list, "realloc");
   checkit_string(list->stringList[list->numEntries - 1], "realloc");
   checkit_int(list->numEntries, 11);
   checkit_int(list->capacity, 30); // check if it it has been reallocated

   free(list->stringList);
   free(list);


}


int main(void)
{
   test_add_to_end1();
   return 0; 
}