#pragma once

#include <istream>

#include "pdfio/pdf1_0/hexstring.h"
/*! \brief Reads the hexstring from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::HexString &hexstring);