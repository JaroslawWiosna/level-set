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
#include <gtest/gtest.h> //for FRIEND_TEST FIXME: We don't want gtest required as default
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
	
	void initImage(const std::string& filename, int flags);
	void initFimage(); 
	void initPhi();
	void destroyFimage();
	void destroyPhi();
	float Heaviside(float data);
	void updateAverages();

	FRIEND_TEST(Test,basic1); // FIXME
public:
	Image(const std::string& filename, int flags);
	Image(Image const&) = delete;
	Image(Image const&&) = delete;
	~Image();
	void displayPhi();
	void detectBorders();
	void setMi(float value);
	void setEta(float value);
	void setNi(float value);
	void setLambda1(float value);
	void setLambda2(float value);
	void setEps(float value);
	void setDt(float value);

};
			
#endif // IMAGE_HPP
