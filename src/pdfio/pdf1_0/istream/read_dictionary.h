#pragma once

#include <istream>

#include "pdfio/pdf1_0/dictionary.h"

namespace pdf1_0 = pdfio::pdf1_0;
/*! \brief Reads the dictionary from the istream*/
std::istream &operator>>(std::istream &istream, pdf1_0::Dictionary &dictionary);