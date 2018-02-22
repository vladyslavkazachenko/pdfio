#pragma once

#include <istream>

#include "pdfio/pdf1_0/file_xref.h"
/*! \brief Reads the fileXref from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::FileXref &fileXref);