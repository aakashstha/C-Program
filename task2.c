#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

int i, n, threadCount, count = 0;
float *all, finalSum = 0;
struct PiVariables
{
    int start;
    int end;
};

// function to run on threads, should return void pointer and
// accept void pointer as parameter.
void *calculatePi(void *piVar)
{
    struct PiVariables *value = (struct PiVariables *)piVar;
    int startLimit = value->start, endLimit = value->end;

    double pi = 0;
    for (int num = startLimit; num <= endLimit; num++)
    {
        pi += pow(-1, num) / (2 * num + 1);
        if (num == endLimit)
        {
            all[count] = pi;
            count++;
        }
    }
    pthread_exit(0);
}

void slicing()
{
    int sliceList[threadCount],
        remainder = n % threadCount,
        startList[threadCount],
        endList[threadCount];
    struct PiVariables mainStruct[threadCount];
    pthread_t thread[threadCount];

    for (i = 0; i < threadCount; i++)
    {
        sliceList[i] = n / threadCount;
        if (remainder >= 0) // to go upto all remainder
        {
            sliceList[i] += 1;
            remainder--;
        }

        if (i == 0)
            startList[i] = 0;
        else
            startList[i] = endList[i - 1] + 1;
        endList[i] = startList[i] + sliceList[i] - 1;

        mainStruct[i].start = startList[i];
        mainStruct[i].end = endList[i];

        pthread_create(&thread[i], NULL, calculatePi, &mainStruct[i]);
    }
    for (i = 0; i < threadCount; i++)
        pthread_join(thread[i], NULL);
}

void main()
{
    printf("How many times you want to loop through this Leibniz formula to get precise value of Pi:\n");
    scanf("%d", &n);
    printf("How many threads you would like to use to solve this problem:\n");
    scanf("%d", &threadCount);
    all = malloc(threadCount * sizeof(double));

    slicing();
    for (i = 0; i < threadCount; i++)
        finalSum += all[i];

    printf("\nThe final value of Pi = %f\n", finalSum * 4);
    free(all);
}
