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

void displayPhi(float** phi, int rows, int cols) {
    cv::Mat3b rec(rows, cols, cv::Vec3b(0,0,0));
    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
        {
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

void copyMatIntoFimage(cv::Mat image, float** fimage){
   int rows = image.rows;
   int cols = image.cols;
   for (std::size_t i = 0; i < rows; ++i)
       for (std::size_t j = 0; j < cols; ++j)
       {
           fimage[i][j] = image.at<uchar>(i,j);
       }
}

void detectBorders(float** fimage, float**phi, std::size_t rows, std::size_t cols) {
    bool should_continue = true;
    for (std::size_t step = 0; step < 500 && should_continue; ++step)
    {
	//should_continue = false;
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
            displayPhi(phi, rows, cols);
    }
}

