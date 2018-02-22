#pragma once

#include <istream>

#include "pdfio/pdf1_0/indirect_reference.h"
/*! \brief Reads the indirectReference from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::IndirectReference &indirectReference);