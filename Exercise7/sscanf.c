#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void nullInput(int argc)
{
   fprintf(stderr, "Usage: dataTyper argument [argument ...]\n");
   exit(EXIT_FAILURE); 
}
void typeOfNum(int i,char *argv)
{ 
   char *decCheck = strchr(argv, '.');
   double Double;
   int Integer;
   sscanf(argv, "%d", &Integer); 
   sscanf(argv, "%lf" , &Double);
   if(decCheck == NULL)   
      printf("   Argument %d is an int, its value is %d\n", i, Integer);
   else
      printf("   Argument %d is a double, its value is %f\n", i, Double); 
}

void typeOfLet(int i, char *argv)
{
   char Char;
   sscanf(argv, "%s", argv);
   sscanf(argv, "%c", &Char);
   if(strlen(argv) == 1)
      printf("   Argument %d is a char, its value is %c\n", i, Char); 
   else
      printf("   Argument %d is a string, its value is %s\n", i, argv);
}
   
void whatType(int i, char *argv)
{  
   char first;
   if(argv[0] == '-')
      first = argv[1];
   else
      first = argv[0];
   if( first >= '0' &&  first <= '9' )
      typeOfNum(i, argv);
   else 
      typeOfLet(i, argv);

}

int main(int argc, char *argv[])
{

   int i;
   if((argc-1 ) == 0)
      nullInput(argc); 
   for(i =1;  i <argc; i++)
      whatType(i, argv[i]);
   return 0;
}

