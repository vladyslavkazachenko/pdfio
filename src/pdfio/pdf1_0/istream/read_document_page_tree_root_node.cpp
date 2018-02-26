#include "read_document_page_tree_root_node.h"

#include "read_dictionary.h"

namespace pdf1_0 = pdfio::pdf1_0;

std::istream &operator>>(std::istream &istream, pdf1_0::DocumentPageTreeRootNode &root)
{
	if(istream >> static_cast<pdf1_0::Dictionary &>(root))
	{
		if(root.contains(pdf1_0::Name("Type")))
		{
			if(root.get<pdf1_0::Name>(pdf1_0::Name("Type")) == "Pages")
			{
				if(root.contains(pdf1_0::Name("Kids")))
				{
					if(!root.contains(pdf1_0::Name("Count")))
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