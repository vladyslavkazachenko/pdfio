#include "read_indirect_object.h"

#include "read_integer.h"
#include "pdfio/read_generic_object.h"

namespace pdf1_0 = pdfio::pdf1_0;

std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::IndirectObject &indirectObject)
{
	if(istream >> indirectObject.objectNumber())
	{
		if(istream >> indirectObject.generationNumber())
		{
			std::string buffer;
			if(istream >> buffer)
			{
				if(buffer == "obj")
				{
					if(istream >> indirectObject.get())
					{
						if(istream >> buffer)
						{
							if(buffer != "endobj")
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
		}
	}
	return istream;
}