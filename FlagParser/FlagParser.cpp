#include "FlagParser.hpp"
#include <cstdio>

FlagParser::FlagParser(int argc, char* argv[])
{
	std::vector<std::string> vargv(argv + 1, argv + argc);
	this->parse(vargv);
}

FlagParser::~FlagParser()
{
	//
}

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

