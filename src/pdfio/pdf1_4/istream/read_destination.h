#pragma once

#include <istream>

#include "pdfio/pdf1_4/destination.h"

/*! \brief Reads the destination from the istream*/
std::istream &operator>>(std::istream &istream, 
   pdfio::pdf1_4::Destination &destination);
