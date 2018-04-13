#pragma once

#include <istream>

#include "pdfio/pdf1_0/document_pages_tree.h"

/*! \brief Reads the pagesTree from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::DocumentPagesTree &pagesTree);