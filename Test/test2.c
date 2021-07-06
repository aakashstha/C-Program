#include <stdio.h>
#include <math.h>
#include <pthread.h>

void main()
{
    int j;
    double pi = 0;

    for (j = 0; j <= 10000; j++)
    {
        pi += pow(-1, j) / (2 * j + 1);
    }
    printf("%lf\n", pi * 4);
}