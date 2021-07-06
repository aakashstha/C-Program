#include <stdio.h>
#include <stdlib.h>

int *x, *y;
int i, num = 0, n = 0;
char fname[20];
double a = 0, b = 0;
double sigmaX = 0, sigmaY = 0, sigmaXY = 0, sigmaX_Square = 0, sigmaY_Square = 0;
FILE *file;
char *filename[4] = {
    "Data/datasetLR1.txt",
    "Data/datasetLR2.txt",
    "Data/datasetLR3.txt",
    "Data/datasetLR4.txt",
};

// This is actually to know how many data are availabel in all dataset files.
void preProcess()
{
    for (i = 0; i < 4; i++)
    {
        file = fopen(filename[i], "r");
        int f, g;
        while (fscanf(file, "%d,%d", &f, &g) != EOF)
        {
            n++;
        }
    }
    x = malloc(n * sizeof(int));
    y = malloc(n * sizeof(int));
}
void readData()
{
    preProcess();
    for (i = 0; i < 4; i++)
    {
        file = fopen(filename[i], "r");
        if (file == NULL)
        {
            printf("There is no data inside file.");
        }
        else
        {
            int f, g;
            while (fscanf(file, "%d,%d", &f, &g) != EOF)
            {
                x[num] = f;
                y[num] = g;
                num++;
            }
        }
    }
}
void calculate()
{
    double numerator = 0;
    double denominator = 0;
    for (i = 0; i < n; i++)
    {
        sigmaX += *(x + i);
        sigmaY += *(y + i);
        sigmaXY += (*(x + i)) * (*(y + i));
        sigmaX_Square += (*(x + i)) * (*(x + i));
        sigmaY_Square += (*(y + i)) * (*(y + i));
    }

    numerator = (sigmaY * sigmaX_Square) - (sigmaX * sigmaXY);
    denominator = (n * sigmaX_Square) - (sigmaX * sigmaX);
    a = numerator / denominator;

    // we donot have to calculate denominator here because it is same as above.
    numerator = (n * sigmaXY) - (sigmaX * sigmaY);
    b = numerator / denominator;
}

void main()
{
    int newX = 0;
    double newY = 0;
    readData();
    calculate();

    printf("The equation of a straight line is y = %lfx + %lf\n", b, a);
    printf("Enter the new value of x to predicit the value of y:\n");
    scanf("%d", &newX);
    newY = (b * newX) + a;
    printf("Your new predicted value of y is = %lf\n", newY);

    free(x);
    free(y);
    fclose(file);
}