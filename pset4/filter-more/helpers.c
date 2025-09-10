#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int gy[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    RGBTRIPLE temp[height][width];

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int red = 0;
            int red1 = 0;
            int green = 0;
            int green1 = 0;
            int blue = 0;
            int blue1 = 0;
            int count = 0;
            for(int a = -1; a < 2; a++){
                for(int b = -1; b < 2; b++){
                    if(i+a >= 0 && i+a <= height-1 && j+b >= 0 && j+b <= width-1){
                        red += image[i+a][j+b].rgbtRed*gx[count];
                        green += image[i+a][j+b].rgbtGreen*gx[count];
                        blue += image[i+a][j+b].rgbtBlue*gx[count];

                        red1 += image[i+a][j+b].rgbtRed*gy[count];
                        green1 += image[i+a][j+b].rgbtGreen*gy[count];
                        blue1 += image[i+a][j+b].rgbtBlue*gy[count];
                    }
                    count++;
                }
            }
            temp[i][j].rgbtRed = (int)fmin(round(sqrt(pow(red, 2) + pow(red1, 2))), 255);
            temp[i][j].rgbtGreen = (int)fmin(round(sqrt(pow(green, 2) + pow(green1, 2))), 255);
            temp[i][j].rgbtBlue = (int)fmin(round(sqrt(pow(blue, 2) + pow(blue1, 2))), 255);
        }
    }

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            image[i][j] = temp[i][j];
        }
    }
    return;
}
