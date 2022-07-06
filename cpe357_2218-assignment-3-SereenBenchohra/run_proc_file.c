#include "dir_management.h"
#include "stat_file_handle.h"

/*
 * VALGRIND LEAKS : NONE
 *
 */

int main(int argc, char *argv[])
{
   DIR *dir = NULL;
   dir = check_arguments(argc, argv); // req 1 
   char *proc_path = NULL;
   proc_path = get_proc_path(argc, argv); 

   struct dirent **entryList = NULL; // make a list of entries to process 

   int len = getLength(dir); // might not need it

   entryList = process_entries(dir); // req 2

   // req 3, 4, and 5
   print_every_pid_info(len, entryList, proc_path);


   free(proc_path);
   closedir(dir);
   free(entryList);
   
   return 0; 
}

