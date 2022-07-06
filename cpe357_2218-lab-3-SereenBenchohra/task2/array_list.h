#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

typedef struct
{
   int capacity;
   int numEntries;
   char **stringList;

}ArrayList;

ArrayList *array_list_new(void);
void array_list_add_to_end(ArrayList *list, char *string);
ArrayList *split(char *string, char *delim);

#endif