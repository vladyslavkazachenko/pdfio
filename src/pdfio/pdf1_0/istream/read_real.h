#pragma once

#include <istream>

#include "pdfio/pdf1_0/real.h"

/*! \brief Reads the real from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::Real &real);