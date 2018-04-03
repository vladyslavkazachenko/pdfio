#pragma once

#include <istream>

#include "pdfio/pdf1_7/file_structure.h"
/*! \brief Reads the xrefEntry from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_7::FileStructure::XrefEntry &xrefEntry);
/*! \brief Reads the xrefSubsection from the istream*/
std::istream &operator>>(std::istream &istream, 
	pdfio::pdf1_7::FileStructure::XrefSubsection &xrefSubsection);
/*! \brief Reads the xrefSection from the istream*/
std::istream &operator>>(std::istream &istream, 
	pdfio::pdf1_7::FileStructure::XrefSection &xrefSection);
/*! \brief Reads the trailer from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_7::FileStructure::Trailer &trailer);
/*! \brief Reads the fileStruct from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_7::FileStructure &fileStruct);