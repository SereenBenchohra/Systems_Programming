#include <stdio.h>
#include <float.h>
#include <limits.h>

int main()
{

   /* CHARS*/

   printf("%13s%21d (N/A)\n", "CHAR_BIT:", CHAR_BIT);

   printf("%13s%21d (%d byte)\n", "CHAR_MIN:", CHAR_MIN, (int)(sizeof(char)));

   printf("%13s%21d (%d byte)\n", "CHAR_MAX:", CHAR_MAX, (int)(sizeof(char)));

   printf("%13s%21d (%d byte)\n", "SCHAR_MIN:", SCHAR_MIN, (int)(sizeof(char)));

   printf("%13s%21d (%d byte)\n", "SCHAR_MAX:", SCHAR_MAX, (int)(sizeof(char)));

   printf("%13s%21u (%d byte)\n", "UCHAR_MAX:", UCHAR_MAX, (int)(sizeof(char)));

   printf("\n");

   /*SHORT*/
   printf("%13s%21d (%d bytes)\n", "SHRT_MIN:", SHRT_MIN, (int)(sizeof(short)));
   
   printf("%13s%21d (%d bytes)\n", "SHRT_MAX:", SHRT_MAX, (int)(sizeof(short)));

   printf("%13s%21u (%d bytes)\n", "USHRT_MAX:", 
      USHRT_MAX, (int)(sizeof(short)));

   printf("\n");

   /*INT*/
   printf("%13s%21d (%d bytes)\n", "INT_MIN:", INT_MIN, (int)(sizeof(int)));

   printf("%13s%21d (%d bytes)\n", "INT_MAX:", INT_MAX, (int)(sizeof(int)));
   
   printf("%13s%21u (%d bytes)\n", "UINT_MAX:", UINT_MAX, (int)(sizeof(int)));
   
   printf("\n");

   /*LONG*/

   printf("%13s%21ld (%d bytes)\n", "LONG_MIN:", LONG_MIN, (int)(sizeof(long)));

   printf("%13s%21ld (%d bytes)\n", "LONG_MAX:", LONG_MAX, (int)(sizeof(long)));
   
   printf("%13s%21lu (%d bytes)\n", 
      "ULONG_MAX:", ULONG_MAX, (int)(sizeof(long)));

   printf("\n");

   /*FLT*/

   printf("%13s%21g (N/A)\n", "FLT_EPSILON:", FLT_EPSILON);

   printf("%13s%21g (%d bytes)\n", "FLT_MIN:", FLT_MIN, (int)(sizeof(float)));
   
   printf("%13s%21g (%d bytes)\n", "FLT_MAX:", FLT_MAX, (int)(sizeof(float)));

   printf("\n");

   /*DBL*/

   printf("%13s%21g (N/A)\n", "DBL_EPSILON:", DBL_EPSILON);

   printf("%13s%21g (%d bytes)\n", "DBL_MIN:", DBL_MIN, (int)(sizeof(double)));
   
   printf("%13s%21g (%d bytes)\n", "DBL_MAX:", DBL_MAX, (int)(sizeof(double)));

   printf("\n");

   return 0;
}
