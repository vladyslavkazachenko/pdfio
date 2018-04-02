#include "read_file_trailer.h"

#include <iostream>

#include "pdfio/pdf1_0/istream/read_file_trailer.h"

namespace pdf1_7 = pdfio::pdf1_7;
namespace pdf1_0 = pdfio::pdf1_0;

std::istream &operator>>(std::istream &istream, pdf1_7::FileTrailer &fileTrailer)
{
	fileTrailer.prepare4Reading();
	return istream >> static_cast<pdf1_0::FileTrailer &>(fileTrailer);
}