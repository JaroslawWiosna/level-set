#include <cstdio>
#include <opencv2/opencv.hpp>
#include <gtest/gtest.h>
#include "Image.hpp"

TEST(Test, basic1)
{
	const std::string& pathToTestImage = "../../test-images/001.jpg";
	//Image image(pathToTestImage, cv::IMREAD_GRAYSCALE );
	//Image image(pathToTestImage ,1);

	ASSERT_TRUE(true);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

