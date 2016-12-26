/**
 * \class FlagParser
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
