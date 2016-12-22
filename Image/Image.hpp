#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <stdio.h>
#include <cstdio>
#include <opencv2/opencv.hpp>
#include "../utils/utils.hpp"

class Image {

private:
	cv::Mat image;
	float** fimage;
	float** phi;
	std::size_t rows;
	std::size_t cols;

public:
	Image(const std::string& filename, int flags);
	~Image();
	void initImage(const std::string& filename, int flags);
	void initFimage(); 
	void initPhi();
	void displayPhi();
	void detectBorders();
	void destroyFimage();
	void destroyPhi();

};
			
#endif // IMAGE_HPP
