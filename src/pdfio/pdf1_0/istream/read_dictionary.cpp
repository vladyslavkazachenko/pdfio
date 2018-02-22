#include "read_dictionary.h"

#include <iostream>

#include "read_generic_object.h"

namespace pdf1_0 = pdfio::pdf1_0;
/*! \brief Reads the dictionary from the istream*/
std::istream &operator>>(std::istream &istream, pdf1_0::Dictionary &dictionary)
{
	std::string buffer;
	if(istream >> buffer)
	{
		if(buffer == "<<")
		{
			auto streamPosition = istream.tellg();
			std::set<pdf1_0::Name> keys = dictionary.keys();
			while(istream)
			{
				streamPosition = istream.tellg();
				pdf1_0::Name name;
				if(istream >> name)
				{
					if(dictionary.contains(name))
					{
						if(istream >> dictionary.get(name))
						{
							keys.erase(name);
							streamPosition = istream.tellg();
						}
					}
					else
					{
						std::cerr << __PRETTY_FUNCTION__ << ":unknown name\n" ;
						istream.setstate(std::ios_base::failbit);
					}
				}
				else
				{
					std::cerr << __PRETTY_FUNCTION__ << ":failed to read key\n";
				}
			}
			istream.clear();
			if(istream.seekg(streamPosition))
			{
				if(istream >> buffer)
				{
					if(buffer != ">>")
					{
						std::cerr << __PRETTY_FUNCTION__ << ":failed to read second delimiter\n";
						istream.setstate(std::ios_base::failbit);
					}
					else
					{
						for(auto key : keys)
						{
							dictionary.remove(key);
						}
					}
				}
			}
		}
		else
		{
			std::cerr << __PRETTY_FUNCTION__ << ":invalid first delimiter\n";
			istream.setstate(std::ios_base::failbit);
		}
	}
	else
	{
		std::cerr << __PRETTY_FUNCTION__ << ":failed to read first delimiter\n";
	}
	return istream;
}