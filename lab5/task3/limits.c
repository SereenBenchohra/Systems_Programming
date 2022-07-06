#include <unistd.h>
#include <limits.h>
#include <stdio.h>

int main()
{
   long child, open, page;

   child = sysconf(_SC_CHILD_MAX);
   open = sysconf(_SC_OPEN_MAX);
   page = sysconf(_SC_PAGE_SIZE);

   printf("SC_CHILD_MAX  : %ld \n", child);
   printf("SC_OPEN  : %ld \n", open);
   printf("SC_PAGE_SIZE  : %ld \n", page);

   return 0;
}