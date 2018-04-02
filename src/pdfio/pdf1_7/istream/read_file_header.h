#pragma once

#include <istream>

#include "pdfio/pdf1_7/file_header.h"
/*! \brief Reads the fileHeader from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_7::FileHeader &fileHeader);