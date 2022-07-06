#include "array_list.h"
#include <stdlib.h>
#include <stdio.h>

/* Write a function that takes a string expected to
 hold two floating point values separated (only) by a : 
 character. 
Your function should split the string into individual 
tokens, verify that there are only two values, convert those 
two values into floats (use strtof), and return the sum 
of the floats.

What should happen if the split (not enough values) 
or string conversion fails? You decide 
and then explain your choice during the demonstration 
(though exiting is not a reasonable 
option because it then takes control away from 
anybody calling your function). */

//probably have a defauly value 

float data_conv_sum(char *string)
{
   float sum, num1, num2;
   char *end, *local, *num2end;
   local = string;
   num1 = strtof(local, &end);
   if(end == local) // if it failed to parse the first num
   {
      printf("failure to parse first number, first number defaulting to 10\n");
      printf("second defaulting to 20\n");
      num1 = 10.0;
      num2 = 20.0;
      sum = num2 + num1;
      return sum;
   }
   //num2end = NULL;
   num2 = strtof(end, &num2end);

   // have condition if fail to tokenize deal 
   // set a default value and print message 
   if(end == num2end)
   {
      printf("failure to parse second number, second number defaulting to 20\n");
      num2 = 20.0;
      return num1 + num2;
   }
   return num1 + num2;
}