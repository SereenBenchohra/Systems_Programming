 #define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "checkit.h"
#include "array_list.h"
#include <string.h>


void test_split1()
{
   ArrayList *list;
   char *string;
   string = strdup("Hello testing split delim should give out multiple");
   list = split(string, " ");
   checkit_string(list->stringList[0], "Hello");
   checkit_string(list->stringList[1], "testing");
   checkit_string(list->stringList[2], "split");
   checkit_string(list->stringList[3], "delim");
   checkit_string(list->stringList[4], "should");
   checkit_string(list->stringList[5], "give");
   checkit_string(list->stringList[6], "out");
   checkit_string(list->stringList[7], "multiple");

   checkit_int(list->numEntries, 8);

   free(string);
   free(list->stringList);
   free(list);
}

void test_split2()
{
   ArrayList *list;
   char *string1;
   string1 = strdup("Hello#testing#split#delim should give#out multiple");
   list = split(string1, "#");
   checkit_string(list->stringList[0], "Hello");
   checkit_string(list->stringList[1], "testing");
   checkit_string(list->stringList[2], "split");
   checkit_string(list->stringList[3], "delim should give");
 
   checkit_string(list->stringList[4], "out multiple");
 

   checkit_int(list->numEntries, 5);

   free(string1);
   free(list->stringList);
   free(list);
}


int main(void)
{
   test_split1();
   test_split2();
   return 0;
}