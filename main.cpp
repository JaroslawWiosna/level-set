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

    Image image(flags["-i"]);

    if (!flags["-mi"].empty())
        image.setMi(flags["-mi"]);
    if (!flags["-eta"].empty())
        image.setEta(flags["-eta"]);
    if (!flags["-ni"].empty())
        image.setNi(flags["-ni"]);
    if (!flags["-lambda1"].empty())
        image.setLambda1(flags["-lambda1"]);
    if (!flags["-lambda2"].empty())
        image.setLambda2(flags["-lambda2"]);
    if (!flags["-lambda"].empty())
    {
        image.setLambda1(flags["-lambda"]);
        image.setLambda2(flags["-lambda"]);
    }
    if (!flags["-eps"].empty())
        image.setEps(flags["-eps"]);
    if (!flags["-dt"].empty())
        image.setDt(flags["-dt"]);
    

    image.displayPhi();
    image.detectBorders();
    image.displayPhi();
    image.displayPhiOnInputImage(flags["-i"]);
    image.savePhi();
    return 0;
}
