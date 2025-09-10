#include "helpers.h"

//lembrando que o minimo para cada cor eh 0 e o maximo eh 255

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int mean = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3;
            image[i][j].rgbtRed = mean;
            image[i][j].rgbtGreen = mean;
            image[i][j].rgbtBlue = mean;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            image[i][j].rgbtRed = (0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue);
            image[i][j].rgbtGreen = (0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue);
            image[i][j].rgbtBlue = (0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width/2; j++){ //devemos percorrer apenas metade da largura da imagem, se nao trocariamos os pixels duas vezes
            RGBTRIPLE aux = image[i][j];
            image[i][j] = image[i][width-1-j];
            image[i][width-1-j] = aux;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int red = 0;
            int blue = 0;
            int green = 0;
            int count = 0;
            for(int a = -1; a < 2; a++){
                for(int b = -1; b < 2; b++){
                    if((i+a >= 0 && i+a <= height-1) && (j+b >= 0 && j+b <= width-1)){
                        red += image[i+a][j+b].rgbtRed;
                        blue += image[i+a][j+b].rgbtBlue;
                        green += image[i+a][j+b].rgbtGreen;
                        count++;
                    }
                }
            }
            image[i][j].rgbtRed = red/count;
            image[i][j].rgbtBlue = blue/count;
            image[i][j].rgbtGreen = green/count;
        }
    }
    return;
}

