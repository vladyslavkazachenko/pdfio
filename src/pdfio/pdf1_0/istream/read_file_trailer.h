#pragma once

#include <istream>

#include "pdfio/pdf1_0/file_trailer.h"
/*! \brief Reads the fileTrailer from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::FileTrailer &fileTrailer);