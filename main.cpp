#include <cstdio>
#include <opencv2/opencv.hpp>
#include "Image.hpp"
#include "FlagParser.hpp"

int main(int argc, char** argv )
{
    FlagParser parser(argc, argv);
    parser.printFlags();
    auto flags = parser.getFlags();

    Image image(flags["-i"], cv::IMREAD_GRAYSCALE );

    image.displayPhi();
    image.detectBorders();
    image.displayPhi();
    return 0;
}
