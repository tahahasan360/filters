#include "helpers.h"
#include <math.h>
#include <stdlib.h>

//Initializes Gx and Gy kernels in the form of 2D arrays
int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

// Converts image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int x = round(((float)image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);
            image[i][j].rgbtRed = x;
            image[i][j].rgbtGreen = x;
            image[i][j].rgbtBlue = x;
        }
    }
    return;
}

// Reflects image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, w = round((float) width / 2); j < w; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blurs image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*tmp)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = 0;
            int blue = 0;
            int green = 0;
            int addcounter = 0;
            for (int i2 = -1; i2 < 2; i2++)
            {
                for (int j2 = -1; j2 < 2; j2++)
                {
                    if ((i + i2 >= 0) && (i + i2 < height) && (j + j2 >= 0) && (j + j2 < width))
                    {
                        red += image[i + i2][j + j2].rgbtRed;
                        blue += image[i + i2][j + j2].rgbtBlue;
                        green += image[i + i2][j + j2].rgbtGreen;
                        addcounter++;
                    }
                }
            }
            tmp[i][j].rgbtRed = round((float) red / addcounter);
            tmp[i][j].rgbtGreen = round((float) green / addcounter);
            tmp[i][j].rgbtBlue = round((float) blue / addcounter);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*tmp)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            unsigned int red = 0;
            unsigned int blue = 0;
            unsigned int green = 0;
            long redx = 0;
            long bluex = 0;
            long greenx = 0;
            long redy = 0;
            long bluey = 0;
            long greeny = 0;
            for (int i2 = -1; i2 < 2; i2++)
            {
                for (int j2 = -1; j2 < 2; j2++)
                {
                    if ((i + i2 >= 0) && (i + i2 < height) && (j + j2 >= 0) && (j + j2 < width))
                    {
                        redx += image[i + i2][j + j2].rgbtRed * Gx[i2 + 1][j2 + 1];
                        bluex += image[i + i2][j + j2].rgbtBlue * Gx[i2 + 1][j2 + 1];
                        greenx += image[i + i2][j + j2].rgbtGreen * Gx[i2 + 1][j2 + 1];
                        redy += image[i + i2][j + j2].rgbtRed * Gy[i2 + 1][j2 + 1];
                        bluey += image[i + i2][j + j2].rgbtBlue * Gy[i2 + 1][j2 + 1];
                        greeny += image[i + i2][j + j2].rgbtGreen * Gy[i2 + 1][j2 + 1];
                    }
                }
            }
            red = round(sqrt((redx * redx) + (redy * redy)));
            green = round(sqrt((greenx * greenx) + (greeny * greeny)));
            blue = round(sqrt((bluex * bluex) + (bluey * bluey)));
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            tmp[i][j].rgbtRed = red;
            tmp[i][j].rgbtGreen = green;
            tmp[i][j].rgbtBlue = blue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }
    return;
}

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = round((float) image[i][j].rgbtRed * 0.393 + (float) image[i][j].rgbtGreen * 0.769 + (float) image[i][j].rgbtBlue * 0.189);
            int green = round((float) image[i][j].rgbtRed * 0.349 + (float) image[i][j].rgbtGreen * 0.686 + (float) image[i][j].rgbtBlue * 0.168);
            int blue = round((float) image[i][j].rgbtRed * 0.272 + (float) image[i][j].rgbtGreen * 0.534 + (float) image[i][j].rgbtBlue * 0.131);
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}
