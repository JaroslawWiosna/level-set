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
	int argct = 4;
	const char * argvt [] = {"level-set", "-i", "my/path/to/file.jpg"};
	FlagParser parser(argct, const_cast<char**>(argvt));

	parser.printFlags();
	
	auto flags = parser.getFlags();

	ASSERT_EQ(flags["-i"], "my/path/to/file.jpg");
}

TEST(Test, flagparser02)
{
	int argct = 4;
	const char * argvt [] = {"level-set", "-i", "my/path/to/file.jpg"};
	FlagParser parser(argct, const_cast<char**>(argvt));

	parser.printFlags();
	
	auto flags = parser.getFlags();

	ASSERT_EQ(flags["-i"], "my/path/to/file.jpg");
}

TEST(Test, flagparser03)
{
	int argct = 6;
	const char * argvt [] = {"level-set", "-i", "my/path/to/file.jpg", "-qqq", "1959"};
	FlagParser parser(argct, const_cast<char**>(argvt));

	parser.printFlags();
	
	auto flags = parser.getFlags();

	ASSERT_EQ(flags["-i"], "my/path/to/file.jpg");
	ASSERT_EQ(flags["-qqq"], "1959");
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

