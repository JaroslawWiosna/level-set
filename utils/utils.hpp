#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <math.h>

float Heaviside(float data)
{
	return ((data >= 0) ? 1 : 0);
}

float Average_c1(float ** phi, float ** fimage, int rows, int cols)
{
    float sum = 0;  //Sum of pixel values
    int pixnum = 0; //number of pixels inside circle
    for (std::size_t i = 1; i < rows-1; ++i)
        for (std::size_t j = 1; j < cols-1; ++j)
        {
            if (Heaviside(phi[i][j]))   //if phi > 0 ==> pixel inside circle
            {
                sum += fimage[i][j];
                pixnum++;
            }
        }
        
    return sum/pixnum;
}

float Average_c2(float ** phi, float ** fimage, int rows, int cols)
{
    float sum = 0;  //Sum of pixel values
    int pixnum = 0; //number of pixels outside circle
    for (std::size_t i = 1; i < rows-1; ++i)
        for (std::size_t j = 1; j < cols-1; ++j)
        {
            if (!Heaviside(phi[i][j]))  //if phi < 0 ==> pixel inside circle
            {
                sum += fimage[i][j];
                pixnum++;
            }
        }
        
    return sum/pixnum;
}

