#include <stdio.h>
#include "checkit.h"
#include "part6.h"
/* int sum(int num[], int length); */
void test_sum_1()
{
   int num[] = {3, 4 , 5};
   checkit_int(sum(num, 0), 0);
}

void test_sum_2()
{
   int num[] = {3, 4 , 5};
   checkit_int(sum(num, 3), 12);
}
void test_sum()
{
   test_sum_1();
   test_sum_2();
}

int main(void)
{
   test_sum();

   return 0;
}
