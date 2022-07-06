#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void nullInput(int argc)
{
   fprintf(stderr, "Usage: dataTyper argument [argument ...]\n");
   exit(EXIT_FAILURE);
}

void isDouble(int i, double doub)
{
   printf("   Argument %d is a double, its value is %f\n", i, doub);
}

void isInt(int i, int Int)
{
   printf("   Argument %d is an int, its value is %d\n", i, Int);
}

void isChar(int i, char Char)
{
   printf("   Argument %d is a char, its value is %c\n", i, Char);
}

void isString(int i, char *argv)
{
   printf("   Argument %d is a string, its value is %s\n", i, argv);
}

void whatType(int i, char *argv)
{
   int Int;
   double doub;

   if( (sscanf(argv, "%lf", &doub) == 1) && strchr(argv, '.'))
      isDouble(i, doub);
   else if ((sscanf(argv, "%d", &Int) == 1))
      isInt(i, Int);
   else if (strlen(argv) == 1)
      isChar(i, argv[0]);
   else
      isString(i, argv);

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

