#pragma once

#include <iostream>

#include "pdfio/pdf1_0/file_header.h"
#include "read_dictionary.h"

namespace pdf1_0 = pdfio::pdf1_0;
/*! \brief Reads the fileHeader from the istream*/
inline std::istream &operator>>(std::istream &istream, pdf1_0::FileHeader &fileHeader)
{
	std::string buffer;
	if(istream >> buffer)
	{
		if(buffer != "%PDF-1.0")
		{
			istream.setstate(std::ios_base::failbit);
		}
	}
	return istream;
}