#include "part6.h"
#include <stdlib.h>

int sum(int num[], int length)
{
    int sum, i;
    sum = 0;
    for(i = 0; i < length; i++)
        sum = sum + num[i];
    
    return sum;
}