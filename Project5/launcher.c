#include <stdio.h>
#include "launcher.h"
#include <stdlib.h>
#include <string.h>

void inValidInput()
{
   fprintf(stderr, "Usage: pipeline path -p processes\n");
   fprintf(stderr, "Where: path is some \"random child\" and "
                   "processes is 2 to 10, inclusive\n");
   exit(EXIT_FAILURE);
}

void checkIfP(int argc, char *argv[], procData* data) /* check valid argument* for number  of processes */
{
   int i;
   data->pFlag = 0;
   for(i = 0; i < argc; i++)
   {
      if (strcmp(argv[i], "-p") == 0)
      {
         data->numProc = atoi(argv[i + 1]);
         data->pFlag = 1;
      }
   }
   if((data->numProc < 2 || data->numProc > 10) || data->pFlag == 0)
      inValidInput();

}

void checkNuMArg(int argc)
{
   if(argc !=4)
      inValidInput();
}

void checkForChild(int argc, char *argv[], procData *data)
{
   if (strcmp(argv[1], "-p") == 0)
      data->procIndex = 3;
   else
      data->procIndex = 1;
}

void parseFile(int argc, char *argv[], procData *data)
{
   checkNuMArg(argc);
   checkIfP(argc, argv, data);
   checkForChild(argc, argv, data);
}

int main(int argc, char *argv[])
{
   procData *data;
   parseFile(argc, argv, data);
   printf("Process number : %d  Child : %d Process Flag %d\n", data->numProc,
   data->procIndex, data->pFlag);
   pipeline(data);

   return 0;
 }

