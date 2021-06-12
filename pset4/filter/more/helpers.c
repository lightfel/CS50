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
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int dx[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    int dy[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
    RGBTRIPLE *tmp = malloc(sizeof(RGBTRIPLE) * height * width);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int x, y, count = 0, sum[3] = {};
            for (int k = 0; k < 9; k++)
            {
                x = j + dx[k];
                y = i + dy[k];
                if (x < 0 || x >= width || y < 0 || y >= height)
                    continue;
                sum[0] += image[y][x].rgbtRed;
                sum[1] += image[y][x].rgbtGreen;
                sum[2] += image[y][x].rgbtBlue;
                count++;
            }
            tmp[i * width + j].rgbtRed = round(sum[0] / (float)count);
            tmp[i * width + j].rgbtGreen = round(sum[1] / (float)count);
            tmp[i * width + j].rgbtBlue = round(sum[2] / (float)count);
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
            int x, y, sum_gx[3] = {}, sum_gy[3] = {};
            for (int k = 0; k < 9; k++)
            {
                x = j + dx[k];
                if (x < 0 || x >= width)
                    continue;
                y = i + dy[k];
                if (y < 0 || y >= height)
                    continue;
                sum_gx[0] += image[y][x].rgbtRed * gx[k];
                sum_gx[1] += image[y][x].rgbtGreen * gx[k];
                sum_gx[2] += image[y][x].rgbtBlue * gx[k];
                sum_gy[0] += image[y][x].rgbtRed * gy[k];
                sum_gy[1] += image[y][x].rgbtGreen * gy[k];
                sum_gy[2] += image[y][x].rgbtBlue * gy[k];
                //printf("%d %d %d %d %d %d\n", i, j, k, gy[k], sum_gx[0], sum_gy[0]);
            }
            //printf("1:%d %d %d %d\n", i, j, sum_gx[0], sum_gy[0]);
            tmp_gx[i * width + j].rgbtRed = sum_gx[0];
            tmp_gx[i * width + j].rgbtGreen = sum_gx[1];
            tmp_gx[i * width + j].rgbtBlue = sum_gx[2];
            tmp_gy[i * width + j].rgbtRed = sum_gy[0];
            tmp_gy[i * width + j].rgbtGreen = sum_gy[1];
            tmp_gy[i * width + j].rgbtBlue = sum_gy[2];
            //printf("%d, %d\n", tmp_gy[i * width + j].rgbtRed, sum_gy[0]);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp_gx[i * width + j].rgbtRed = round(sqrt(pow(tmp_gx[i * width + j].rgbtRed, 2) + pow(tmp_gy[i * width + j].rgbtRed, 2)));
            if (tmp_gx[i * width + j].rgbtRed > 255)
                tmp_gx[i * width + j].rgbtRed = 255;
            image[i][j].rgbtRed = tmp_gx[i * width + j].rgbtRed;
            //printf("%d, %d, %d, %d\n", i, j, tmp_gx[i * width + j].rgbtRed, tmp_gy[i * width + j].rgbtRed);
            //printf("%f\n", sqrt(pow(tmp_gx[i * width + j].rgbtRed, 2)+pow(tmp_gy[i * width + j].rgbtRed, 2)));
            //printf("%d\n", image[i][j].rgbtRed);
            tmp_gx[i * width + j].rgbtGreen = round(sqrt(pow(tmp_gx[i * width + j].rgbtGreen, 2) + pow(tmp_gy[i * width + j].rgbtGreen, 2)));
            if (tmp_gx[i * width + j].rgbtGreen > 255)
                tmp_gx[i * width + j].rgbtGreen = 255;
            image[i][j].rgbtGreen = tmp_gx[i * width + j].rgbtGreen;
            tmp_gx[i * width + j].rgbtBlue = round(sqrt(pow(tmp_gx[i * width + j].rgbtBlue, 2) + pow(tmp_gy[i * width + j].rgbtBlue, 2)));
            if (tmp_gx[i * width + j].rgbtBlue > 255)
                tmp_gx[i * width + j].rgbtBlue = 255;
            image[i][j].rgbtBlue = tmp_gx[i * width + j].rgbtBlue;
        }
    }
    free(tmp_gx);
    free(tmp_gy);
    return;
}
/*
int main(void)
{
    RGBTRIPLE image[3][3];
    int width = 3;
    int height = 3;
    image[0][0].rgbtRed = 10;
    image[0][0].rgbtGreen = 20;
    image[0][0].rgbtBlue = 30;
    image[0][1].rgbtRed = 20;
    image[0][1].rgbtGreen = 30;
    image[0][1].rgbtBlue = 40;
    image[0][2].rgbtRed = 30;
    image[0][2].rgbtGreen = 40;
    image[0][2].rgbtBlue = 50;
    image[1][0].rgbtRed = 40;
    image[1][0].rgbtGreen = 50;
    image[1][0].rgbtBlue = 60;
    image[1][1].rgbtRed = 50;
    image[1][1].rgbtGreen = 60;
    image[1][1].rgbtBlue = 70;
    image[1][2].rgbtRed = 60;
    image[1][2].rgbtGreen = 70;
    image[1][2].rgbtBlue = 80;
    image[2][0].rgbtRed = 70;
    image[2][0].rgbtGreen = 20;
    image[2][0].rgbtBlue = 30;
    image[2][1].rgbtRed = 80;
    image[2][1].rgbtGreen = 30;
    image[2][1].rgbtBlue = 40;
    image[2][2].rgbtRed = 90;
    image[2][2].rgbtGreen = 40;
    image[2][2].rgbtBlue = 50;
    for (int i = 0; i < height; i++)
    {
        for (int j =0; j < width; j++)
            printf("%d ", image[i][j].rgbtRed);
        printf("\n");
    }
    edges(height, width, image);
    for (int i = 0; i < height; i++)
    {
        for (int j =0; j < width; j++)
            printf("%d ", image[i][j].rgbtRed);
        printf("\n");
    }
}
*/
