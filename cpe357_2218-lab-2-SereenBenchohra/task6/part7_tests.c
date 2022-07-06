#include <stdio.h>
#include "checkit.h"
#include "part7.h"
#include <string.h>
/*void str_lower(char old[], char lower[]); */ 

void test_to_lower_1()
{
   char old[] = "ABC";
   int length = strlen(old);
   char lower[length];
   str_lower(old, lower);
   checkit_string(lower, "abc");
}

void test_to_lower_2()
{
   char old[] = "abc";
   int length = strlen(old);
   char lower[length];   
   str_lower(old, lower);
   checkit_string(lower, "abc");
}

void test_to_lower_3()
{
   char old[] = "TbUStWwU";
   int length = strlen(old);
   char lower[length];
   str_lower(old, lower);
   checkit_string(lower, "tbustwwu");
}
// void str_lower_mutate(char *lower);
void test_to_lower_4()
{
   char lower[] = "ABCD";
   str_lower_mutate(lower);
   checkit_string(lower, "abcd");
}

// void str_lower_mutate(char *lower);
void test_to_lower_5()
{
   char lower[] = "AbBCtfecD";
   str_lower_mutate(lower);
   checkit_string(lower, "abbctfecd");
}

void test_to_lower_6()
{
   char lower[] = "TEWDIFGKLEOJLJS";
   str_lower_mutate(lower);
   checkit_string(lower, "tewdifgkleojljs");
}


void test_to_lower()
{
   test_to_lower_1();
   test_to_lower_2();
   test_to_lower_3();
   test_to_lower_4();
   test_to_lower_5();
   test_to_lower_6();
}

int main(void)
{
   test_to_lower();
   return 0;
}
