/**
 * \class ExperimImage
 *
 * @par Licence
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */


#include "ExperimImage.hpp"

/**
 * Constructor
 *
 * @param [in] filename - path to the image
 * @param [in] flag - default value is equal to cv::IMREAD_GRAYSCALE
 */
#if 0
ExperimImage::ExperimImage(const std::string& filename)
{
/*	initImage(filename, 1);
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
	dt = 0.5; // timestep*/
}
#endif
ExperimImage::~ExperimImage()
{
	destroyFimage();
	destroyPhi();
}

void ExperimImage::initImage(const std::string& filename, int flags=1)
{
	inputImage = cv::imread(filename, flags);
}
/*
void ExperimImage::savePhi()
{    
	// TODO:
}

void ExprerimImage::displayPhiOnInputImage(const std::string& filename)
{
	// TODO:
}
*/
