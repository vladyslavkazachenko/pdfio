#pragma once

#include "pdfio/pdf1_0/string.h"

/*! \brief Reads the string from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::String &string);