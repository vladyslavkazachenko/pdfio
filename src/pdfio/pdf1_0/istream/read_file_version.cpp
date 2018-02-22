#include "read_file_version.h"

#include "read_file_xref.h"
#include "read_file_trailer.h"

namespace pdf1_0 = pdfio::pdf1_0;

std::istream &operator>>(std::istream &istream, pdf1_0::FileVersion &fileVersion)
{
	fileVersion.beginOffset() = istream.tellg();
	if(istream >> fileVersion.xref())
	{
		if(istream >> fileVersion.trailer())
		{
			if(istream.peek() == '\r' || istream.peek() == '\n')
			{
				if(istream.peek() == '\r')
				{
					if(istream.seekg(1, std::ios_base::cur) && istream.peek() == '\n')
					{
						istream.seekg(1, std::ios_base::cur);
					}
				}
				else
				{
					istream.seekg(1, std::ios_base::cur);
				}
				fileVersion.endOffset() = istream.tellg();
			}
			else
			{
				istream.setstate(std::ios_base::failbit);
			}
		}
	}
	return istream;
}