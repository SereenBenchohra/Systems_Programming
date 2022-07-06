#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*
 * *
 *
Write a C function called bstr2int() that takes a valid C string (possibly null) consisting exclusively of the digits “0” and “1”, strips off any leading zeros, and then builds an int out of the
remaining values. Returns the resulting integer on success or −1 if the number cannot be represented
 (due to overflow). Recall that the size of an int on the current platform can be determined through
sizeof(int).
 * */
typedef unsigned char byte;

int bstr2int(const char *s)
{
   int cpts = 0;
   byte dec = 0;
   uchar x = 0;
   for (cpts = 0; cpts <= 7; cpts++) {
      x = 7 - cpts;
      dec += ((binstr[cpts] == '1')*(1 << x));
   }
   return dec;
}


