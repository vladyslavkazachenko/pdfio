#pragma once

#include "pdfio/pdf1_4/action.h"

/*! \brief Reads the catalog from the istream*/
std::istream &operator>>(std::istream &istream, 
   pdfio::pdf1_4::Action &action);
