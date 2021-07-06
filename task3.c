#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
/*
    While running this task3 programme you have to pass how many number 
    of threads you want to create here if you donot specify any number
    then the programe will throw "Segmentation fault: 11" like this.

    Example:-
     To Compile = gcc task3.c -o xyz -pthread
     To Run = ./xyz 7
              ./xyz 6
              ./xyz 5 (accordingly)

*/
int i, threadCount, n = 0, num = 0, count = 0;
int *data;
pthread_mutex_t mutex;
FILE *file, *file2;
char *filename[3] = {
    "Data/PrimeData1.txt",
    "Data/PrimeData2.txt",
    "Data/PrimeData3.txt",
};

void preProcess()
{
    for (i = 0; i < 3; i++)
    {
        file = fopen(filename[i], "r");
        int a;
        while (fscanf(file, "%d", &a) != EOF)
            n++;
    }
    data = malloc(n * sizeof(int));
}
void readData()
{
    preProcess();
    for (int i = 0; i < 3; i++)
    {
        file = fopen(filename[i], "r");
        int a;
        while (fscanf(file, "%d", &a) != EOF)
        {
            data[num] = a;
            num++;
        }
    }
}

struct PrimeVariables
{
    int start;
    int end;
};

void *checkPrime(void *primeVar)
{
    file = fopen("NewPrimeOnly.txt", "w");
    struct PrimeVariables *value = (struct PrimeVariables *)primeVar;
    int startLimit = value->start, endLimit = value->end;

    int isPrime, d = 0;
    for (int num = startLimit; num <= endLimit; num++)
    {
        d = data[num];
        isPrime = 1;
        if (d == 1 || d == 0)
            isPrime = 0;
        for (int j = 2; j <= d / 2; j++)
        {
            if (d % j == 0)
            {
                isPrime = 0;
                break;
            }
        }

        pthread_mutex_lock(&mutex);
        if (isPrime)
        {
            count++;
            fprintf(file, "%d\n", d);
        }

        pthread_mutex_unlock(&mutex);
    }
}

void slicing()
{
    int sliceList[threadCount],
        remainder = n % threadCount,
        startList[threadCount],
        endList[threadCount];
    struct PrimeVariables mainStruct[threadCount];

    for (i = 0; i < threadCount; i++)
    {
        sliceList[i] = n / threadCount;
        if (remainder > 0)
            sliceList[i] += 1;
    }

    for (i = 0; i < threadCount; i++)
    {
        if (i == 0)
            startList[i] = 0;
        else
            startList[i] = endList[i - 1] + 1;

        endList[i] = startList[i] + sliceList[i] - 1;

        // Assign to Structure
        mainStruct[i].start = startList[i];
        mainStruct[i].end = endList[i];
    }

    pthread_t thread[threadCount];
    for (i = 0; i < threadCount; i++)
        pthread_create(&thread[i], NULL, checkPrime, &mainStruct[i]);

    for (i = 0; i < threadCount; i++)
        pthread_join(thread[i], NULL);
}

void main(int argc, char **argv)
{
    threadCount = atoi(argv[1]);

    pthread_mutex_init(&mutex, NULL);
    readData();
    slicing();
    pthread_mutex_destroy(&mutex);
    file2 = fopen("NewPrimeOnly.txt", "a");
    fprintf(file2, "The amount of Prime numbers is = %d\n", count);

    free(data);
    fclose(file);
}