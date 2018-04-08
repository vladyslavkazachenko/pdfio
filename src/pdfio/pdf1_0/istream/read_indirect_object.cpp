#include "read_indirect_object.h"

#include "read_integer.h"
#include "pdfio/read_generic_object.h"
#include "pdfio/log.h"

namespace pdf1_0 = pdfio::pdf1_0;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
	":istream[" << std::hex << std::showbase << reinterpret_cast<unsigned long>(&istream) << \
	"],indirectObject[" << reinterpret_cast<unsigned long>(&indirectObject) << "]:"

std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::IndirectObject &indirectObject)
{
	LOG_DEBUG(LOG_PREFIX << "enter\n");
	if(istream >> indirectObject.objectNumber())
	{
		LOG_DEBUG(LOG_PREFIX << "object number is " << indirectObject.objectNumber() << "\n");
		if(istream >> indirectObject.generationNumber())
		{
			LOG_DEBUG(LOG_PREFIX << "generation number is " << 
				indirectObject.generationNumber() << "\n");
			while(istream && std::isspace(istream.peek()))
			{
				LOG_DEBUG(LOG_PREFIX << "skipping space character:" << std::hex << std::showbase << 
					istream.peek() << "\n");
				static_cast<void>(istream.get());
			}
			char tmp[4] = {'\0', '\0', '\0', '\0'};
			if(istream.read(tmp, 3))
			{
				std::string buffer(tmp);
				LOG_DEBUG(LOG_PREFIX << "obj line is " << buffer << "\n");
				if(buffer == "obj")
				{
					if(istream >> indirectObject.get())
					{
						if(istream >> buffer)
						{
							LOG_DEBUG(LOG_PREFIX << "endobj line is " << buffer << "\n");
							if(buffer != "endobj")
							{
								istream.setstate(std::ios_base::failbit);
							}
						}
					}
					else
					{
						LOG_ERROR(LOG_PREFIX << "failed to read object, stream state is " << 
							istream.rdstate() << "\n");
					}
				}
				else
				{
					istream.setstate(std::ios_base::failbit);
				}
			}
		}
	}
	LOG_DEBUG(LOG_PREFIX << "leave\n");
	return istream;
}

#undef LOG_PREFIX