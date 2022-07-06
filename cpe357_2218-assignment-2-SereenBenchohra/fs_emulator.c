#include <stdio.h>
#include <stdlib.h>
#include "InodeHandle.h"
#include "user_commands.h"


int main(int argc, char *argv[])
{
   // make an  char Inode Array where index is inode number 
   //and element determines a type a file or dir
   int *maxInodes, *inode_fs_len;
   maxInodes = inode_fs_len  = NULL;
   maxInodes = malloc(sizeof(int));
   inode_fs_len  = malloc(sizeof(int));
   
   getInode_fs_len(inode_fs_len);

   char *inode_fs;
   // allocate Inode Array, check if malloc fails
   inode_fs = malloc(sizeof(char *) * (*inode_fs_len)); // need to get length 
   if(inode_fs == NULL)
   {
      perror(inode_fs);
      exit(EXIT_FAILURE);
   }

   // check arguments are valid (requirement 1 )
   verify_arguments(argc, argv, maxInodes);
   load_Inode(inode_fs);    //load number into inode struct (req 2)

   // successful in checking the first inode is a directory or not (req 3)
   Inode_Directory_Check(inode_fs);


   // gets user commands (req 4)
   user_command(&inode_fs, maxInodes, inode_fs_len );   

   free(inode_fs_len);
   free(inode_fs);
   free(maxInodes);
   return 0; 
}