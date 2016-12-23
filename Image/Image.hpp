#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <stdio.h>
#include <cstdio>
#include <opencv2/opencv.hpp>
class Image {

private:
	cv::Mat image;
	float** fimage;
	float** phi;
	std::size_t rows;

	void initImage(const std::string& filename, int flags);
	void initFimage(); 
	void initPhi();
	void destroyFimage();
	void destroyPhi();
	std::size_t cols;
	float Heaviside(float data);
	std::pair<float, float> Average_c();

public:
	Image(const std::string& filename, int flags);
	~Image();
	void displayPhi();
	void detectBorders();

};
			
#endif // IMAGE_HPP
