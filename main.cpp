#include <cstdio>
#include <opencv2/opencv.hpp>
#include "utils/utils.hpp"

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
    
    //printf("\r\n%d\t%d\r\n",rows,cols);

    float** fimage = new float*[rows];
    for(int i = 0; i < rows; ++i)
        fimage[i] = new float[cols];

    copyMatIntoFimage(image, fimage);

    float** phi = new float*[rows];
    for(int i = 0; i < rows; ++i)
        phi[i] = new float[cols];

    initializePhi(phi, rows, cols);

    detectBorders(fimage, phi, rows, cols);

    for(int i = 0; i < rows; ++i)
    {
      delete [] phi[i];
      delete [] fimage[i];
    }


    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    return 0;
}
