/**
 * \class ExperimImage
 *
 * @par Licence
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */


#ifndef EXPERIMIMAGE_HPP
#define EXPERIMIMAGE_HPP

#include <cstdio>
#include <jpeglib.h>
#include "../Image/Image.hpp"

class ExperimImage : public Image {
private:
	void initImage(const std::string& filename, int flags);
public:
	ExperimImage(const std::string& filename) : Image(filename,1) 
	{
		
	}
	ExperimImage(Image const&) = delete;
	ExperimImage(Image const&&) = delete;
	~ExperimImage();
//        void savePhi();
//        void displayPhiOnInputImage(const std::string& filename);
};
			
#endif // EXPRERIMIMAGE_HPP
