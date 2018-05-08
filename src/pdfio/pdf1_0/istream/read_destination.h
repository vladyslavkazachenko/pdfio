#pragma once

#include <istream>

#include "pdfio/pdf1_0/destination.h"

/*! \brief Reads the destination from the istream*/
std::istream &operator>>(std::istream &istream, 
   pdfio::pdf1_0::Destination &destination);
