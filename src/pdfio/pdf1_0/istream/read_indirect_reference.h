#pragma once

#include <istream>

#include "pdfio/pdf1_0/indirect_reference.h"

namespace pdf1_0 = pdfio::pdf1_0;
/*! \brief Reads the indirectReference from the istream*/
inline std::istream &operator>>(std::istream &istream, pdf1_0::IndirectReference &indirectReference)
{
	auto objNumBuffer = indirectReference.objectNumber();
	if(istream >> objNumBuffer)
	{
		auto genNumBuffer = indirectReference.generationNumber();
		if(istream >> genNumBuffer)
		{
			char ch = 0;
			if(istream >> ch)
			{
				if(ch == 'R')
				{
					indirectReference.objectNumber() = objNumBuffer;
					indirectReference.generationNumber() = genNumBuffer;
				}
				else
				{
					istream.setstate(std::ios_base::failbit);
				}
			}
		}
	}
	return istream;
}