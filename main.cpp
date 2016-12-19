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
            //phi[i][j] = 100 - sqrt( (rows/2-i)*(rows/2-i) + (cols/2-j)*(cols/2-j) ); //Middle point of a circle depends on image size 
	    //phi[i][j] = Heaviside(phi[i][j]);
            /*
            if (100 - sqrt( (rows/2-i)*(rows/2-i) + (cols/2-j)*(cols/2-j) ) >= 0)
                phi[i][j] = 1;
            else
                phi[i][j] = -1;
		*/
            phi[i][j] = 0.02 * sin( M_PI *i/50)*sin( M_PI *j/50);
	}

    bool should_continue = true;
    for (std::size_t step = 0; step < 500 && should_continue; ++step)
    {
	should_continue = false;
        auto c = Average_c(phi, fimage, rows, cols);
	auto c1 = c.first;
	auto c2 = c.second;
        for (std::size_t i = 1; i < rows-1; ++i)
            for (std::size_t j = 1; j < cols-1; ++j)
            {
	        float mi = 0.2;
		float eta = 0.00000001;
		float ni = 0;//0.00000001;
		float lambda1 = 0.300002;
		float lambda2 = 0.300002;
		float eps = 1000;
		float dt = 0.001; // timestep
		
                auto A = 
                    [](int i, int j, float ** phi, float & mi, float & eta)
		    -> float { 
                        return mi / (sqrt( pow(eta,2) 
			    + pow((phi[i+1][j] - phi[i][j]),2) 
			    + pow((phi[i][j+1] - phi[i][j-1])/2.0,2) ));
		    };
                auto B = 
                    [](int i, int j, float ** phi, float & mi, float & eta)
		    -> float { 
                        return mi / (sqrt( pow(eta,2) 
                            + pow((phi[i+1][j] - phi[i-1][j]/2.0),2) 
			    + pow((phi[i][j] - phi[i+1][j])/2.0,2) ));
		    };
                
		auto old_value = phi[i][j];

	        phi[i][j] = 
                    ( phi[i][j] 
		        + dt * (eps/( M_PI * (pow(eps,2) + pow(phi[i][j],2))))
		        * A(i,j,phi,mi,eta) *  phi[i+1][j] 
			+ A(i-1,j,phi,mi,eta) * phi[i-1][j] 
			+ B(i,j,phi,mi,eta) * phi[i][j+1] 
			+ B(i,j-1,phi,mi,eta) * phi[i][j-1] 
			- ni 
			- lambda1 * pow(fimage[i][j] - c1,2) 
			- lambda2*pow(fimage[i][j] - c2,2) )
                    / 
                    ( 1 + dt 
		        * (eps / ( M_PI * ( pow(eps,2) + pow( phi[i][j],2) ))) 
		        * (A(i,j,phi,mi,eta) + A(i-1,j,phi,mi,eta) 
                        + B(i,j,phi,mi,eta) + B(i,j-1,phi,mi,eta))  ) ;

                if ( phi[i][j] - old_value > 0.0000001 ) 
                {
		        should_continue = true;
	        }
	    }
	    cv::Mat3b rec(image.rows, image.cols, cv::Vec3b(0,0,0));
            for (std::size_t i = 0; i < rows; ++i)
                for (std::size_t j = 0; j < cols; ++j)
                {
//                    if(phi[i][j] < 0)
//                        rec[i][j] = cv::Vec3b(0,0,155);
//                    if(phi[i][j] > 0)
//                        rec[i][j] = cv::Vec3b(155,0,0);
                    if(std::abs(phi[i][j]) < 100)
                        rec[i][j] = cv::Vec3b(0,105,0);
                    if(std::abs(phi[i][j]) < 10)
                        rec[i][j] = cv::Vec3b(0,155,0);
                    if(std::abs(phi[i][j]) < 1)
                        rec[i][j] = cv::Vec3b(0,205,0);
                    if(std::abs(phi[i][j]) < 0.1)
                        rec[i][j] = cv::Vec3b(0,255,0);
                }
                cv::imshow("Display Image", rec);
                cv::waitKey(0);
    }

    cv::Mat3b rec(image.rows, image.cols, cv::Vec3b(0,0,0));
    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
        {
	    if(std::abs(phi[i][j]) < 1)
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
