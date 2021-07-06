// 1 Blur
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "lodepng.h"

int i;
unsigned char *Image;
unsigned int width, height, error, encError;
unsigned int r = 0, g = 0, b = 0;
int count = 0;
void processImage()
{
    error = lodepng_decode32_file(&Image, &width, &height, "imag1.png");
    if (error)
    {
        printf("%d %s", error, lodepng_error_text(error));
    }

    for (i = 0; i < width * height * 4; i += 4)
    {
        if (i == 0)
        {
            // 4 corner pixel
            r = Image[i] + Image[i + 4] + Image[4 * width] + Image[4 * width + 4];
            g = Image[i + 1] + Image[i + 4 + 1] + Image[4 * width + 1] + Image[4 * width + 4 + 1];
            b = Image[i + 2] + Image[i + 4 + 2] + Image[4 * width + 2] + Image[4 * width + 4 + 2];
            Image[i] = r / 4;
            Image[i + 1] = g / 4;
            Image[i + 2] = b / 4;
        }
        // i==16
        else if (i == (width * 4 - 4))
        {
            // 4 corner pixel
            r = Image[i - 4] + Image[i] + Image[4 * width * 2 - 4 - 4] + Image[4 * width * 2 - 4];
            g = Image[i - 4 + 1] + Image[i + 1] + Image[4 * width * 2 - 4 - 4 + 1] + Image[4 * width * 2 - 4 + 1];
            b = Image[i - 4 + 2] + Image[i + 2] + Image[4 * width * 2 - 4 - 4 + 2] + Image[4 * width * 2 - 4 + 2];
            Image[i] = r / 4;
            Image[i + 1] = g / 4;
            Image[i + 2] = b / 4;
        }
        // i==80
        else if (i == (width * height * 4) - (width * 4))
        {
            // 4 corner pixel
            r = Image[(width * height * 4) - (width * 4 * 2)] + Image[(width * height * 4) - (width * 4 * 2) + 4] + Image[i] + Image[i + 4];
            g = Image[(width * height * 4) - (width * 4 * 2) + 1] + Image[(width * height * 4) - (width * 4 * 2) + 4 + 1] + Image[i + 1] + Image[i + 4 + 1];
            b = Image[(width * height * 4) - (width * 4 * 2) + 2] + Image[(width * height * 4) - (width * 4 * 2) + 4 + 2] + Image[i + 2] + Image[i + 4 + 2];
            Image[i] = r / 4;
            Image[i + 1] = g / 4;
            Image[i + 2] = b / 4;
        }
        // i==96
        else if (i == (width * height * 4 - 4))
        {
            // 4 corner pixel
            r = Image[(width * height * 4) - (width * 4) - (4 * 2)] + Image[(width * height * 4) - (width * 4) - 4] + Image[i - 4] + Image[i];
            g = Image[(width * height * 4) - (width * 4) - (4 * 2) + 1] + Image[(width * height * 4) - (width * 4) - 4 + 1] + Image[i - 4 + 1] + Image[i + 1];
            b = Image[(width * height * 4) - (width * 4) - (4 * 2) + 2] + Image[(width * height * 4) - (width * 4) - 4 + 2] + Image[i - 4 + 2] + Image[i + 2];
            Image[i] = r / 4;
            Image[i + 1] = g / 4;
            Image[i + 2] = b / 4;
        }

        // first row
        else if (i < (4 * width))
        {
            // second pixel
            r = Image[i - 4] + Image[i] + Image[i + 4] + Image[(4 * width) + (i - 4)] + Image[4 * width + i] + Image[4 * width + i + 4];
            g = Image[i - 4 + 1] + Image[i + 1] + Image[i + 4 + 1] + Image[(4 * width) + (i - 4) + 1] + Image[4 * width + i + 1] + Image[4 * width + i + 4 + 1];
            b = Image[i - 4 + 2] + Image[i + 2] + Image[i + 4 + 2] + Image[(4 * width) + (i - 4) + 2] + Image[4 * width + i + 2] + Image[4 * width + i + 4 + 2];
            Image[i] = r / 6;
            Image[i + 1] = g / 6;
            Image[i + 2] = b / 6;
        }
        // left side
        else if (i == ((4 * width) * (int)(i / (4 * width))))
        {
            // second pixel
            r = Image[i - (4 * width)] + Image[i - (4 * width) + 4] + Image[i] + Image[i + 4] + Image[i + (4 * width)] + Image[i + (4 * width) + 4];
            g = Image[i - (4 * width) + 1] + Image[i - (4 * width) + 4 + 1] + Image[i + 1] + Image[i + 4 + 1] + Image[i + (4 * width) + 1] + Image[i + (4 * width) + 4 + 1];
            b = Image[i - (4 * width) + 2] + Image[i - (4 * width) + 4 + 2] + Image[i + 2] + Image[i + 4 + 2] + Image[i + (4 * width) + 2] + Image[i + (4 * width) + 4 + 2];
            Image[i] = r / 6;
            Image[i + 1] = g / 6;
            Image[i + 2] = b / 6;
        }
        // right side
        else if (i == (4 * width) * (int)((i + (4 * width)) / (4 * width)) - 4)
        {
            count++;
            // second pixel
            r = Image[i - (4 * width) - 4] + Image[i - (4 * width)] + Image[i - 4] + Image[i] + Image[i + (4 * width) - 4] + Image[i + (4 * width)];
            g = Image[i - (4 * width) - 4 + 1] + Image[i - (4 * width) + 1] + Image[i - 4 + 1] + Image[i + 1] + Image[i + (4 * width) - 4 + 1] + Image[i + (4 * width) + 1];
            b = Image[i - (4 * width) - 4 + 2] + Image[i - (4 * width) + 2] + Image[i - 4 + 2] + Image[i + 2] + Image[i + (4 * width) - 4 + 2] + Image[i + (4 * width) + 2];
            Image[i] = r / 6;
            Image[i + 1] = g / 6;
            Image[i + 2] = b / 6;
        }
        // bottom row
        else if (i > (width * height * 4) - (width * 4))
        {
            // second pixel
            r = Image[i - (4 * width) - 4] + Image[i - (4 * width)] + Image[i - (4 * width) + 4] + Image[i - 4] + Image[i] + Image[i + 4];
            g = Image[i - (4 * width) - 4 + 1] + Image[i - (4 * width) + 1] + Image[i - (4 * width) + 4 + 1] + Image[i - 4 + 1] + Image[i + 1] + Image[i + 4 + 1];
            b = Image[i - (4 * width) - 4 + 2] + Image[i - (4 * width) + 2] + Image[i - (4 * width) + 4 + 2] + Image[i - 4 + 2] + Image[i + 2] + Image[i + 4 + 2];
            Image[i] = r / 6;
            Image[i + 1] = g / 6;
            Image[i + 2] = b / 6;
        }

        else
        {
            // center pixel
            r =
                Image[i - (4 * width + 4)] + Image[(i + 4) - (4 * width + 4)] + Image[(i + 4 + 4) - (4 * width + 4)] +
                Image[i - 4] + Image[i] + Image[i + 4] +
                Image[(i - 4) + (4 * width)] + Image[i + (4 * width)] + Image[(i + 4) + (4 * width)];

            g =
                Image[(i + 1) - (4 * width + 4)] + Image[(i + 4 + 1) - (4 * width + 4)] + Image[(i + 4 + 4 + 1) - (4 * width + 4)] +
                Image[i + 1 - 4] + Image[i + 1] + Image[i + 4 + 1] +
                Image[(i - 4 + 1) + (4 * width)] + Image[(i + 1) + (4 * width)] + Image[(i + 4 + 1) + (4 * width)];

            b =
                Image[(i + 2) - (4 * width + 4)] + Image[(i + 4 + 2) - (4 * width + 4)] + Image[(i + 4 + 4 + 2) - (4 * width + 4)] +
                Image[i - 4 + 2] + Image[i + 2] + Image[i + 4 + 2] +
                Image[(i - 4 + 2) + (4 * width)] + Image[(i + 2) + (4 * width)] + Image[(i + 4 + 2) + (4 * width)];

            Image[i] = r / 9;
            Image[i + 1] = g / 9;
            Image[i + 2] = b / 9;
        }
        //printf("%d %d %d %d\n", Image[i], Image[i + 1], Image[i + 2], Image[i + 3]);
    }
    lodepng_encode32_file("wow.png", Image, width, height);
    printf("\n\n%d %d\n", width, height);
}

void main()
{
    processImage();
}