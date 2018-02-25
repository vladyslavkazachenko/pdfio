#pragma once

#include <istream>

#include "pdfio/pdf1_0/array.h"
#include "pdfio/pdf1_0/istream/read_indirect_reference.h"

/*! \brief Reads the array from the istream*/
template <typename T>
inline std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::Array<T> &array)
{
	std::string buffer;
	if(istream >> buffer)
	{
		if(buffer == "[")
		{
			std::vector<T> elements;
			auto streamPos = istream.tellg();
			while(istream)
			{
				T tmp;
				if(istream >> tmp)
				{
					elements.push_back(tmp);
					streamPos = istream.tellg();
				}
			}
			istream.clear();
			if(istream.seekg(streamPos))
			{
				if(istream >> buffer)
				{
					if(buffer == "]")
					{
						array.resize(elements.size());
						for(std::size_t i = 0; i < elements.size(); ++i)
						{
							array[i] = elements[i];
						}
					}
					else
					{
						istream.setstate(std::ios_base::failbit);
					}
				}
			}
		}
		else
		{
			istream.setstate(std::ios_base::failbit);
		}
	}
	return istream;
}