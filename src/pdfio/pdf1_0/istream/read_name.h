#pragma once

#include <istream>

#include "pdfio/pdf1_0/name.h"

namespace pdf1_0 = pdfio::pdf1_0;
/*! \brief Reads the Name from the istream*/
std::istream &operator>>(std::istream &istream, pdf1_0::Name &name)
{
	if(istream.peek() != '/')
	{
		istream.setstate(std::ios_base::failbit);
	}
	else
	{
		if(istream.seekg(1, std::ios_base::cur))
		{
			std::string buffer;
			if(istream >> buffer)
			{
				name = buffer;
			}
			else
			{
				if(istream.eof())
				{
					istream.clear();
				}
			}
		}
	}
	return istream;
}