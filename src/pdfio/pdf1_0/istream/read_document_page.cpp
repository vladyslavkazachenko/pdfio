#include "read_document_page.h"

#include <iostream>

#include "read_name.h"
#include "read_indirect_reference.h"
#include "read_dictionary.h"
#include "read_array.h"

namespace pdf1_0 = pdfio::pdf1_0;

std::istream &operator>>(std::istream &istream, pdf1_0::DocumentPage &page)
{
	page.prepare4Read();
	if(istream >> static_cast<pdf1_0::Dictionary &>(page))
	{
		
	}
	return istream;
}

std::istream &operator>>(std::istream &istream, pdf1_0::DocumentPage::Resources &resources)
{
	resources.prepare4Read();
	return istream >> static_cast<pdf1_0::Dictionary &>(resources);
}

std::istream &operator>>(std::istream &istream, pdf1_0::DocumentPage::ResourceDictionary &resource)
{
	std::string buffer;
	if(istream >> buffer)
	{
		if(buffer == "<<")
		{
			auto streamPosition = istream.tellg();
			while(istream)
			{
				streamPosition = istream.tellg();
				pdf1_0::Name name;
				if(istream >> name)
				{
					pdf1_0::IndirectReference value;
					if(istream >> value)
					{
						resource[name] = value;
					}
					else
					{
						std::cerr << __PRETTY_FUNCTION__ << ":failed to read value\n";
					}
				}
				else
				{
					std::cerr << __PRETTY_FUNCTION__ << ":failed to read key\n";
				}
			}
			istream.clear();
			if(istream.seekg(streamPosition))
			{
				if(istream >> buffer)
				{
					if(buffer != ">>")
					{
						std::cerr << __PRETTY_FUNCTION__ << ":failed to read second delimiter\n";
						istream.setstate(std::ios_base::failbit);
					}
				}
			}
		}
		else
		{
			std::cerr << __PRETTY_FUNCTION__ << ":invalid first delimiter\n";
			istream.setstate(std::ios_base::failbit);
		}
	}
	return istream;
}

std::istream &operator>>(std::istream &istream, pdf1_0::DocumentPage::ProcSet &procSet)
{
  return istream >> static_cast<pdf1_0::Array<pdf1_0::Name> &>(procSet);
}