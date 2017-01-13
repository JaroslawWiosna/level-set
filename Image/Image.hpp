/**
 * \class Image
 *
 * @par Licence
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */


#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cstdio>
#include <opencv2/opencv.hpp>
class Image {

private:
	cv::Mat inputImage;

	
	//fimage is a 2d array which is a copy of inputImage
	float** fimage;
	float** phi;
	std::size_t rows;
	std::size_t cols;
	float c1;//averageInside;
	float c2;//averageOutside;
	float mi;
	float eta;
	float ni;
	float lambda1;
	float lambda2;
	float eps;
	float dt;
	
	std::size_t steps;
        
        int sub_i;  //substraction from i
        int sub_j;  //substraction from i
        int add_i;  //addition to i
        int add_j;  //addition to j
	
	void initImage(const std::string& filename, int flags);
	void initFimage(); 
	void initPhi(int type = 1);    //default sinus initialization, 2 <- circle
	void destroyFimage();
	void destroyPhi();
	float Heaviside(float data);
	void updateAverages();

public:
	Image(const std::string& filename, int flag=cv::IMREAD_GRAYSCALE);
	Image(std::map<std::string, std::string> flags);
	Image(Image const&) = delete;
	Image(Image const&&) = delete;
	~Image();
	void displayPhi();
	void detectBorders();
	void setMi(float value);
	void setMi(std::string value);
	void setEta(float value);
	void setEta(std::string value);
	void setNi(float value);
	void setNi(std::string value);
	void setLambda1(float value);
	void setLambda1(std::string value);
	void setLambda2(float value);
	void setLambda2(std::string value);
	void setEps(float value);
	void setEps(std::string value);
	void setDt(float value);
	void setDt(std::string value);
	void setSteps(float value);
	void setSteps(std::string value);
        void savePhi();
        void displayPhiOnInputImage(const std::string& filename);

};
			
#endif // IMAGE_HPP
