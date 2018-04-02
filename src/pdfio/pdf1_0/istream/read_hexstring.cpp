#include "read_hexstring.h"

namespace pdf1_0 = pdfio::pdf1_0;

std::istream &operator>>(std::istream &istream, pdf1_0::HexString &hexstring)
{
	std::string s;
	if(istream >> s)
	{
		if(s == "<")
		{
			if(istream >> s)
			{
				hexstring = s;
				if(istream >> s)
				{
					if(s != ">")
					{
						istream.setstate(std::ios_base::failbit);
					}
				}
				else
				{
					istream.setstate(std::ios_base::failbit);
				}
			}
			else
			{
				istream.setstate(std::ios_base::failbit);
			}
		}
		else
		{
			istream.setstate(std::ios_base::failbit);
		}
	}
	return istream;
}