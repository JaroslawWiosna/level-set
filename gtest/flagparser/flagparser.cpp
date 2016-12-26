/**
 * @par Licence
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */


#include <cstdio>
#include <opencv2/opencv.hpp>
#include <gtest/gtest.h>
#include "FlagParser.hpp"

TEST(Test, flagparser01)
{
	int argct = 3;
	
	//char * argvt [3];
       	//argvt[0] = "level-set";
	//argvt[1] = "-i";
	//argvt[2] = "my/path/to/file.jpg";

	char * argvt [] = {"level-set", "-i", "my/path/to/file.jpg"};

	FlagParser parser(argct, argvt);

	//parser.printFlags();
	
	auto flags = parser.getFlags();

	ASSERT_EQ(flags["-i"], "my/path/to/file.jpg");
	ASSERT_TRUE(true);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

