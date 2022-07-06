#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include "InodeHandle.h"


void integer_error(char *notNum)
{
   fprintf(stderr, "\"%s\" is not an integer\n", notNum);
   fprintf(stderr, "Usage error: [integer][file_system]");
   exit(EXIT_FAILURE);
}

/* is integer program checks for the string whether it is an integer or not
the program loops through each character to 
check if its a digit or not */

void is_integer(char *isNum, int *maxInodes)
{
   int num;

   char *end, *local;
   local = isNum;
   num = strtol(local, &end, 10);
   // if not raise error
   if(end == local)
      integer_error(isNum);
   
   *maxInodes = num;
}

void isFile(char *isFile)
{
   // if its  use S_ISDIR(m)  directory?
   DIR *dir = opendir(isFile);
   if (dir == NULL) 
   {
      perror(isFile);
      exit(EXIT_FAILURE);   
   }
   else
      closedir(dir);
}

void verify_arguments(int argc, char *argv[], int *maxInodes)
{
   
   if(argc != VALID_ARGUMENTS)
   {
      fprintf(stderr, "Improper number arguments \n");
      exit(EXIT_FAILURE);
   }

   isFile(argv[2]); // check second argument if valid directory 
   is_integer(argv[1], maxInodes); // check if valid integer if so, store in inode struct

}


FILE *open_file(const char *path, const char *mode)
{
   FILE *file;
   if((file = fopen(path, mode)) == NULL)
   {
        perror(path);
      exit(EXIT_FAILURE);
   } 
   return file;
}

void check_Inode_valid(char *inode_fs, int len)
{
   int i;
   for(i = 0; i < len; i++ )
   {
      if(inode_fs[i] != 'd' && inode_fs[i] != 'f')
      {
         fprintf(stderr, "Invalid Indicator should be \'f\' or \'d\'\n" );
         exit(EXIT_FAILURE);
      }
   }

}

void getInode_fs_len(int *inode_fs_len)
{
   // open the file for read mode (write later requirement)
   char *line = NULL;
   size_t size = 0;

   // open the file for read mode (write later requirement)
   FILE *file = open_file(INODE_LIST_PATH, "r");  // read from file 
   int i = 0;
   
   while(getline(&line, &size, file) > 0)
      i++;
   *inode_fs_len = i; // get inode len 
   // free  line when finished
   free(line);
   fclose(file); // close file after use 
}


/* loads inode_list file into an inode list and checks wheter the the elements of the inode list file has a valid inode
 * number and file */

void load_Inode(char *inode_fs)
{

   // open the file for read mode (write later requirement)
   FILE *file;
   char *line;
   size_t size = 0;

   file = open_file(INODE_LIST_PATH, "r");  // read from file 
   int i = 0;
   
   line = NULL;

   while(getline(&line, &size, file) > 0)
   {
      inode_fs[i] = line[2];
      i++;
   }

   check_Inode_valid(inode_fs, i);
   // to test loop through Inode Struct and print contents s
   free(line);
   fclose(file); // close file after use 
} 


/* checks if the first inode is a directory, raises error if it is not one */

void Inode_Directory_Check(char *inode_fs)
{
   if(inode_fs[0] != 'd')
   {
      fprintf(stderr, "First Inode is not a directory\n");
      exit(EXIT_FAILURE);
   }

}

