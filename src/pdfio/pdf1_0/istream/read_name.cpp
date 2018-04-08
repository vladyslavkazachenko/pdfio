#include "read_name.h"

#include "pdfio/log.h"

namespace pdf1_0 = pdfio::pdf1_0;

static bool isDelimiter(char ch)
{
  return std::isspace(ch) || ch == '[' || ch == '<' || ch == '/';
}

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
	":istream[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(&istream) << \
	"],name[" << reinterpret_cast<unsigned long>(&name) << "]:"

std::istream &operator>>(std::istream &istream, pdf1_0::Name &name)
{
	LOG_DEBUG(LOG_PREFIX << "enter\n");
	char slash = 0;
	if(istream >> slash)
	{
		LOG_DEBUG(LOG_PREFIX << "delimiter character is " << static_cast<int>(slash) << "\n");
		if(slash != '/')
		{
			LOG_DEBUG(LOG_PREFIX << "invalid delimiter character: " << static_cast<int>(slash) << "\n");
			istream.setstate(std::ios_base::failbit);
		}
		else
		{
			std::string buffer;
			while(istream && !isDelimiter(istream.peek()))
			{
				auto ch = istream.get();
				if(istream)
				{
					buffer += ch;
				}
			}
			if(istream.eof())
			{
				istream.clear();
			}
			if(istream)
			{
				LOG_DEBUG(LOG_PREFIX << "name is " << buffer << "\n");
				name = buffer;
			}
		}
	}
	else
	{
		LOG_ERROR(LOG_PREFIX << "failed to read delimiter\n");
	}
	LOG_DEBUG(LOG_PREFIX << "leave\n");
	return istream;
}

#undef LOG_PREFIX