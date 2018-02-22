#pragma once

#include <istream>

#include "pdfio/pdf1_0/dictionary.h"
/*! \brief Reads the dictionary from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::Dictionary &dictionary);