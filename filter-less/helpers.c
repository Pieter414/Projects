#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

#define RED_COLOR 0
#define GREEN_COLOR 1
#define BLUE_COLOR 2

int check(int num);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // 1. Calculate average pixel value. If the data is float, convert into nearest int
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            // 2. Set each color value into the average value
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // 1. Calculate each new color value using Sepia formula
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            // 2. Check if the result between 0 and 255 inclusive, and assign it to the original image
            image[i][j].rgbtRed = check(sepiaRed);
            image[i][j].rgbtGreen = check(sepiaGreen);
            image[i][j].rgbtBlue = check(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // 1. Set up the k for getting the last pixel to swap and holds for temporarily swap
        int k = width - 1, holds[3];

        for (int j = 0; j < k; j++)
        {
            // 2. Hold the image far left RGB data
            holds[0] = image[i][j].rgbtRed;
            holds[1] = image[i][j].rgbtGreen;
            holds[2] = image[i][j].rgbtBlue;
            // 3. Swap pixel on horizontally opposite sides
            image[i][j].rgbtRed = image[i][k].rgbtRed;
            image[i][j].rgbtGreen = image[i][k].rgbtGreen;
            image[i][j].rgbtBlue = image[i][k].rgbtBlue;

            image[i][k].rgbtRed = holds[0];
            image[i][k].rgbtGreen = holds[1];
            image[i][k].rgbtBlue = holds[2];

            // 4. Subtract the k as parameter for opposite sides
            k--;
        }
    }
    return;
}

// Blur the image
int getBlur(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color)
{
    float count = 0.0;
    int sum = 0;
    for (int r0w = i - 1; r0w <= (i + 1); r0w++)
    {
        for (int c0lUmn = j - 1; c0lUmn <= (j + 1); c0lUmn++)
        {
            if (r0w < 0 || r0w >= height || c0lUmn < 0 || c0lUmn >= width)
            {
                continue;
            }
            if (color == RED_COLOR)
            {
                sum += image[r0w][c0lUmn].rgbtRed;
            }
            else if (color == GREEN_COLOR)
            {
                sum += image[r0w][c0lUmn].rgbtGreen;
            }
            else
            {
                sum += image[r0w][c0lUmn].rgbtBlue;
            }
            count++;
        }
    }
    return round(sum / count);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = getBlur(i, j, height, width, copy, 0);
            image[i][j].rgbtGreen = getBlur(i, j, height, width, copy, 1);
            image[i][j].rgbtBlue = getBlur(i, j, height, width, copy, 2);
        }
    }
    return;
}

// Check function for the sepia filter
int check(int num)
{
    if (num > 255)
    {
        return 255;
    }
    else if (num < 0)
    {
        return 0;
    }
    else
    {
        return num;
    }
}

int getEdges(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color)
{
    // 4. Declare the sum for Gx and Gy
    int sumGX = 0, sumGY = 0, new_value;
    // 5. Calculate the sum Gx and Gy
    for (int r0w = i - 1; r0w <= (i + 1); r0w++)
    {
        for (int c0lUmn = j - 1; c0lUmn <= (j + 1); c0lUmn++)
        {
            // 6. Check if the row and column are out of border, if yes just += 0 and continue
            if (r0w < 0 || r0w >= height || c0lUmn < 0 || c0lUmn >= width)
            {
                sumGX += 0;
                sumGY += 0;
                continue;
            }
            // 7. Check what color type, red green or blue
            if (color == RED_COLOR)
            {
                // 7b. Check of the position of the box
                // box 1 (upper left gx)
                if (r0w == i - 1 && c0lUmn == j - 1)
                {
                    sumGX += image[r0w][c0lUmn].rgbtRed * -1;
                    sumGY += image[r0w][c0lUmn].rgbtRed * -1;
                }
                // box 2 (upper middle gx)
                else if (r0w == i - 1 && c0lUmn == j)
                {
                    sumGX += image[r0w][c0lUmn].rgbtRed * 0;
                    sumGY += image[r0w][c0lUmn].rgbtRed * -2;
                }
                // box 3 (upper right gx)
                else if (r0w == i - 1 && c0lUmn == j + 1)
                {
                    sumGX += image[r0w][c0lUmn].rgbtRed * 1;
                    sumGY += image[r0w][c0lUmn].rgbtRed * -1;
                }
                // box 4 (middle left gx)
                else if (r0w == i && c0lUmn == j - 1)
                {
                    sumGX += image[r0w][c0lUmn].rgbtRed * -2;
                    sumGY += image[r0w][c0lUmn].rgbtRed * 0;
                }
                // box 5 (middle center gx)
                else if (r0w == i && c0lUmn == j)
                {
                    sumGX += image[r0w][c0lUmn].rgbtRed * 0;
                    sumGY += image[r0w][c0lUmn].rgbtRed * 0;
                }
                // box 6 (middle right gx)
                else if (r0w == i && c0lUmn == j + 1)
                {
                    sumGX += image[r0w][c0lUmn].rgbtRed * 2;
                    sumGY += image[r0w][c0lUmn].rgbtRed * 0;
                }
                // box 7 (lower left gx)
                else if (r0w == i + 1 && c0lUmn == j - 1)
                {
                    sumGX += image[r0w][c0lUmn].rgbtRed * -1;
                    sumGY += image[r0w][c0lUmn].rgbtRed * 1;
                }
                // box 8 (lower middle gx)
                else if (r0w == i + 1 && c0lUmn == j)
                {
                    sumGX += image[r0w][c0lUmn].rgbtRed * 0;
                    sumGY += image[r0w][c0lUmn].rgbtRed * 2;
                }
                // box 9 (lower right gx)
                else if (r0w == i + 1 && c0lUmn == j + 1)
                {
                    sumGX += image[r0w][c0lUmn].rgbtRed * 1;
                    sumGY += image[r0w][c0lUmn].rgbtRed * 1;
                }
            }
            else if (color == GREEN_COLOR)
            {
                // 7b. Check of the position of the box
                // box 1 (upper left gx)
                if (r0w == i - 1 && c0lUmn == j - 1)
                {
                    sumGX += image[r0w][c0lUmn].rgbtGreen * -1;
                    sumGY += image[r0w][c0lUmn].rgbtGreen * -1;
                }
                // box 2 (upper middle gx)
                else if (r0w == i - 1 && c0lUmn == j)
                {
                    sumGX += image[r0w][c0lUmn].rgbtGreen * 0;
                    sumGY += image[r0w][c0lUmn].rgbtGreen * -2;
                }
                // box 3 (upper right gx)
                else if (r0w == i - 1 && c0lUmn == j + 1)
                {
                    sumGX += image[r0w][c0lUmn].rgbtGreen * 1;
                    sumGY += image[r0w][c0lUmn].rgbtGreen * -1;
                }
                // box 4 (middle left gx)
                else if (r0w == i && c0lUmn == j - 1)
                {
                    sumGX += image[r0w][c0lUmn].rgbtGreen * -2;
                    sumGY += image[r0w][c0lUmn].rgbtGreen * 0;
                }
                // box 5 (middle center gx)
                else if (r0w == i && c0lUmn == j)
                {
                    sumGX += image[r0w][c0lUmn].rgbtGreen * 0;
                    sumGY += image[r0w][c0lUmn].rgbtGreen * 0;
                }
                // box 6 (middle right gx)
                else if (r0w == i && c0lUmn == j + 1)
                {
                    sumGX += image[r0w][c0lUmn].rgbtGreen * 2;
                    sumGY += image[r0w][c0lUmn].rgbtGreen * 0;
                }
                // box 7 (lower left gx)
                else if (r0w == i + 1 && c0lUmn == j - 1)
                {
                    sumGX += image[r0w][c0lUmn].rgbtGreen * -1;
                    sumGY += image[r0w][c0lUmn].rgbtGreen * 1;
                }
                // box 8 (lower middle gx)
                else if (r0w == i + 1 && c0lUmn == j)
                {
                    sumGX += image[r0w][c0lUmn].rgbtGreen * 0;
                    sumGY += image[r0w][c0lUmn].rgbtGreen * 2;
                }
                // box 9 (lower right gx)
                else if (r0w == i + 1 && c0lUmn == j + 1)
                {
                    sumGX += image[r0w][c0lUmn].rgbtGreen * 1;
                    sumGY += image[r0w][c0lUmn].rgbtGreen * 1;
                }
            }
            else
            {
                // 7b. Check of the position of the box
                // box 1 (upper left gx)
                if (r0w == i - 1 && c0lUmn == j - 1)
                {
                    sumGX += image[r0w][c0lUmn].rgbtBlue * -1;
                    sumGY += image[r0w][c0lUmn].rgbtBlue * -1;
                }
                // box 2 (upper middle gx)
                else if (r0w == i - 1 && c0lUmn == j)
                {
                    sumGX += image[r0w][c0lUmn].rgbtBlue * 0;
                    sumGY += image[r0w][c0lUmn].rgbtBlue * -2;
                }
                // box 3 (upper right gx)
                else if (r0w == i - 1 && c0lUmn == j + 1)
                {
                    sumGX += image[r0w][c0lUmn].rgbtBlue * 1;
                    sumGY += image[r0w][c0lUmn].rgbtBlue * -1;
                }
                // box 4 (middle left gx)
                else if (r0w == i && c0lUmn == j - 1)
                {
                    sumGX += image[r0w][c0lUmn].rgbtBlue * -2;
                    sumGY += image[r0w][c0lUmn].rgbtBlue * 0;
                }
                // box 5 (middle center gx)
                else if (r0w == i && c0lUmn == j)
                {
                    sumGX += image[r0w][c0lUmn].rgbtBlue * 0;
                    sumGY += image[r0w][c0lUmn].rgbtBlue * 0;
                }
                // box 6 (middle right gx)
                else if (r0w == i && c0lUmn == j + 1)
                {
                    sumGX += image[r0w][c0lUmn].rgbtBlue * 2;
                    sumGY += image[r0w][c0lUmn].rgbtBlue * 0;
                }
                // box 7 (lower left gx)
                else if (r0w == i + 1 && c0lUmn == j - 1)
                {
                    sumGX += image[r0w][c0lUmn].rgbtBlue * -1;
                    sumGY += image[r0w][c0lUmn].rgbtBlue * 1;
                }
                // box 8 (lower middle gx)
                else if (r0w == i + 1 && c0lUmn == j)
                {
                    sumGX += image[r0w][c0lUmn].rgbtBlue * 0;
                    sumGY += image[r0w][c0lUmn].rgbtBlue * 2;
                }
                // box 9 (lower right gx)
                else if (r0w == i + 1 && c0lUmn == j + 1)
                {
                    sumGX += image[r0w][c0lUmn].rgbtBlue * 1;
                    sumGY += image[r0w][c0lUmn].rgbtBlue * 1;
                }
            }
        }
    }
    // 8. Calculate the new_value
    new_value = round(sqrt((float) pow(sumGX, 2) + (float) pow(sumGY, 2)));
    if (new_value > 255)
    {
        new_value = 255;
    }
    else if (new_value < 0)
    {
        new_value = 0;
    }
    return new_value;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // 1. Make copy of the image for calculating
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // 2. Nested loop for each block
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // 3. Assign the new RGB into the image from the updated copy
            image[i][j].rgbtRed = getEdges(i, j, height, width, copy, 0);
            image[i][j].rgbtGreen = getEdges(i, j, height, width, copy, 1);
            image[i][j].rgbtBlue = getEdges(i, j, height, width, copy, 2);
        }
    }
    return;
}
