#include "helpers.h"

typedef enum
{
    RED,
    GREEN,
    BLUE,
    RGB
}   rgb;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int gray;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            gray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtRed = gray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepia[RGB];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepia[RED] = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            if (sepia[RED] > 255)
                sepia[RED] = 255;
            sepia[GREEN] = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            if (sepia[GREEN] > 255)
                sepia[GREEN] = 255;
            sepia[BLUE] = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            if (sepia[BLUE] > 255)
                sepia[BLUE] = 255;
            image[i][j].rgbtRed = sepia[RED];
            image[i][j].rgbtGreen = sepia[GREEN];
            image[i][j].rgbtBlue = sepia[BLUE];
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
           RGBTRIPLE tmp;
           tmp = image[i][j];
           image[i][j] = image[i][width - j - 1];
           image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int dx[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    int dy[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
    RGBTRIPLE *tmp = malloc(sizeof(RGBTRIPLE) * height * width);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int x, y, count = 0, sum[RGB] = {};
            for (int k = 0; k < 9; k++)
            {
                x = j + dx[k];
                y = i + dy[k];
                if (x < 0 || x >= width || y < 0 || y >= height)
                    continue;
                sum[RED] += image[y][x].rgbtRed;
                sum[GREEN] += image[y][x].rgbtGreen;
                sum[BLUE] += image[y][x].rgbtBlue;
                count++;
            }
            tmp[i * width + j].rgbtRed = round(sum[RED] / (float)count);
            tmp[i * width + j].rgbtGreen = round(sum[GREEN] / (float)count);
            tmp[i * width + j].rgbtBlue = round(sum[BLUE] / (float)count);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            image[i][j] = tmp[i * width + j];
    }
    free(tmp);
    return;
}
