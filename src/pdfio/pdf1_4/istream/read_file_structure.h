#pragma once

#include <istream>

#include "pdfio/pdf1_4/file_structure.h"
#include "pdfio/pdf1_4/file_version.h"
#include "pdfio/file_structure.h"

/*! \brief Reads the fileStruct from the istream*/
std::istream &operator>>(std::istream &istream, 
   pdfio::pdf1_4::FileStructure &fileStruct);
/*! \brief Reads the trailer from the istream*/
std::istream &operator>>(std::istream &istream, 
   pdfio::pdf1_4::FileStructure::Trailer &trailer);
/*! \brief Reads the trailer from the istream*/
std::istream &operator>>(std::istream &istream, 
   pdfio::FileStructure<pdfio::pdf1_4::FileVersion> &fileStruct);
