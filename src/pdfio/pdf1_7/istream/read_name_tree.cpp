#include "read_name_tree.h"

namespace pdf1_7 = pdfio::pdf1_7;

std::istream &operator>>(std::istream &istream, pdf1_7::NameTree &/*nameTree*/)
{
	return istream;
}