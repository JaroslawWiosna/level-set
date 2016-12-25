#include <cstdio>
#include <opencv2/opencv.hpp>
#include "Image.hpp"
#include "FlagParser.hpp"

int main(int argc, char** argv )
{
    FlagParser parser(argc, argv);
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
