#include <cstdio>
#include <opencv2/opencv.hpp>
#include "Image/Image.hpp"
#include "utils/utils.hpp"

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: level-set <Image_Path>\n");
        return -1;
    }


    Image image(argv[1], cv::IMREAD_GRAYSCALE );

    image.displayPhi();
    image.detectBorders();
    image.displayPhi();
    return 0;
}
