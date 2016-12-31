/**
 * \class FlagParser
 *
 * @par Licence
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */


#include "FlagParser.hpp"
#include <cstdio>

/*
 * Constructor
 */
FlagParser::FlagParser(int argc, char* argv[])
{
	std::vector<std::string> vargv(argv + 1, argv + argc);
	this->parse(vargv);
}

FlagParser::~FlagParser()
{
	//
}

/**
 * @brief parsing method
 *
 * @param vector of strings, which should be a argv, but instead of char**
 *  type, param is a vector of strings, as written earier
 *
 * Takes an argument which is argv as a vector of strings
 * As a result 'flags' field (of type map of two strings) is set as 
 * a vector of pair of flag and value.
 *
 * Basicly, method iterates through all strings in vargv. If 'flag' is 
 * found (and by flag I mean the string begins with "-" sign 
 * (ASCII 46 (0x2E)) then:
 * if the flag is the last one in vargv, the value is set to an empty string.
 * If not, the next string (if only does not begin with "-" sign)
 * is assumed to be the value of the flag. 
 * 
 * @return none
 */ 
void FlagParser::parse(std::vector<std::string> vargv)
{
	const std::string prefix = "-";
	for(std::vector<std::string>::iterator it = vargv.begin();
		       it != vargv.end(); 
		       ++it)
	{
		//std::cout << "it=" << *it << std::endl;
		if(it->substr(0, prefix.size()) == prefix)
		{
			//
			if (it == vargv.end()-1)
			{
				//std::cout << "endit=" << *it << std::endl;
				flags[*it] = "";
				break;
			}

			auto next = std::next(it, 1);
			//std::cout << "it=" << *it;
			//std::cout << " next=" << *next << std::endl;
			
			if(next->substr(0, prefix.size()) != prefix)
			{
				flags[*it] = *next;
			}
			else 
			{
				flags[*it] = "";
			}
		}
	}	
}

void FlagParser::printFlags()
{
	std::cout << "printFlags" << std::endl;
	for (auto& i : flags)
	{
		std::cout 
			<< i.first << " " 
			<< i.second << "\n";
	}
}

std::map<std::string, std::string> FlagParser::getFlags()
{
	return flags;
}


