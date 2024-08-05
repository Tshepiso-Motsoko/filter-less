#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over each row
    for (int i = 0; i < height; i++)
    {
        // Loop over each pixel in row
        for (int j = 0; j < width; j++)
        {
            // Get pixel's color
            RGBTRIPLE pixel = image[i][j];

            // Calculate average of RGB values (add 0.5 for rounding)
            int avg = round((pixel.rgbtRed + pixel.rgbtBlue + pixel.rgbtGreen) / 3.0);

            // Set new color
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over each row
    for (int i = 0; i < height; i++)
    {
        // Loop over each pixel in row
        for (int j = 0; j < width; j++)
        {
            // Get original color values
            RGBTRIPLE original = image[i][j];

            // Calculate new color values
            int sepiaRed = round(0.393 * original.rgbtRed + 0.769 * original.rgbtGreen + 0.189 * original.rgbtBlue);
            int sepiaGreen = round(0.349 * original.rgbtRed + 0.686 * original.rgbtGreen + 0.168 * original.rgbtBlue);
            int sepiaBlue = round(0.272 * original.rgbtRed + 0.534 * original.rgbtGreen + 0.131 * original.rgbtBlue);

            // Cap values at 255
            sepiaRed = (sepiaRed > 255) ? 255 : sepiaRed;
            sepiaGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            sepiaBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;

            // Set new color
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over each row
    for (int i = 0; i < height; i++)
    {
        // Loop over half of the pixels in the row
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixel with its mirror image
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy the original image
    RGBTRIPLE original[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original[i][j] = image[i][j];
        }
    }

    // Loop over each row
    for (int i = 0; i < height; i++)
    {
        // Loop over each pixel in row
        for (int j = 0; j < width; j++)
        {
            // Initialize sum and count for average
            int sumRed = 0, sumGreen = 0, sumBlue = 0, count = 0;

            // Loop over the pixel and its neighbors
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    // Ensure pixel's neighbor is in the image
                    if (i + k >= 0 && i + k < height && j + l >= 0 && j + l < width)
                    {
                        // Add color value to sum
                        sumRed += original[i + k][j + l].rgbtRed;
                        sumGreen += original[i + k][j + l].rgbtGreen;
                        sumBlue += original[i + k][j + l].rgbtBlue;
                        count++;
                    }
                }
            }

            // Set new color values
            image[i][j].rgbtRed = round(sumRed / (float)count);
            image[i][j].rgbtGreen = round(sumGreen / (float)count);
            image[i][j].rgbtBlue = round(sumBlue / (float)count);
        }
    }
}
