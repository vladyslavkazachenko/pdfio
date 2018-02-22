#pragma once

#include <istream>

#include "pdfio/pdf1_0/file.h"
/*! \brief Reads the file from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::File &file);