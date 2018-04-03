#include "read_file_header.h"

namespace pdf1_7 = pdfio::pdf1_7;

std::istream &operator>>(std::istream &istream, pdf1_7::FileHeader &)
{
	std::string buffer;
	if(istream >> buffer)
	{
		if(buffer != "%PDF-1.7" && buffer != "%PDF-1.6" && buffer != "%PDF-1.5" &&
			buffer != "%PDF-1.4" && buffer != "%PDF-1.3" && buffer != "%PDF-1.2" &&
			buffer != "%PDF-1.1" && buffer != "%PDF-1.0")
		{
			istream.setstate(std::ios_base::failbit);
		}
	}
	return istream;
}