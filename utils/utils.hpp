#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <math.h>

float Heaviside(float data)
{
	return ((data >= 0) ? 1 : 0);
}

std::pair<float, float> Average_c(float ** phi, float ** fimage, int rows, int cols)
{
    float sum_inside{}; // inside or on border
    float sum_outside{};
    int pixnum{}; //number of pixels inside circle
    for (std::size_t i = 1; i < rows-1; ++i)
        for (std::size_t j = 1; j < cols-1; ++j)
        {
            if (Heaviside(phi[i][j]))   //if phi > 0 ==> pixel inside circle
            {
                sum_inside += fimage[i][j];
                pixnum++;
            }
            else // if (Heaviside(phi[i][j]))   //if phi < 0 ==> pixel outside circle
            {
                sum_outside += fimage[i][j];
            }
        }
    return std::make_pair(sum_inside/pixnum, sum_outside/(rows*cols-pixnum));
}

