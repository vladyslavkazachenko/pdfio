#include "read_name.h"

namespace pdf1_0 = pdfio::pdf1_0;

std::istream &operator>>(std::istream &istream, pdf1_0::Name &name)
{
	char slash = 0;
	if(istream >> slash)
	{
		if(slash != '/')
		{
			istream.setstate(std::ios_base::failbit);
		}
		else
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