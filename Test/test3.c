#include <stdio.h>

// prime
void main()
{
    FILE *file = fopen("primeData1.txt", "r");
    int a;
    int isPrime;
    int count = 0;
    while (fscanf(file, "%d", &a) != EOF)
    {
        isPrime = 1;
        if (a == 1 || a == 0)
            isPrime = 0;

        for (int i = 2; i <= a / 2; i++)
        {
            if (a % i == 0)
            {
                isPrime = 0;
                break;
            }
        }
        if (isPrime)
        {
            count++;
            printf("%d = %d\n", count, a);
        }
    }
    fclose(file);
}