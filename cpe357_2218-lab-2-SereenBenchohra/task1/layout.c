#include <stdio.h>

void function_one(int input)
{
   int function_one_local = input;
}

int function_two(int input)
{
   int function_two_local;

   function_two_local = input;
   return function_two_local;
}

int main(void)
{
   int first = 111;
   int second = 222;
   int *p = &first;

   function_one(357);
   function_two(0);

   return 0;
}
