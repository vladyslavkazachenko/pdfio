#pragma once

#include <istream>

#include "pdfio/pdf1_0/info.h"

/*! \brief Reads the info from the istream*/
std::istream &operator>>(std::istream &istream, 
   pdfio::pdf1_0::Info &info);
