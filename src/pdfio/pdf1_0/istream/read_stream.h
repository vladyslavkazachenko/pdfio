#pragma once

#include <istream>

#include "pdfio/pdf1_0/stream.h"
/*! \brief Reads the pdfStream from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::Stream &pdfStream);