#pragma once

#include <istream>

#include "pdfio/pdf1_0/document_page_description.h"

/*! \brief Reads the description from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::DocumentPageDescription &description);