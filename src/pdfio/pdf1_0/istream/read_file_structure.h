#pragma once

#include <istream>

#include "pdfio/pdf1_0/file_structure.h"
/*! \brief Reads the xrefEntry from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::FileStructure::XrefEntry &xrefEntry);
/*! \brief Reads the xrefSubsection from the istream*/
std::istream &operator>>(std::istream &istream, 
	pdfio::pdf1_0::FileStructure::XrefSubsection &xrefSubsection);
/*! \brief Reads the xrefSection from the istream*/
std::istream &operator>>(std::istream &istream, 
	pdfio::pdf1_0::FileStructure::XrefSection &xrefSection);