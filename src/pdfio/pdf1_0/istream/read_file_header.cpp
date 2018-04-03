#include "read_file_header.h"

namespace pdf1_0 = pdfio::pdf1_0;

std::istream &operator>>(std::istream &istream, pdf1_0::FileHeader &)
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