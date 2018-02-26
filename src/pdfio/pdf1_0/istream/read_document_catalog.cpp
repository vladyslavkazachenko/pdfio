#include "read_document_catalog.h"

#include "read_dictionary.h"

namespace pdf1_0 = pdfio::pdf1_0;

std::istream &operator>>(std::istream &istream, pdf1_0::DocumentCatalog &catalog)
{
	catalog.prepare4Read();
	if(istream >> static_cast<pdf1_0::Dictionary &>(catalog))
	{
		if(catalog.contains(pdf1_0::Name("Type")))
		{
			if(catalog.get<pdf1_0::Name>(pdf1_0::Name("Type")) == "Catalog")
			{
				if(!catalog.contains(pdf1_0::Name("Pages")))
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