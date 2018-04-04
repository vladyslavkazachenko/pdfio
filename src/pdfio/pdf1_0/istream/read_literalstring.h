#pragma once

#include <istream>

#include "pdfio/pdf1_0/literalstring.h"
/*! \brief Reads the literalString from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::LiteralString &literalString);