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
    vector<Point> contours2;

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
/*
    for (std::size_t i = 100; i<=200; ++i)
    {
	Point tmp = Point{100,i};
        contours2.push_back(tmp);
    }
    
    printf("wartosc: %d",image.at<uchar>(200,150));
    for (std::size_t i = 100; i<=200; ++i)
    {
	Point tmp = Point{i,200};
        contours2.push_back(tmp);
    }
    for (std::size_t i = 200; i>=100; --i)
    {
	Point tmp = Point{200,i};
        contours2.push_back(tmp);
    }
    for (std::size_t i = 200; i>=100; --i)
    {
	Point tmp = Point{i,100};
        contours2.push_back(tmp);
    }
    
    contours.push_back(contours2);
  */

    int esc = 200;//contours1.size();
    int pos_x = 0, pos_y = 0;
    while(esc)
    {
        for(int i = 0; i < contours1.size(); i++)
        {
            pos_x = contours1[i].x;
            pos_y = contours1[i].y;
            if (image.at<uchar>(contours1[i].x,contours1[i].y) == 255)
            {
                if (contours1[i].x <= 150)
                    pos_x +=1;//contours1[i].x += 1;
                if (contours1[i].x > 150)
                    pos_x -=1;//contours1[i].x -= 1;
                if (contours1[i].y <= 150)
                    pos_y +=1;//contours1[i].y += 1;
                if (contours1[i].y > 150)
                    pos_y -=1;//contours1[i].y -= 1;
                contours1[i] = Point{pos_x,pos_y};
            }
        }
        esc--;
    }
    contours.push_back(contours1);
    printf("size: %d\r\n",contours1.size());
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

    Mat Dx;
    Sobel(image, Dx, CV_64F, 1, 0, 3);

    Mat Dy;
    Sobel(image, Dy, CV_64F, 0, 1, 3);

    imshow("Display Image", Dx);
    waitKey(0);
    return 0;
}
