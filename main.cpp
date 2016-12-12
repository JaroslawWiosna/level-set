#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <math.h>

//using namespace cv;

float Heaviside(float data)
{
	return ((data >= 0) ? 1 : 0);
}

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }

    cv::Mat image;
    image = imread( argv[1], cv::IMREAD_GRAYSCALE );

    int rows = image.rows;
    int cols = image.cols;

    float** phi = new float*[rows];
    for(int i = 0; i < rows; ++i)
        phi[i] = new float[cols];

    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
        {
            phi[i][j] = 50 - sqrt( (200-i)*(200-i) + (150-j)*(150-j) );
	}



    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", cv::WINDOW_AUTOSIZE );

//    cv::imshow("Display Image", rec);
    cv::waitKey(0);

    return 0;
}
