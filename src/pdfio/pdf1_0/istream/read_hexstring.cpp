#include "read_hexstring.h"

#include "pdfio/log.h"

namespace pdf1_0 = pdfio::pdf1_0;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
  ":istream[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(&istream) << \
  "],hexstring[" << reinterpret_cast<unsigned long>(&hexstring) << "]:"

std::istream &operator>>(std::istream &istream, pdf1_0::HexString &hexstring)
{
	LOG_DEBUG(LOG_PREFIX << "entry\n");
	char ch;
	if(istream >> ch)
	{
		if(ch == '<')
		{
			while(istream && std::isspace(istream.peek()))
			{
				static_cast<void>(istream.get());
			}
			std::string s;
			while(istream && std::isxdigit(istream.peek()))
			{
				s += istream.get();
			}
			if(istream)
			{
				if(istream >> ch)
				{
					if(ch == '>')
					{
						hexstring = s;
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
	LOG_DEBUG(LOG_PREFIX << "leave\n");
	return istream;
}

#undef LOG_PREFIX