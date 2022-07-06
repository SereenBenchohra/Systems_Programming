#include <stdio.h>
#include <string.h>

int main()
{
   int A, B, result;
   char *cp;
   A = 2;
   B = -1;
   cp = "abcdefg";
   int grade[5] = { 4, 3, 2, 1, 0};

    result = (A !=A)?A:B;
   // grade[5] = { 4, 3, 2, 1, 0};

   printf("%d\n", 3 / 6);
   printf("%d\n", A + B);
   printf("%d\n", +A++ + ++B);
   printf("%d\n", grade[2]);
   printf("%c\n", *(cp+4));
   
   printf("&grade[4] %ld\n", &grade[4]);
   printf("&grade[2] %ld\n", &grade[2]);
   
   printf("%ld\n", &grade[4] - &grade[2]);
   printf("%d\n", (int)&grade[4] - (int)&grade[2]);
   printf("%d\n", result);
   printf("%zu\n", strlen(cp));

   printf("%d\n", sizeof(grade));
   printf("%d\n", strlen((char *) (&grade[0])));

   return 0;
}
