/*
 * Provided source - DO NOT MODIFY !!!
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "memmon.h" 
#include "linkedList.h"

#define PGM_NAME "linkedList"

static int getValue()
{
   int value;

   while (1)
   {
      printf("Value: ");

      if (1 != scanf("%d", &value))
      {
         printf("The value must be an integer, please try again\n");
         getchar();
      }
      else
         break;
   }

   return value;
}

static int getIndex()
{
   int value;

   while (1)
   {
      printf("Index: ");

      if (1 != scanf("%d", &value))
      {
         printf("The index must be an integer, please try again\n");
         getchar();
      }
      else
         break;
   }

   return value;
}

static char doCommand(char command, ListNode **list)
{
   switch (command)
   {
      case 'h': /* h-ead add */
         *list = addHead(*list, getValue());
      break;

      case 't': /* t-ail add */
         *list = addTail(*list, getValue());
      break;

      case 'd': /* d-elete node at index */
         *list = deleteNode(*list, getIndex());
      break;
      
      case 'p': /* p-rint list */
         printList(*list);
      break;

      case 'q':
      break;

      default:
         printf("Unknown command '%c', please try again\n", command);
      break;
   }

   return command;
}

static char getCommand()
{
   char c;

   printf("Enter command (h|t|d|p|q): ");

   if (1 != scanf(" %c", &c))
   {
      fprintf(stderr, "Expected scanf failure in %s at line %d\n", __FILE__,
         __LINE__);
      exit(EXIT_FAILURE);
   }

   return c;
}

static int checkArgs(int argc, char *argv[])
{
   if (argc == 1)
      return 0 /* Run memmon with memory available */;

   if (argc > 2 || 0 != strcmp("-nomem", argv[1]))
   {
      fprintf(stderr, "Usage: %s [-nomem]\n", PGM_NAME);
      exit(EXIT_FAILURE);
   }

   return 1; /* Run memmon as though there is no memory available */
}

int main(int argc, char *argv[])
{
   char command;
   ListNode *list = NULL;

   /* Sets whether or not memmon thinks there is available memory */
   memSetOutOfMemory(checkArgs(argc, argv));

   do {
      command = doCommand(getCommand(), &list);

      /* Report the memory usage to see if it matches expectations */
      printf("Number of memory allocations: %d\n", memAllocs());
      printf("Number of memory frees      : %d\n", memFrees());
      printf("Peak memory allocation      : %u\n", memPeak());
      printf("Current memory allocation   : %u\n\n", memCurrent());
   } while (command != 'q');

   return EXIT_SUCCESS;
}
