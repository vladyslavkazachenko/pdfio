#pragma once

#include <istream>

#include "pdfio/pdf1_0/document_catalog.h"
/*! \brief Reads the catalog from the istream*/
std::istream &operator>>(std::istream &istream, 
   pdfio::pdf1_0::DocumentCatalog &catalog);
