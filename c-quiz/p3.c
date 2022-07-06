#include <stdio.h>

double mean(int integers[], int len)
{
    int i;
    double sum, average; 
    for ( i = 0; i < len; i++)
        sum += integers[i];
    
    average = sum / (double) len;

    return average;
}
