#pragma once

#include <istream>

#include "pdfio/pdf1_4/file_version.h"

/*! \brief Reads the header from the istream*/
std::istream &operator>>(std::istream &istream, 
   pdfio::pdf1_4::FileVersion::Header &header);
/*! \brief Reads the entry from the istream*/
std::istream &operator>>(std::istream &istream, 
   pdfio::pdf1_4::FileVersion::XrefEntry &entry);
/*! \brief Reads the version from the istream*/
std::istream &operator>>(std::istream &istream, 
   pdfio::pdf1_4::FileVersion::Trailer &trailer);
