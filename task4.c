#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "lodepng.h"

unsigned char *ImageIn, *ImageOut;
unsigned int width, height, error;
// Here n is the total size of a image and s is the varibale used in slicing
// Thread Count by default is 1 and updated by user
int threadCount = 1, n = 0, s;
struct GaussianBlur
{
    int start;
    int end;
};

void RGB_SumDivide(int j, int d, int r1, int r2, int r3, int r4, int r5, int r6, int r7, int r8, int r9)
{
    int r = 0, g = 0, b = 0;
    if (d == 4)
    {
        r = ImageIn[r1] + ImageIn[r2] + ImageIn[r3] + ImageIn[r4];
        g = ImageIn[r1 + 1] + ImageIn[r2 + 1] + ImageIn[r3 + 1] + ImageIn[r4 + 1];
        b = ImageIn[r1 + 2] + ImageIn[r2 + 2] + ImageIn[r3 + 2] + ImageIn[r4 + 2];
    }
    else if (d == 6)
    {
        r = ImageIn[r1] + ImageIn[r2] + ImageIn[r3] + ImageIn[r4] + ImageIn[r5] + ImageIn[r6];
        g = ImageIn[r1 + 1] + ImageIn[r2 + 1] + ImageIn[r3 + 1] + ImageIn[r4 + 1] + ImageIn[r5 + 1] + ImageIn[r6 + 1];
        b = ImageIn[r1 + 2] + ImageIn[r2 + 2] + ImageIn[r3 + 2] + ImageIn[r4 + 2] + ImageIn[r5 + 2] + ImageIn[r6 + 2];
    }
    else if (d == 9)
    {
        r = ImageIn[r1] + ImageIn[r2] + ImageIn[r3] + ImageIn[r4] + ImageIn[r5] + ImageIn[r6] + ImageIn[r7] + ImageIn[r8] + ImageIn[r9];
        g = ImageIn[r1 + 1] + ImageIn[r2 + 1] + ImageIn[r3 + 1] + ImageIn[r4 + 1] + ImageIn[r5 + 1] + ImageIn[r6 + 1] + ImageIn[r7 + 1] + ImageIn[r8 + 1] + ImageIn[r9 + 1];
        b = ImageIn[r1 + 2] + ImageIn[r2 + 2] + ImageIn[r3 + 2] + ImageIn[r4 + 2] + ImageIn[r5 + 2] + ImageIn[r6 + 2] + ImageIn[r7 + 2] + ImageIn[r8 + 2] + ImageIn[r9 + 2];
    }

    ImageOut[j * 4] = r / d;
    ImageOut[j * 4 + 1] = g / d;
    ImageOut[j * 4 + 2] = b / d;
    ImageOut[j * 4 + 3] = ImageIn[j * 4 + 3];
}

void *processImage(void *blur)
{
    struct GaussianBlur *value = (struct GaussianBlur *)blur;
    int startValue = value->start, endValue = value->end;
    int r1 = 0, r2 = 0, r3 = 0, r4 = 0, r5 = 0, r6 = 0, r7 = 0, r8 = 0, r9 = 0;
    int row = 4 * width;     // calculate one row size of a image
    int full = row * height; // All row size of a image

    for (int i = startValue; i <= endValue; i++)
    {
        if (i == 0) //Left topmost corner pixel
        {
            r1 = i, r2 = i + 4, r3 = row, r4 = row + 4;
            RGB_SumDivide(i, 4, r1, r2, r3, r4, r5, r6, r7, r8, r9);
        }
        else if (i == (width - 1)) //(i==4)  Right topmost corner pixel
        {
            r1 = (i * 4) - 4, r2 = i * 4, r3 = row * 2 - 4 - 4, r4 = row * 2 - 4;
            RGB_SumDivide(i, 4, r1, r2, r3, r4, r5, r6, r7, r8, r9);
        }
        else if (i == (width * height) - width) //(i==20)  Left bottom-most corner pixel
        {
            r1 = full - (row * 2), r2 = full - (row * 2) + 4, r3 = i * 4, r4 = i * 4 + 4;
            RGB_SumDivide(i, 4, r1, r2, r3, r4, r5, r6, r7, r8, r9);
        }
        else if (i == (width * height - 1)) //i==24  Right bottom-most corner pixel
        {
            r1 = full - row - (4 * 2), r2 = full - row - 4, r3 = i * 4 - 4, r4 = i * 4;
            RGB_SumDivide(i, 4, r1, r2, r3, r4, r5, r6, r7, r8, r9);
        }
        else if (i < width) // Top Edge Row
        {
            r1 = i * 4 - 4, r2 = i * 4, r3 = i * 4 + 4, r4 = row + (i * 4 - 4), r5 = row + (i * 4), r6 = row + (i * 4) + 4;
            RGB_SumDivide(i, 6, r1, r2, r3, r4, r5, r6, r7, r8, r9);
        }
        else if (i == (width * (int)(i / width))) // Left Edge Row
        {
            r1 = i * 4 - row, r2 = i * 4 - row + 4, r3 = i * 4, r4 = i * 4 + 4, r5 = i * 4 + row, r6 = i * 4 + row + 4;
            RGB_SumDivide(i, 6, r1, r2, r3, r4, r5, r6, r7, r8, r9);
        }
        else if (i == width * (int)((i + width) / width) - 1) // Rigth Edge Row
        {
            r1 = i * 4 - row - 4, r2 = i * 4 - row, r3 = i * 4 - 4, r4 = i * 4, r5 = i * 4 + row - 4, r6 = i * 4 + row;
            RGB_SumDivide(i, 6, r1, r2, r3, r4, r5, r6, r7, r8, r9);
        }
        else if (i > (width * height) - width) // Bottom Edge Row
        {
            r1 = i * 4 - row - 4, r2 = i * 4 - row, r3 = i * 4 - row + 4, r4 = i * 4 - 4, r5 = i * 4, r6 = i * 4 + 4;
            RGB_SumDivide(i, 6, r1, r2, r3, r4, r5, r6, r7, r8, r9);
        }
        else // All Center Pixels
        {
            r1 = i * 4 - (row + 4), r2 = i * 4 - (row + 4) + 4, r3 = i * 4 + 4 + 4 - (row + 4), r4 = i * 4 - 4, r5 = i * 4, r6 = i * 4 + 4, r7 = i * 4 + row - 4, r8 = i * 4 + row, r9 = i * 4 + row + 4;
            RGB_SumDivide(i, 9, r1, r2, r3, r4, r5, r6, r7, r8, r9);
        }
    }
}
void slicing()
{
    // Preprocess for Images
    printf("In how many number of threads you want to encode image and run this program:\n");
    scanf("%d", &threadCount);

    error = lodepng_decode32_file(&ImageIn, &width, &height, "Data/image.png");
    if (error)
        printf("%d %s", error, lodepng_error_text(error));

    ImageOut = malloc(width * height * 4 * sizeof(char));
    n = width * height;

    // slicing for thread starts for here
    int sliceList[threadCount],
        remainder = n % threadCount,
        startList[threadCount],
        endList[threadCount];
    struct GaussianBlur mainStruct[threadCount];

    for (s = 0; s < threadCount; s++)
        sliceList[s] = n / threadCount;

    for (s = 0; s < remainder; s++)
        sliceList[s] += 1;

    for (s = 0; s < threadCount; s++)
    {
        if (s == 0)
            startList[s] = 0;
        else
            startList[s] = endList[s - 1] + 1;

        endList[s] = startList[s] + sliceList[s] - 1;
    }

    for (s = 0; s < threadCount; s++)
    {
        mainStruct[s].start = startList[s];
        mainStruct[s].end = endList[s];
    }

    pthread_t thread[threadCount];
    for (s = 0; s < threadCount; s++)
        pthread_create(&thread[s], NULL, processImage, &mainStruct[s]);

    for (s = 0; s < threadCount; s++)
        pthread_join(thread[s], NULL);

    // Encoding Image (output)
    lodepng_encode32_file("WOW_Image.png", ImageOut, width, height);
}

void main()
{
    slicing();

    free(ImageIn);
    free(ImageOut);
}
