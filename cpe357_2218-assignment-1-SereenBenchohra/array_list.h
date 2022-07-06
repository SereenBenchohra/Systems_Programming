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
void split(char *string, char *delim, ArrayList *list);
float data_conv_sum(char *string);
void free_ArrayList(ArrayList *list);
// char *drop_quotes(char *string);
char *drop_quotes(char *s1);

#endif