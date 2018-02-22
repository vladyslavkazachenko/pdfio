#pragma once

#include <istream>

#include "pdfio/pdf1_0/file_version.h"
/*! \brief Reads the fileVersion from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::FileVersion &fileVersion);