#pragma once

#include <istream>

#include "pdfio/pdf1_0/integer.h"

namespace pdf1_0 = pdfio::pdf1_0;
/*! \brief Reads the integer from the istream*/
std::istream &operator>>(std::istream &istream, pdf1_0::Integer &integer);