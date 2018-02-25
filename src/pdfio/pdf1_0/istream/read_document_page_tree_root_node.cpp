#include "read_document_page_tree_root_node.h"

#include "read_indirect_object.h"

namespace pdf1_0 = pdfio::pdf1_0;

std::istream &operator>>(std::istream &istream, pdf1_0::DocumentPageTreeRootNode &root)
{
	if(istream >> root.object())
	{
		const pdf1_0::Dictionary &dictionary = root.object().get<pdf1_0::Dictionary>();
		if(dictionary.contains(pdf1_0::Name("Type")))
		{
			if(dictionary.get<pdf1_0::Name>(pdf1_0::Name("Type")) == "Pages")
			{
				if(dictionary.contains(pdf1_0::Name("Kids")))
				{
					if(!dictionary.contains(pdf1_0::Name("Count")))
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
		else
		{
			istream.setstate(std::ios_base::failbit);
		}
	}
	return istream;
}