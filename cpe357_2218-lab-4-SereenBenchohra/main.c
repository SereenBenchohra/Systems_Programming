#include <stdio.h>
#include "mem.h"
#include "util.h"

#define LARGER_SIZE 40
#define MEDIUM_SIZE 10
#define SMALL_SIZE 7

int main(void)
{
   void *p1, *p2, *p3, *p4, *p5, *p6, *p7;

   size_t initial_sizes = LARGER_SIZE * sizeof(int);
   size_t medium_size = MEDIUM_SIZE * sizeof(int);
   size_t small_size = SMALL_SIZE * sizeof(int);

   p1 = checked_malloc(initial_sizes);
   p2 = checked_malloc(initial_sizes);
   p3 = checked_malloc(initial_sizes);
   p4 = checked_malloc(initial_sizes);
   p5 = checked_malloc(initial_sizes);

   printf("1. %p -- %ld (%ld bytes)\n", p1, (long) p1, initial_sizes);
   printf("2. %p -- %ld (%ld bytes)\n", p2, (long) p2, initial_sizes);
   printf("3. %p -- %ld (%ld bytes)\n", p3, (long) p3, initial_sizes);
   printf("4. %p -- %ld (%ld bytes)\n", p4, (long) p4, initial_sizes);
   printf("5. %p -- %ld (%ld bytes)\n", p5, (long) p5, initial_sizes);

   printf("Freeing 4th -- %p\n", p4);
   lab_free(p4);

   p6 = checked_malloc(medium_size);
   printf("Allocated -- %p -- %ld (%ld bytes)\n", p6, (long) p6, medium_size);

   printf("Freeing 2nd -- %p\n", p2);
   lab_free(p2);
   p7 = checked_malloc(small_size);
   printf("Allocated -- %p -- %ld (%ld bytes)\n", p7, (long) p7, small_size);

   lab_free(p1);
   lab_free(p3);
   lab_free(p5);
   lab_free(p6);
   lab_free(p7);
   return 0;
}
