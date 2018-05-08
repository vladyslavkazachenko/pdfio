#pragma once

#include <ostream>

#include "pdfio/pdf1_0/dictionary.h"

/*! \brief Write the dictionary to the ostream*/
std::ostream &operator<<(std::ostream &ostream, 
   const pdfio::pdf1_0::Dictionary &dictionary);
