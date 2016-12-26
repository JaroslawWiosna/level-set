/**
 * \class FlagParser
 *
 * @par Licence
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */


#ifndef FLAGPARSER_HPP
#define FLAGPARSER_HPP

#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <string>
class FlagParser {

private:
	using Flags = std::map<std::string, std::string>;
	Flags flags;
public:
	FlagParser(int argc, char* argv[]);
	~FlagParser();
	void parse(std::vector<std::string> vargv);
	void printFlags();
	std::map<std::string, std::string> getFlags();
};

#endif // FLAGPARSER_HPP
