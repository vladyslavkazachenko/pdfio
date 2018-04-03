#include "read_dictionary.h"

#include <iostream>

#include "read_name.h"
#include "pdfio/pdf1_0/generic_object_type.h"
#include "read_generic_object.h"

namespace pdf1_0 = pdfio::pdf1_0;

std::istream &operator>>(std::istream &istream, pdf1_0::Dictionary &dictionary)
{
	std::string buffer;
	while(istream && std::isspace(istream.peek()))
	{
		static_cast<void>(istream.get());
	}
	if(istream)
	{
		char tmp[3] = {0, 0, 0};
		if(istream.read(tmp, 2))
		{
			buffer = tmp;
		}
	}
	if(istream)
	{std::cerr << "aaaaaaaaaaaa1\n";
		if(buffer == "<<")
		{std::cerr << "aaaaaaaaaaaa2\n";
			auto streamPosition = istream.tellg();
			std::set<pdf1_0::Name> keys = dictionary.keys();
			while(istream)
			{std::cerr << "aaaaaaaaaaaax\n";
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
						else
						{
							std::cerr << "failed to read " << std::string(name) << "\n";
						}
					}
					else
					{
						std::cerr << __PRETTY_FUNCTION__ << ":unknown name " << std::string(name) << "\n" ;
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