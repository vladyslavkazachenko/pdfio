#pragma once

#include <istream>

#include "pdfio/pdf1_0/name.h"
/*! \brief Reads the name from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::Name &name);