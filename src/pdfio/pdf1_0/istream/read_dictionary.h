#pragma once

#include <iostream>

#include "pdfio/pdf1_0/dictionary.h"
#include "read_name.h"
#include "read_integer.h"
#include "read_indirect_reference.h"

namespace pdf1_0 = pdfio::pdf1_0;
/*! \brief Reads the dictionary from the istream*/
inline std::istream &operator>>(std::istream &istream, pdf1_0::Dictionary &dictionary)
{
	std::string buffer;
	if(istream >> buffer)
	{
		if(buffer == "<<")
		{
			auto streamPosition = istream.tellg();
			pdf1_0::Dictionary tmp;
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
						case pdf1_0::GenericObject::TypeId::kName:
							{
								pdf1_0::Name value;
								if(!(istream >> value))
								{
									std::cerr << __PRETTY_FUNCTION__ << ":failed to read name value\n" ;
								}
								else
								{
									tmp.insert(name, value);
								}
							}
							break;
						case pdf1_0::GenericObject::TypeId::kInteger:
							{
								pdf1_0::Integer value;
								if(!(istream >> value))
								{
									std::cerr << __PRETTY_FUNCTION__ << ":failed to integer name value\n" ;
								}
								else
								{
									tmp.insert(name, value);
								}
							}
							break;
						case pdf1_0::GenericObject::TypeId::kIndirectReference:
							{
								pdf1_0::IndirectReference value;
								if(!(istream >> value))
								{
									std::cerr << __PRETTY_FUNCTION__ << ":failed to indirect reference name value\n" ;
								}
								else
								{
									tmp.insert(name, value);
								}
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
					else
					{
						dictionary.swap(tmp);
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