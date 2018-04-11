#include "read_string.h"

#include "pdfio/log.h"
#include "read_literalstring.h"
#include "read_hexstring.h"

namespace pdf1_0 = pdfio::pdf1_0;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
  ":istream[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(&istream) << \
  "],string[" << reinterpret_cast<unsigned long>(&string) << "]:"

std::istream &operator>>(std::istream &istream, pdf1_0::String &string)
{
	LOG_DEBUG(LOG_PREFIX << "enter\n");
	auto pos = istream.tellg();
	if(istream >> string.literalString_)
	{
		string.field_ = pdf1_0::String::kLiteralString;
	}
	else
	{
		istream.clear();
		istream.seekg(pos);
		if(istream >> string.hexString_)
		{
			string.field_ = pdf1_0::String::kHexString;
		}
		else
		{
			string.field_ = pdf1_0::String::kNone;
		}
	}
	LOG_DEBUG(LOG_PREFIX << "leave\n");
	return istream;
}

#undef LOG_PREFIX