#pragma once

#include <istream>

#include "pdfio/pdf1_0/generic_object.h"

/*! \brief Reads the name from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::GenericObject &object);