#include "C:\Users\lenovo\Desktop\github repo\filter-more\helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = image[i][j].rgbtRed = image[i][j].rgbtGreen = round((image[i][j].rgbtBlue + image[i][j].rgbtRed +
                                   image[i][j].rgbtGreen) / 3.00);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < floor(width / 2); j++)
            //floor(width/2) allows j to only go up to mid point of the width of picture, because if it went all the way of the width, it would return the pic same as before as all pixcels would end up in same position as all will be replaced twice
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //set up a temp file to hold the changed image
    RGBTRIPLE temp_image[height][width];


    int avg_red;
    int avg_green;
    int avg_blue;


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //checks if the selected pixel is not on the edge or a corner
            if (i != 0 && i != height - 1 && j != 0 && j != width - 1)
            {
                //these 3 lines of codes find avg values of RGB in 1 pixel around and within a set pixel
                avg_red = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                 image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
                                 image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9.00);
                avg_green = round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                   image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                   image[i + 1][j - 1].rgbtGreen +  image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9.00);
                avg_blue = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                  image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                                  image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9.00);


            }
            else if (i == 0 && j == 0)
            {
                avg_red = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 4.00);
                avg_green = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                   image[i + 1][j + 1].rgbtGreen) / 4.00);
                avg_blue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                  image[i + 1][j + 1].rgbtBlue) / 4.00);

            }
            else if (i == 0 && j == width - 1)
            {
                avg_red = round((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed)
                                / 4.00);
                avg_green = round((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                                   image[i + 1][j].rgbtGreen) / 4.00);
                avg_blue = round((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                                  image[i + 1][j].rgbtBlue) / 4.00);

            }
            else if (i == height - 1 && j == 0)
            {
                avg_red = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed +
                                 image[i - 1][j + 1].rgbtRed) / 4.00);
                avg_green = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                   image[i - 1][j + 1].rgbtGreen) / 4.00);
                avg_blue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                  image[i - 1][j + 1].rgbtBlue) / 4.00);

            }
            else if (i == height - 1 && j == width - 1)
            {
                avg_red = round((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i - 1][j - 1].rgbtRed +
                                 image[i - 1][j].rgbtRed) / 4.00);
                avg_green = round((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                                   image[i - 1][j].rgbtGreen) / 4.00);
                avg_blue = round((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                                  image[i - 1][j].rgbtBlue) / 4.00);
            }
            else if (i == 0 && j != 0 && j != width - 1)
            {
                avg_red = round((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
                                 image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.00);
                avg_green = round((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                   image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.00);
                avg_blue = round((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                  image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.00);

            }
            else if (j == 0 && i != 0 && i != height - 1)
            {
                avg_red = round((image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                                 image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.00);
                avg_green = round((image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j].rgbtGreen +
                                   image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.00);
                avg_blue = round((image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j].rgbtBlue +
                                  image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.00);
            }
            else if (i == height - 1 && j != 0 && j != width - 1)
            {
                avg_red = round((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed +
                                 image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6.00);
                avg_green = round((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                   image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6.00);
                avg_blue = round((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                  image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6.00);
            }
            else if (j == width - 1 && i != 0 && i != height - 1)
            {
                avg_red = round((image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j - 1].rgbtRed +
                                 image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6.00);
                avg_green = round((image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i][j].rgbtGreen +
                                   image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6.00);
                avg_blue = round((image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j].rgbtBlue +
                                  image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6.00);
            }
            temp_image[i][j].rgbtRed = avg_red;
            temp_image[i][j].rgbtGreen = avg_green;
            temp_image[i][j].rgbtBlue = avg_blue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp_image[i][j];
        }
    }


    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //make a temp copy of image so original one is not changed untill all the pixels have been changed
    RGBTRIPLE temp_image[height][width];

    //initialize the Gx and Gy values
    int gx_red, gx_green, gx_blue, gy_red, gy_green, gy_blue;
    int gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            gx_red = gx_green = gx_blue = gy_red = gy_green = gy_blue = 0;

            for (int r = -1; r < 2; r++)
            {
                for (int c = -1; c < 2; c++)
                {
                    //check if pixel is outside the image
                    if (i + r < 0 || i + r > height - 1)
                    {
                        continue;
                    }

                    if (j + c < 0 || j + c > width - 1)
                    {
                        continue;
                    }
                    //calculate the sum of gx and gy values of each color
                    gx_red += image[i + r][j + c].rgbtRed * gx[r + 1][c + 1];
                    gx_green += image[i + r][j + c].rgbtGreen * gx[r + 1][c + 1];
                    gx_blue += image[i + r][j + c].rgbtBlue * gx[r + 1][c + 1];

                    gy_red += image[i + r][j + c].rgbtRed * gy[r + 1][c + 1];
                    gy_green += image[i + r][j + c].rgbtGreen * gy[r + 1][c + 1];
                    gy_blue += image[i + r][j + c].rgbtBlue * gy[r + 1][c + 1];


                }
            }

            //fmin found from google.
            //stores the changed image to the temp image
            temp_image[i][j].rgbtRed = fmin(round(sqrt(gx_red * gx_red + gy_red * gy_red)), 255);
            temp_image[i][j].rgbtGreen = fmin(round(sqrt(gx_green * gx_green + gy_green * gy_green)), 255);
            temp_image[i][j].rgbtBlue = fmin(round(sqrt(gx_blue * gx_blue + gy_blue * gy_blue)), 255);


        }
    }
    //puts the temp image in actual image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp_image[i][j];
        }
    }


}