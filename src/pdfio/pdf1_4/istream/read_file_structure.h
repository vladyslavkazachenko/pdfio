#pragma once

#include <istream>

#include "pdfio/pdf1_4/file_structure.h"

/*! \brief Reads the fileStruct from the istream*/
std::istream &operator>>(std::istream &istream, 
   pdfio::pdf1_4::FileStructure &fileStruct);
/*! \brief Reads the trailer from the istream*/
std::istream &operator>>(std::istream &istream, 
   pdfio::pdf1_4::FileStructure::Trailer &trailer);
