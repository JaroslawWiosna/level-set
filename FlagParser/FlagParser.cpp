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

/*
 * parsing method
 *
 * Takes an argument which is argv as a vector of strings
 * As a result 'flags' field of type map of two strings is set as 
 * a vector of pair of flag and value.
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
			if (it == vargv.end())
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


