/**
 * \class FlagParser
 *
 */

#ifndef FLAGPARSER_HPP
#define FLAGPARSER_HPP

#include <cstdio>
#include <map>
#include <string>
class FlagParser {

private:

public:
	FlagParser(int argc, char* argv[]);
	~FlagParser();
	void parse();
};

#endif // FLAGPARSER_HPP
