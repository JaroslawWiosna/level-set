#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }

    Mat image;
    image = imread( argv[1], IMREAD_GRAYSCALE );

    vector<vector<Point> > contours;
    vector<Point> contours1;

    //    findContours(image.clone(), contours, CV_RETR_LIST, CHAIN_APPROX_NONE);

    for (std::size_t i = 50; i<=250; ++i)
    {
	Point tmp = Point{50,i};
        contours1.push_back(tmp);
    }
    for (std::size_t i = 50; i<=250; ++i)
    {
	Point tmp = Point{i,250};
        contours1.push_back(tmp);
    }
    for (std::size_t i = 250; i>=50; --i)
    {
	Point tmp = Point{250,i};
        contours1.push_back(tmp);
    }
    for (std::size_t i = 250; i>=50; --i)
    {
	Point tmp = Point{i,50};
        contours1.push_back(tmp);
    }

    contours.push_back(contours1);

    // Draw all contours in green on a black image
    Mat3b rec(image.rows, image.cols, Vec3b(0,0,0));
    drawContours(rec, contours, -1, Scalar(0,255,0), 1);

    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE );

//    imshow("Display Image", image);
//    waitKey(0);

    imshow("Display Image", rec);
    waitKey(0);

    return 0;
}
