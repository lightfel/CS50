#include "helpers.h"

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
typedef enum
{
    RED,
    GREEN,
    BLUE,
    RGB
}   rgb;

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

// Detect edges
typedef struct
{
    int  rgbtBlue;
    int  rgbtGreen;
    int  rgbtRed;
}
MYRGBTRIPLE;

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int dx[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    int dy[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
    int gx[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    int gy[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    MYRGBTRIPLE *tmp_gx = malloc(sizeof(MYRGBTRIPLE) * height * width);
    MYRGBTRIPLE *tmp_gy = malloc(sizeof(MYRGBTRIPLE) * height * width);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int x, y;
            for (int k = 0; k < 9; k++)
            {
                x = j + dx[k];
                y = i + dy[k];
                if (x < 0 || x >= width || y < 0 || y >= height)
                    continue;
                tmp_gx[i * width + j].rgbtRed += image[y][x].rgbtRed * gx[k];
                tmp_gx[i * width + j].rgbtGreen += image[y][x].rgbtGreen * gx[k];
                tmp_gx[i * width + j].rgbtBlue += image[y][x].rgbtBlue * gx[k];
                tmp_gy[i * width + j].rgbtRed += image[y][x].rgbtRed * gy[k];
                tmp_gy[i * width + j].rgbtGreen += image[y][x].rgbtGreen * gy[k];
                tmp_gy[i * width + j].rgbtBlue += image[y][x].rgbtBlue * gy[k];
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int value;

            value = round(sqrt(pow(tmp_gx[i * width + j].rgbtRed, 2) + pow(tmp_gy[i * width + j].rgbtRed, 2)));
            if (value > 255)
                value = 255;
            image[i][j].rgbtRed = value;
            value = round(sqrt(pow(tmp_gx[i * width + j].rgbtGreen, 2) + pow(tmp_gy[i * width + j].rgbtGreen, 2)));
            if (value > 255)
                value = 255;
            image[i][j].rgbtGreen = value;
            value = round(sqrt(pow(tmp_gx[i * width + j].rgbtBlue, 2) + pow(tmp_gy[i * width + j].rgbtBlue, 2)));
            if (value > 255)
                value = 255;
            image[i][j].rgbtBlue = value;
        }
    }
    free(tmp_gx);
    free(tmp_gy);
    return;
}
