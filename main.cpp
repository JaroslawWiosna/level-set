/**
 * @par Licence
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */


#include <cstdio>
#include <opencv2/opencv.hpp>
#include "Image.hpp"
#include "FlagParser.hpp"

int main(int argc, char** argv )
{
    FlagParser parser(argc, argv);
    parser.printFlags();
    auto flags = parser.getFlags();

    Image image(flags["-i"], cv::IMREAD_GRAYSCALE );

    image.displayPhi();
    image.detectBorders();
    image.displayPhi();
    image.displayPhioninputImage(flags["-i"]);
    image.savePhi();
    return 0;
}
