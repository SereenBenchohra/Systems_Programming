#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user_commands.h"
#include "InodeHandle.h"

#define TRUE  1
#define FALSE 0
/*
 * CURRENT VALGRIND LEAKS: conditional jump when using mkdir and touch twice
*/

char **split(char *string)
{
    char **StringList;
    StringList = NULL;
    char *local, *tokens;
    local = tokens = NULL;
    int len = 0; 
    local = string;
    tokens = strtok (local, " ");

    while(tokens) /* split string and append tokens to 'StringList' */
    {
        StringList = realloc(StringList, sizeof (char*) * ++len);
        if(StringList == NULL)
        {
            perror(*StringList);
            exit(EXIT_FAILURE);
        }
        StringList[len - 1] = tokens;  
        tokens = strtok (NULL, " ");      
    }

    /* realloc one extra element for the last NULL */
    StringList = realloc (StringList, sizeof (char*) * (len+1));
    StringList[len] = 0;

/* print the result */

    return StringList;

}

char *get_File_path(char *inode_fs, int *cur_Dir)
{
   // concatenate string 
   int len;
   len = strlen(FS_FILE_PATH) + 2;
   char numStr[10];

   sprintf(numStr, "%d", *cur_Dir); // converts cur_Dir to Char

   char *inode_path;
   inode_path = NULL;
   inode_path = strdup(FS_FILE_PATH);
   inode_path = (char*)realloc(inode_path, len); // realloc to fit in new String
   
   strncat(inode_path, numStr, 1); // concatenate num into path to print 

   return inode_path;

}

void run_ls(char *inode_fs, int *cur_Dir)
{
   char *inode_path = get_File_path(inode_fs, cur_Dir);
   FILE *file = open_file(inode_path, "r");    // opens the file location

   char *line = NULL;
   size_t size = 0;
   char *name = NULL;
   int name_len = 0; 
   char **line_token = NULL;
   while(getline(&line, &size, file) > 0)
   {
      line_token = split(line);

      name = line_token[1];
      name_len = strlen(name);
      name[name_len - 1] = '\0'; // gets rid of null character
      
      printf("%s ", name);
      free(line_token); // frees the contents once done
   }

   printf("\n");

   free(line);
   //close the file
   fclose(file);
   free(inode_path);
}

void run_cd(char *inode_fs, int *cur_Dir, char **CommandTokens)
{

   if(CommandTokens[1] == NULL) // no argument or file after cd raise error
   {
      fprintf(stderr, "Usage error: cd [name]\n");
      return; // dont exit out program and continue
   }

   char *inode_path = get_File_path(inode_fs, cur_Dir); // creates path with cur Inode
   FILE *file = open_file(inode_path, "r");    // opens the file location

   char *line = NULL;
   char **line_token = NULL;

   size_t size = 0;
   char inode_num_char;
   int inode_num, exist; 

   char *name = NULL;
   int name_len = 0; 

   exist = FALSE;

   while(getline(&line, &size, file) > 0)
   {
      line_token = split(line);
      name = line_token[1];
      name_len = strlen(name);
      name[name_len - 1] = '\0'; // gets rid of null character for strcmp

      if(strcmp(line_token[1], CommandTokens[1] ) == 0) // if file exists , update cur directory other raise error that it does not exists, retrieve Inode 
      {
         exist = TRUE;
         inode_num_char = line[0]; // store inode from file into char
         inode_num = (int) inode_num_char - 48; // converts inode to int 
      }

      free(line_token); // frees line after finished
   }

   // checks if the file does not exist or not a directory
   if(exist == FALSE || inode_fs[inode_num] != 'd' )
      fprintf(stderr, "%s : Not a valid directory \n", CommandTokens[1]); // dont exit out program and continue
   else
      *cur_Dir = inode_num; // set current Directory to inode of directory

   free(line);
   
   //close the file
   fclose(file);
   free(inode_path);

}
// if there isnt an available inode, checks max Inodes bounds, if not exceeded resize array and make mkdir Inode to last in inode_fs
int resize_inode(char *inode_fs, int *mkdir_inode, int *maxInodes, int *inode_fs_len)
{
   int maxExceeded = FALSE;
   int inode_list_len = *inode_fs_len;
   if((*inode_fs_len + 1) >= *maxInodes) // checks if the potential new max has been exceeded
      maxExceeded = TRUE;
   else
   {
      inode_list_len++; // increment inode length
      inode_fs = realloc(inode_fs, sizeof(char ) * (inode_list_len));
      *mkdir_inode = inode_list_len - 1; // keeps mkdir inode as new last inode
      *inode_fs_len = inode_list_len;
   }

   return maxExceeded;
}
// works. checks if there is an available inode, returns TRUE and records the location of empty inode 
int available_Inode(char *inode_fs, int *inode_fs_len, int *mkdir_inode)
{
   int i, inodes_exists;
   inodes_exists = FALSE;

   for(i = 0; i < *inode_fs_len; i++)
   {
       if(inode_fs[i] == '0') // Works great . When removing an inode set inode value to '0'
      {
         *mkdir_inode = i; 
         inodes_exists = TRUE;
      }
   }

   return inodes_exists; 
}

// writes to the inode file its contents
void write_inode_file_dir(char *inode_path, int *inode, char **CommandTokens, char *inode_fs, int *cur_Dir)
{
    char *new_path = get_File_path(inode_fs, inode); // creates path with new inode
    FILE *file1 = open_file(new_path, "a");    // opens file for writing
    char inode_char = (*inode) + '0' ;

    // writes inodes
    fputc(inode_char, file1);    // write to current directory fs/.., write inode num and file name

    fputc(' ', file1);
    fputc('.', file1);

    fputc('\n', file1);
    // need to find away to get previous inode(use Cur_Dir)
    char cur_dir_char = (*cur_Dir) + '0' ;
    fputc(cur_dir_char, file1); // create an inode file with inode num and write . and ..
    fputc(' ', file1);
    fputc('.', file1);
    fputc('.', file1);
    fputc('\n', file1);

    free(new_path);
    fclose(file1);
}
void write_to_cur_Dir(char *inode_path, int *inode, char **CommandTokens, char *inode_fs)
{
    FILE *file = open_file(inode_path, "a");    // opens file for writing

    char inode_char = (*inode) + '0' ;
    fputc(inode_char, file);
    fputc(' ', file);
    fputs(CommandTokens[1], file);
    fputc('\n', file);

    inode_fs[*inode] = 'd'; // record in inode_fs
    fclose(file);
}
void create_Dir(char *inode_fs, int *cur_Dir, char **CommandTokens, int *maxInodes, int *inode_fs_len, char *inode_path)
{
      
   // check if there is an available inode by looping through inode_fs to reuse , (empty inodes are marked with a '0')
   int inodes_exists, *mkdir_inode;

   mkdir_inode = NULL;
   mkdir_inode = malloc(sizeof(int));
   *mkdir_inode = 0;

   inodes_exists =  available_Inode(inode_fs, inode_fs_len, mkdir_inode);

   int maxExceeded = FALSE; 
   // assume initially not empty  and maxExceeded is false
   if(inodes_exists == FALSE) 
      maxExceeded =  resize_inode(inode_fs, mkdir_inode, maxInodes, inode_fs_len); // resize inode_fs to fit new file , get inode num

   if(maxExceeded == TRUE)
      fprintf(stderr, "Max Inodes Exceeded system requirements\n");   
   else
   {
       write_to_cur_Dir(inode_path, mkdir_inode, CommandTokens, inode_fs);
       write_inode_file_dir(inode_path, mkdir_inode, CommandTokens, inode_fs, cur_Dir);
   }

   free(mkdir_inode);
}

void run_mkdir(char **inode_fs, int *cur_Dir, char **CommandTokens, int *maxInodes, int *inode_fs_len)
{

   if(CommandTokens[1] == NULL) // no argument or file after mkdir raise error
   {
      fprintf(stderr, "Usage error: mkdir [name]\n");
      return; // dont exit out program and continue
   }

   char *inode_path = get_File_path(*inode_fs, cur_Dir); // creates path with cur Inode
   FILE *file = open_file(inode_path, "r");    // opens the file location

   char *line = NULL;
   char **line_token = NULL;

   size_t size = 0;
   int exist = FALSE;

   char *name = NULL;
   int name_len = 0; 

   while(getline(&line, &size, file) > 0)
   {
      line_token = split(line);
      name = line_token[1]; // gets file name
      name_len = strlen(name);
      name[name_len - 1] = '\0'; // gets rid of null character for strcmp

      if(strcmp(line_token[1], CommandTokens[1] ) == 0) // if file exists ,  make exist true to later raise error
         exist = TRUE;

      free(line_token); 
   }

   //close the file
   fclose(file);
   // checks if the Exist Flag does not exist or not a directory
   if(exist == TRUE)
      fprintf(stderr, "mkdir: cannot create directory '%s': File exists  \n", CommandTokens[1]); // dont exit out program and continue
   else
      create_Dir(*inode_fs, cur_Dir, CommandTokens, maxInodes, inode_fs_len, inode_path );

   free(line);
   free(inode_path);

}

void remove_line_in_file(int line_num, char *inode_path)
{
    FILE  *src = open_file(inode_path, "r");
    FILE *tempFile = open_file("delete.tmp", "w"); // create a temp file to write final results to

    int count = 1; // start count at one
    char *line = NULL;
    size_t size = 0;

    while(getline(&line, &size, src) > 0)
    {
        if(count != line_num)
            fputs(line, tempFile);
        count++;
    }

    free(line);
    fclose(src);
    fclose(tempFile);

    remove(inode_path); // remove old file
    rename("delete.tmp", inode_path); // replace old file with new file


}


void remove_file(char *inode_fs, int *cur_Dir, int line_num, char *inode_path)
{

    remove_line_in_file(line_num, inode_path); // remove the file from line
    inode_fs[*cur_Dir] = '0';     // update inode_list with the inode num location with a '0'
    char *inode_path_dir = get_File_path(inode_fs, cur_Dir); // creates path with with inode directory
    remove(inode_path_dir); // removes INode directory

    free(inode_path_dir);

}



void run_rm(char **inode_fs, int *cur_Dir, char **CommandTokens, int *maxInodes, int *inode_fs_len) // removes the file directory
{
    if(CommandTokens[1] == NULL) // no argument or file after rm raise error
    {
        fprintf(stderr, "Usage error: rm [name]\n");
        return; // dont exit out program and continue
    }

    char *inode_path = get_File_path(*inode_fs, cur_Dir); // creates path with cur Inode
    FILE *file = open_file(inode_path, "r");    // opens the file location

    char *line = NULL;
    char **line_token = NULL;

    size_t size = 0;
    int exist;

    char *name = NULL;
    int line_num = 1; // saves line number to delete line
    int name_len;

    exist = FALSE;

    int *rm_inode = NULL;
    rm_inode = malloc(sizeof(int));

    while(getline(&line, &size, file) > 0)
    {
        line_token = split(line);
        name = line_token[1]; // gets file name
        name_len = strlen(name);
        name[name_len - 1] = '\0'; // gets rid of null character for strcmp

        if(strcmp(line_token[1], CommandTokens[1] ) == 0) // if file exists ,  make exist true to later raise error
        {
            exist = TRUE;
            is_integer(line_token[0], rm_inode);  // save inode location of remove file to remove it
            free(line_token);
            break;
        }

        line_num++; // records line number in file to delete it
        free(line_token);
    }

    fclose(file);

    if(exist == FALSE) // if file does not exist, raise error
        fprintf(stderr, "rm: cannot remove '%s': No such file or directory\n", CommandTokens[1]);
    else // otherwise start process of removing file
        remove_file(*inode_fs, rm_inode, line_num, inode_path);

    free(rm_inode);
    free(inode_path);
}

void write_to_inode_file_touch(int *inode, char **CommandTokens, char *inode_fs)
{
    char *new_path = get_File_path(inode_fs, inode); // creates path with new inode
    FILE *file1 = open_file(new_path, "a");    // opens inode file for writing
    fputs(CommandTokens[1], file1);     // writes to inode file just the file name
    fputc('\n', file1);

    free(new_path);
    fclose(file1);
}
void create_file(char *inode_fs, char **CommandTokens, int *maxInodes, int *inode_fs_len, char *inode_path)
{

    // check if there is an available inode by looping through inode_fs to reuse , (empty inodes are marked with a '0')
    int inodes_exists, *touch_inode;

    touch_inode = NULL;
    touch_inode = malloc(sizeof(int));
    *touch_inode = 0;

    inodes_exists =  available_Inode(inode_fs, inode_fs_len, touch_inode);

    int maxExceeded = FALSE;
    // assume initially not empty  and maxExceeded is false
    if(inodes_exists == FALSE)
        maxExceeded =  resize_inode(inode_fs, touch_inode, maxInodes, inode_fs_len); // resize inode_fs to fit new file , get inode num

    if(maxExceeded == TRUE)
        fprintf(stderr, "Max Inodes Exceeded system requirements\n");
    else
    {
        write_to_cur_Dir(inode_path, touch_inode, CommandTokens, inode_fs);
        write_to_inode_file_touch(touch_inode, CommandTokens, inode_fs);
    }

    free(touch_inode);
}

// runs exactly like mkdir with the only difference is writing an 'f' to the inode list, and different contents for the
// inode file
void run_touch(char **inode_fs, int *cur_Dir, char **CommandTokens, int *maxInodes, int *inode_fs_len)
{
    if(CommandTokens[1] == NULL) // no argument or file after mkdir raise error
    {
        fprintf(stderr, "Usage error: touch [name]\n");
        return; // dont exit out program and continue
    }

    char *inode_path = get_File_path(*inode_fs, cur_Dir); // creates path with cur Inode
    FILE *file = open_file(inode_path, "r");    // opens the file location

    char *line = NULL;
    char **line_token = NULL;

    size_t size = 0;
    int exist = FALSE;

    char *name = NULL;
    int name_len = 0;

    while(getline(&line, &size, file) > 0) // parses the inode file
    {
        line_token = split(line); // splits the inode file line into two , the inode num and file name
        name = line_token[1]; // gets file name
        name_len = strlen(name);
        name[name_len - 1] = '\0'; // gets rid of null character for strcmp

        if(strcmp(line_token[1], CommandTokens[1] ) == 0) // if file exists ,  make exist true to later raise error
            exist = TRUE;

        free(line_token);
    }

    //close the file
    fclose(file);
    // checks if the Exist Flag does not exist or not a directory
    if(exist == TRUE)
        fprintf(stderr, "touch: cannot create file '%s': File exists  \n", CommandTokens[1]); // dont exit out program and continue
    else
        create_file(*inode_fs, CommandTokens, maxInodes, inode_fs_len, inode_path );

    free(line);
    free(inode_path);
}

// catches the EOF condition and writes the Inodes list to the inode_list file updated
void run_exit(char *inode_fs, int *inode_fs_len)
{
    // open inode_list file for writing
    FILE *file = open_file(INODE_LIST_PATH, "w"); // open file for writing
    int i;
    char inode_char;
    for(i = 0; i < (*inode_fs_len); i++) // puts the inode and file type into inode_list file
    {
        inode_char = (i) + '0' ;
        fputc(inode_char, file);
        fputc(' ', file);
        fputc(inode_fs[i], file);
        fputc('\n', file);
    }

    fclose(file);     // close the file

}

void get_command(char *line, char **inode_fs, int *cur_Inode, int *maxInodes,  int *inode_fs_len)
{
   // make an array of strings to store words and commands
   char **CommandTokens = split(line);

   if(strcmp(CommandTokens[0], "ls") == 0)
      run_ls(*inode_fs, cur_Inode);
   else if(strcmp(CommandTokens[0], "cd") == 0) // check for cd 
      run_cd(*inode_fs, cur_Inode, CommandTokens);
   else if(strcmp(CommandTokens[0], "mkdir") == 0) // check for mkdir
      run_mkdir(inode_fs, cur_Inode, CommandTokens, maxInodes, inode_fs_len);
   else if(strcmp(CommandTokens[0], "rm") == 0) // check for rm
       run_rm(inode_fs, cur_Inode, CommandTokens, maxInodes, inode_fs_len);
   else if(strcmp(CommandTokens[0], "touch") == 0) // check for touch
       run_touch(inode_fs, cur_Inode, CommandTokens, maxInodes, inode_fs_len);

   free(CommandTokens);
}

/* Requirement 4 */
// use inode fs to store local copy and also keep track of the file system
void user_command(char **inode_fs, int *maxInodes, int *inode_fs_len) 
{
   char *line = NULL; // initialize to prevent leaks
   int len;
   size_t size = 0;

   int *cur_Inode = NULL;
   cur_Inode = malloc(sizeof(int));
   *cur_Inode = 0;   // starts at current Inode at 0

   //read from stdin and stores line 
   while(getline(&line, &size, stdin) > 0) // getline returns a the line with a \n
   {

      len = strlen(line);
      line[len - 1] = '\0'; // gets rid of the null for comparison purposes
      get_command(line, inode_fs, cur_Inode, maxInodes, inode_fs_len);
      if(strcmp(line, "exit") == 0) // compare for exit string if so then break
          break;
   }
   run_exit(*inode_fs, inode_fs_len);
   
   free(cur_Inode);
   free(line);   
}

