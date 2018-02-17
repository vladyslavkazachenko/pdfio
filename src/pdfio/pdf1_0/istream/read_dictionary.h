#pragma once

#include <iostream>

#include "pdfio/pdf1_0/dictionary.h"
#include "read_name.h"
#include "read_integer.h"
#include "read_indirect_reference.h"

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
			while(istream)
			{
				streamPosition = istream.tellg();
				pdf1_0::Name name;
				if(istream >> name)
				{
					if(dictionary.contains(name))
					{
						switch(dictionary.valueTypeId(name))
						{
						case pdf1_0::TypeId::kName:
							if(!(istream >> dictionary.get<pdf1_0::Name>(name)))
							{
								std::cerr << __PRETTY_FUNCTION__ << ":failed to read name value\n" ;
							}
							break;
						case pdf1_0::TypeId::kInteger:
							if(!(istream >> dictionary.get<pdf1_0::Integer>(name)))
							{
								std::cerr << __PRETTY_FUNCTION__ << ":failed to read integer value\n" ;
							}
							break;
						case pdf1_0::TypeId::kIndirectReference:
							if(!(istream >> dictionary.get<pdf1_0::IndirectReference>(name)))
							{
								std::cerr << __PRETTY_FUNCTION__ << ":failed to read indirect reference value\n" ;
							}
							break;
						default:
							break;
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