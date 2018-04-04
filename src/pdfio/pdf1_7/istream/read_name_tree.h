#pragma once

#include <istream>

#include "pdfio/pdf1_7/name_tree.h"
/*! \brief Reads the nameTree from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_7::NameTree &nameTree);