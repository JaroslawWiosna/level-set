/**
 * \class Image
 *
 * @par Licence
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */


#include "Image.hpp"
#include <cstdio>
#include <opencv2/opencv.hpp>

/**
 * Constructor
 *
 * @param [in] filename - path to the image
 * @param [in] flag - default value is equal to cv::IMREAD_GRAYSCALE
 */
Image::Image(const std::string& filename, int flag)
{
	initImage(filename, flag);
	rows = inputImage.rows;
	cols = inputImage.cols;

	initFimage();
	initPhi();

	//default values
	mi = 0.2;
	eta = 0.00000001;
	ni = FLT_MIN;
	lambda1 = 1;
	lambda2 = 1;
	eps = 1;
	dt = 0.5; // timestep
	steps = 2;
}

/**
 * Constructor
 *
 * @param [in] TODO:
 */
Image::Image(std::map<std::string, std::string> flags)
{
	initImage(flags["-i"], cv::IMREAD_GRAYSCALE);
	rows = inputImage.rows;
	cols = inputImage.cols;

	initFimage();
	initPhi();

	//default values
	mi = 0.2;
	eta = 0.00000001;
	ni = FLT_MIN;
	lambda1 = 1;
	lambda2 = 1;
	eps = 1;
	dt = 0.5; // timestep
	steps = 2;

	if (!flags["-mi"].empty())
		setMi(flags["-mi"]);
 	if (!flags["-eta"].empty())
 		setEta(flags["-eta"]);
 	if (!flags["-ni"].empty())
 		setNi(flags["-ni"]);
 	if (!flags["-lambda1"].empty())
		setLambda1(flags["-lambda1"]);
	if (!flags["-lambda2"].empty())
 		setLambda2(flags["-lambda2"]);
	if (!flags["-lambda"].empty())
	{
		setLambda1(flags["-lambda"]);
		setLambda2(flags["-lambda"]);
	}
	if (!flags["-eps"].empty())
		setEps(flags["-eps"]);
	if (!flags["-dt"].empty())
		setDt(flags["-dt"]);
 
	if (!flags["-steps"].empty())
		setSteps(flags["-steps"]);
 
}

Image::~Image()
{
	destroyFimage();
	destroyPhi();
}

void Image::initImage(const std::string& filename, int flags=1)
{
	inputImage = cv::imread(filename, flags);
}

void Image::initFimage() 
{
	fimage = new float*[rows];
	for(int i = 0; i < rows; ++i)
		fimage[i] = new float[cols];

	for (std::size_t i = 0; i < rows; ++i)
		for (std::size_t j = 0; j < cols; ++j)
		{
			fimage[i][j] = inputImage.at<uchar>(i,j);
		}
}

void Image::initPhi(int type)
{
	phi= new float*[rows];
	for(int i = 0; i < rows; ++i)
      		phi[i] = new float[cols];
		
	for (std::size_t i = 0; i < rows; ++i)
       		for (std::size_t j = 0; j < cols; ++j)
       		{
                    if (type == 1)
                        phi[i][j] = sin( M_PI *i/5)*sin( M_PI *j/5);
                    if (type == 2)
        		phi[i][j] = 100 - sqrt( (rows/2-i)*(rows/2-i) + (cols/2-j)*(cols/2-j) ); 
			//Middle point of a circle depends on image size 
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

void Image::displayPhi() 
{
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
void Image::detectBorders()
{
        
	bool should_continue = true;
	for (std::size_t step = 0; step < steps && should_continue; ++step)
   		{
		//should_continue = false;
		updateAverages();

		//auto c = Average_c();
		//auto c1 = c.first;
		//auto c2 = c.second;

		std::cout << "c1=" << c1 << " c2=" << c2 << std::endl;

		for (std::size_t i = 0; i < rows; ++i)
			for (std::size_t j = 0; j < cols; ++j)
			{
               
                sub_i = 0;
                sub_j = 0;
                add_i = 0;
                add_j = 0;
                
                if (i == 0)
                    add_i++;
                if (j == 0)
                    add_j++;
                if (i == rows-1)
                    sub_i++;
                if (i == cols-1)
                    sub_j++;
                
               auto A = 
                   [&](int i, int j, float ** phi, float & mi, float & eta)
	    -> float { 
                       return mi / (sqrt( pow(eta,2) 
		    + pow((phi[i-sub_i+1][j] - phi[i][j]),2) 
		    + pow((phi[i][j-sub_j+1] - phi[i][j+add_j-1])/2.0,2) ));
	    };
               auto B = 
                   [&](int i, int j, float ** phi, float & mi, float & eta)
	    -> float {
                       return mi / (sqrt( pow(eta,2) 
                           + pow((phi[i-sub_i+1][j] - phi[i+add_i-1][j]/2.0),2) 
		    + pow((phi[i][j] - phi[i-sub_i+1][j])/2.0,2) ));
	    };
               
	auto old_value = phi[i][j];
	        phi[i][j] = 
                   ( phi[i][j] 
	        + dt * (eps/( M_PI * (pow(eps,2) + pow(phi[i][j],2))))
	        * A(i,j,phi,mi,eta) *  phi[i-sub_i+1][j] 
		+ A(i+add_i-1,j,phi,mi,eta) * phi[i+add_i-1][j] 
		+ B(i,j,phi,mi,eta) * phi[i][j-sub_j+1] 
		+ B(i,j+add_j-1,phi,mi,eta) * phi[i][j+add_j-1] 
		- ni 
		- lambda1 * pow(fimage[i][j] - c1,2) 
		- lambda2*pow(fimage[i][j] - c2,2) )
                   / 
                   ( 1 + dt 
	        * (eps / ( M_PI * ( pow(eps,2) + pow( phi[i][j],2) ))) 
	        * (A(i,j,phi,mi,eta) + A(i+add_i-1,j,phi,mi,eta) 
                       + B(i,j,phi,mi,eta) + B(i,j+add_j-1,phi,mi,eta))  ) ;
                if ( phi[i][j] - old_value > 0.0000001 ) 
               {
	        should_continue = true;
        }
    }
		displayPhi();
		//displayPhioninputImage("../test-images/008.jpg");
   		}
}

void Image::destroyFimage()
{
	for(int i = 0; i < rows; ++i)
	{
		delete [] fimage[i];
		fimage[i] = nullptr;
	}
}
void Image::destroyPhi()
{
	for(int i = 0; i < rows; ++i)
	{
		delete [] phi[i];
		phi[i] = nullptr;
	}
}

float Image::Heaviside(float data)
{
	return ((data >= 0) ? 1 : 0);
}

void Image::updateAverages()
{
    float sum_inside{}; // inside or on border
    float sum_outside{};
    int pixnum_inside{}; //number of pixels inside circle
    int pixnum_outside{}; //number of pixels outside circle
    for (std::size_t i = 1; i < rows-1; ++i)
        for (std::size_t j = 1; j < cols-1; ++j)
        {
            if (phi[i][j] >= 0)   //if phi > 0 ==> pixel inside circle
            {
                sum_inside += fimage[i][j];
                pixnum_inside++;
            }
            else if (phi[i][j] < 0)   //if phi < 0 ==> pixel outside circle
            {
                sum_outside += fimage[i][j];
                pixnum_outside++;
            }
        }

    std::cout << "sum_inside=" << sum_inside << std::endl;
    std::cout << "sum_outside=" << sum_outside << std::endl;

    std::cout << "pix_inside=" << pixnum_inside << std::endl;
    std::cout << "pix_outside=" << pixnum_outside << std::endl;

    c1 = sum_inside  / static_cast<float>(pixnum_inside);
    c2 = sum_outside / static_cast<float>(pixnum_outside);
}

void Image::setMi(float value)
{
	mi = value;
}

void Image::setMi(std::string value)
{
	mi = std::stof(value);
}

void Image::setEta(float value)
{
	eta = value;
}

void Image::setEta(std::string value)
{
	eta = std::stof(value);
}

void Image::setNi(float value)
{
	ni = value;
}

void Image::setNi(std::string value)
{
	ni = std::stof(value);
}

void Image::setLambda1(float value)
{
	lambda1 = value;
}

void Image::setLambda1(std::string value)
{
	lambda1 = std::stof(value);
}

void Image::setLambda2(float value)
{
	lambda2 = value;
}

void Image::setLambda2(std::string value)
{
	lambda2 = std::stof(value);
}

void Image::setEps(float value)
{
	eps = value;
}

void Image::setEps(std::string value)
{
	eps = std::stof(value);
}

void Image::setDt(float value)
{
	dt = value;
}

void Image::setDt(std::string value)
{
	dt = std::stof(value);
}

void Image::setSteps(float value)
{
	steps = value;
}

void Image::setSteps(std::string value)
{
	steps = std::stof(value);
}

void Image::savePhi()
{    
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
    cv::imwrite("phi.jpg",rec);
}

void Image::displayPhiOnInputImage(const std::string& filename)
{
    cv::Mat phiOnImage = cv::imread(filename, cv::IMREAD_COLOR);
    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
        {
            if(std::abs(phi[i][j]) < 100)
               			phiOnImage.at<cv::Vec3b>(i,j)[1] = 105;
           		if(std::abs(phi[i][j]) < 10)
        	       		phiOnImage.at<cv::Vec3b>(i,j)[1] = 155;
			if(std::abs(phi[i][j]) < 1)
				phiOnImage.at<cv::Vec3b>(i,j)[1] = 205;
			if(std::abs(phi[i][j]) < 0.1)
				phiOnImage.at<cv::Vec3b>(i,j)[1] = 255;
        }
    
    cv::imshow("Phi on inputImage",phiOnImage);
    cv::waitKey(0);
}
