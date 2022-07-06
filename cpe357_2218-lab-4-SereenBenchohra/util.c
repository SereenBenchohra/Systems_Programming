#include <stdio.h>
#include "util.h"
#include "mem.h"

void exit(int);

void *checked_malloc(size_t size)
{
   void *ptr = lab_malloc(size);
   if (ptr == NULL)
   {
      fprintf(stderr, "memory allocation error ... exiting");
      exit(-1);
   }

   return ptr;
}
