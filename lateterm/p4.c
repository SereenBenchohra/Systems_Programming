#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int same_file (const char src, const char dest) {
   struct stat *src_stat;
   struct stat *dst_stat;

   if (lstat(dst, dst_stat) == -1)
   {
      perror("same file");
      exit(EXIT_FAILURE);
   }

   if(lstat(src, src_stat) == -1)
   {
      perror("same file");
      exit(EXIT_FAILURE);
   }

   if((src_stat->st_ino == dst_stat->st_ino) &&
      (src_stat->st_dev == dst_stat->st_dev))
      return 1;
   return 0;
}

