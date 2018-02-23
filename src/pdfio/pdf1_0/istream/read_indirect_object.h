#pragma once

#include <istream>

#include "pdfio/pdf1_0/indirect_object.h"
/*! \brief Reads the indirectObject from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::IndirectObject &indirectObject);