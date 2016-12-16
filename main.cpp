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
    
    //printf("\r\n%d\t%d\r\n",rows,cols);

    float** fimage = new float*[rows];
    for(int i = 0; i < rows; ++i)
        fimage[i] = new float[cols];

    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
        {
            fimage[i][j] = image.at<uchar>(i,j);
	}


    float** phi = new float*[rows];
    for(int i = 0; i < rows; ++i)
        phi[i] = new float[cols];

    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
        {
            phi[i][j] = 50 - sqrt( (rows/2-i)*(rows/2-i) + (cols/2-j)*(cols/2-j) ); //Middle point of a circle depends on image size 
	    //phi[i][j] = Heaviside(phi[i][j]);
	}


    for (std::size_t step = 0; step < 10; ++step)
        for (std::size_t i = 1; i < rows-1; ++i)
            for (std::size_t j = 1; j < cols-1; ++j)
            {
	        float mi = 0.00001;
		float eta = 0.0001;
		float ni = 0.0001;
		float lambda1 = 0.0001;
		float lambda2 = 0.0001;
		float eps = 0.0001;
		float c1 = 0.0001;
		float c2 = 0.0001;
	        //float A = mi / (sqrt( pow(eta,2) + pow((phi[i+1][j] - phi[i][j]),2)  + pow((phi[i][j+1] - phi[i][j-1])/2.0,2) ));
	        float B = mi / (sqrt( pow(eta,2) + pow((phi[i+1][j] - phi[i-1][j]/2.0),2)  + pow((phi[i][j] - phi[i+1][j])/2.0,2) ));
		// TODO: change A to lambda expr
                
                auto A = [](int i, int j, float ** phi, float & mi, float & eta)->float { return mi / (sqrt( pow(eta,2) + pow((phi[i+1][j] - phi[i][j]),2)  + pow((phi[i][j+1] - phi[i][j-1])/2.0,2) ));};
                
	        phi[i][j] = (phi[i][j] + (eps/ (3.1415 * (pow(eps,2) + pow(phi[i][j],2)))) * A(i,j,phi,mi,eta)* phi[i+1][j] + A(i,j,phi,mi,eta)*phi[i-1][j] + B*phi[i][j+1] + B*phi[i][j-1] - ni - lambda1*pow(fimage[i][j] - c1,2)   - lambda2*pow(fimage[i][j] - c2,2) ) / ( 1 + (eps/ (3.1415 * (pow(eps,2) + pow(phi[i][j],2)))) * (A(i,j,phi,mi,eta) + A(i,j,phi,mi,eta) + B + B)  ) ;
	    }

    


//    cv::Mat matphi = static_cast<cv::Point>(phi);
    cv::Mat3b rec(image.rows, image.cols, cv::Vec3b(0,0,0));
    rec[200][100] = cv::Vec3b(0,255,0);
    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
        {
	    if(std::abs(phi[i][j]) < 0.1)
                rec[i][j] = cv::Vec3b(0,255,0);
	}


    

    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", cv::WINDOW_AUTOSIZE );

    cv::imshow("Display Image", rec);
    cv::waitKey(0);

    return 0;
}
