#include <cstdio>
#include <opencv2/opencv.hpp>
#include <cmath>

float Heaviside(float data)
{
	return ((data >= 0) ? 1 : 0);
}

std::pair<float, float> Average_c(float ** phi, float ** fimage, int rows, int cols)
{
    float sum_inside{}; // inside or on border
    float sum_outside{};
    int pixnum_inside{}; //number of pixels inside circle
    int pixnum_outside{}; //number of pixels outside circle
    for (std::size_t i = 1; i < rows-1; ++i)
        for (std::size_t j = 1; j < cols-1; ++j)
        {
            if (Heaviside(phi[i][j]))   //if phi > 0 ==> pixel inside circle
            {
                sum_inside += fimage[i][j];
                pixnum_inside++;
            }
            else // if (Heaviside(phi[i][j]))   //if phi < 0 ==> pixel outside circle
            {
                sum_outside += fimage[i][j];
                pixnum_outside++;
            }
        }
    return std::make_pair(sum_inside/pixnum_inside, sum_outside/pixnum_outside);
}

void initializePhi(float** phi, int rows, int cols, int type=1) {
    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
        {
            phi[i][j] = 100 - sqrt( (rows/2-i)*(rows/2-i) + (cols/2-j)*(cols/2-j) ); //Middle point of a circle depends on image size 
	    //phi[i][j] = Heaviside(phi[i][j]);
            /*
            if (100 - sqrt( (rows/2-i)*(rows/2-i) + (cols/2-j)*(cols/2-j) ) >= 0)
                phi[i][j] = 1;
            else
                phi[i][j] = -1;
		*/
            //phi[i][j] = 0.02 * sin( M_PI *i/50)*sin( M_PI *j/50);
        }


}
