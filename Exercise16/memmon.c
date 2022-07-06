/*
 * Memory Monitor 
 *
 * Intended for use Kurt Mammen's CPE 357 Systems Programming course at
 * Cal Poly. If you use it anywhere please attribute authorship appropriately!
 *
 * !!! DO NOT MODIFY !!!
 *
 * See memmon.h for instructions on how to use Memory Monitor in your program.
 *
 * Author: Kurt Mammen (2016)
 * Change Log:
 *    01/15/2018: Fixed memory leak.
 *    10/23/2016: Fixed realloc so it updates peak when necessary.
 *    10/12/2016: Made realloc free its old allocation when new one is zero.
 *    04/19/2016: Removed allocs++ from realloc.
 *    04/14/2016: Added support for errno.
 *    04/14/2016: Broke out numbers for calloc, malloc, and realloc. 
 *    04/11/2016: Fixed bug in unLogAlloc.
 *    04/07/2016: Initial revision.
 */
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#ifndef NOMEMMON
   typedef struct memAlloc
   {
      void *ptr;
      size_t bytes;
      struct memAlloc *next;
   } MemAlloc;

   static size_t peak = 0;       /* Peak memory allocation during execution */
   static size_t current = 0;    /* Current total memory allocated */
   static int    allocs = 0;     /* Number of unique allocations */
   static int    callocs = 0;    /* Number of successful calls to calloc */
   static int    mallocs = 0;    /* Number of successful calls to malloc */
   static int    reallocs = 0;   /* Number of successful calls to realloc */
   static int    frees = 0;      /* Number of successful frees */
   static int outOfMemory = 0;   /* To simulate of out-of-memory condition */
   static MemAlloc *list = NULL; /* List of current allocations */

   static int memmonOutOfMemory()
   {
      /* Fake out of memory */ 
      if (outOfMemory)
         errno = ENOMEM;

      return outOfMemory;
   }

   static void* logAlloc(void *ptr, size_t bytes)
   {
      MemAlloc *temp;

      /* Real out of memory */
      if (ptr == NULL)
         return NULL;

      /* Otherwise, update the numbers... */
      current += bytes;
      
      if (current > peak)
         peak = current;

      /* Add it to the log... */
      temp = malloc(sizeof(MemAlloc));

      if (temp == NULL)
      {
         fprintf(stderr, "memmon error: %s at line %d\n", __FILE__, __LINE__);
         exit(EXIT_FAILURE);
      }
 
      temp->ptr = ptr;
      temp->bytes = bytes;
      temp->next = list;
      list = temp;

      return ptr;
   }
   
   static void unLogAlloc(void *ptr)
   {
      MemAlloc *cur, *prev;

      /* Find it in the log, remove it, and update the numbers */
      cur = prev = list;

      while (cur != NULL)
      {
         if (cur->ptr == ptr)
         { 
            current -= cur->bytes; 

            if (cur == prev)
               list = cur->next;
            else
               prev->next = cur->next;

            free(cur);
            return;
         }
         else
         {
            prev = cur;
            cur = cur->next;
         }
      }

      if (ptr != NULL)
         fprintf(stderr,
            "Pointer %p not found, probable memory corruption (%s: %d)\n",
            ptr, __FILE__, __LINE__);
   }

   void memFree(void *ptr)
   {
      free(ptr);
      
      if (ptr != NULL)
      {
         frees++;
         unLogAlloc(ptr);
      }
   }

   void* memCalloc(size_t count, size_t size, const char *fname, int line)
   {
      void *ptr;

      if (memmonOutOfMemory())
         return NULL;
      
      if (NULL == (ptr = logAlloc(calloc(count, size), count * size)))
         return NULL;
      
      callocs++;
      allocs++;
      return ptr;
   }

   void* memMalloc(size_t bytes, const char *fname, int line)
   {
      void *ptr;

      if (memmonOutOfMemory())
         return NULL;
      
      if (NULL == (ptr = logAlloc(malloc(bytes), bytes)))
         return NULL;
      
      mallocs++;
      allocs++;
      return ptr;
   }

   static void updateRealloc(void *ptr, size_t bytes)
   {
      int diff;
      MemAlloc *cur, *prev;

      /* Find it in the log, update it, and update the numbers */
      cur = prev = list;

      while (cur != NULL)
      {
         if (cur->ptr == ptr)
         {
            diff = bytes - cur->bytes;
            cur->bytes = bytes;
            current += diff; 
            peak = current > peak ? current : peak;
            return;
         }
         else
            cur = cur->next;
      }
      
      if (ptr != NULL)
         fprintf(stderr,
            "Pointer %p not found, probable memory corruption (%s: %d)\n",
            ptr, __FILE__, __LINE__);
   }

   void* memRealloc(void *ptr, size_t bytes, const char *fname, int line)
   {
      void *returnedPtr;
      
      if (memmonOutOfMemory())
         return NULL;
      
      if (NULL == (returnedPtr = realloc(ptr, bytes)))
      {
         /* realloc frees the memory when bytes is 0 */
         if (bytes == 0 && ptr != NULL)
         {
            frees++;
            unLogAlloc(ptr);
         }

         return NULL;
      }

      reallocs++;

      if (returnedPtr == ptr)
      {
         /* Old allocation was kept -  adjust its size */
         updateRealloc(ptr, bytes);
      }
      else
      {
         /* New allocation - remove old one from the log */
         unLogAlloc(ptr);
         
         /* Log new one. Special case when bytes is 0, 1 byte allocated */
         logAlloc(returnedPtr, (bytes == 0 ? 1 : bytes));
      }

      return returnedPtr; 
   }

   int memAllocs()
   {
      return allocs;
   }

   int memCallocs()
   {
      return callocs;
   }

   int memMallocs()
   {
      return mallocs;
   }

   int memReallocs()
   {
      return reallocs;
   }

   int memFrees()
   {
      return frees;
   }

   unsigned memPeak()
   {
      return peak;
   }

   unsigned memCurrent()
   {
      return current;
   }

   void memSetOutOfMemory(int flag)
   {
      outOfMemory = flag;
   }

#endif
