#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>


/* not complete */ 
int lstat(const char *path, struct stat *buf);

void myfindDir(const char *path, const char *name )
{
   DIR *dir;
   struct dirent *ent;
   char relpath[PATH_MAX+1];

   if ( (dir = opendir(path)) == NULL) {
      perror(path);
      exit(EXIT_FAILURE);
   }
   while ((ent=readdir(dir))) {
      if()
      snprintf(relpath,PATH_MAX+1,"%s/%s",path,ent->d_name);
      lsfile(relpath);
   }
   closedir(dir);
}

int myfindfile(const char *path, const char *name)
{

}

int myfind(const char *path, const char *name)
{
   DIR *d;
   struct stat *sb;
   struct dirent *dir;

   if (-1 == lstat(path,sb) )
   {
      perror(path);
      exit(EXIT_FAILURE);
   }

   if((d = opendir(path)) == NULL)
   {
      perror(path);
      exit(EXIT_FAILURE);
   }


   while ((dir = readdir(d)) != NULL)
   {
      /* if its a directory */
      if ( S_ISREG(sb.st_mode) )
      {
         if(strcmp(dir->d_name, name ) == 0)
            printf("%s\n", dir->d_name);
      }
      else if ( S_ISDIR(sb.st_mode) )
      {

      }


      /* if its  a file */
   }
      printf("%s\n", dir->d_name);
   closedir(d);

   return 0;
}

int main()
{
   int num;
   num = myfind(".", "p4.c");
   return 0;
}