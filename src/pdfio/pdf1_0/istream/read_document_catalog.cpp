#include "read_document_catalog.h"

#include "pdfio/pdf1_0/generic_object_type.h"
#include "read_indirect_object.h"

namespace pdf1_0 = pdfio::pdf1_0;

std::istream &operator>>(std::istream &istream, pdf1_0::DocumentCatalog &catalog)
{
	catalog.prepare4Read();
	if(istream >> catalog.object())
	{
		if(catalog.object().get<pdf1_0::Dictionary>().contains(pdf1_0::Name("Type")))
		{
			if(catalog.object().get<pdf1_0::Dictionary>().get<pdf1_0::Name>(pdf1_0::Name("Type")) == "Catalog")
			{
				if(!catalog.object().get<pdf1_0::Dictionary>().contains(pdf1_0::Name("Pages")))
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