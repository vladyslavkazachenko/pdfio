#pragma once

#include <ostream>

#include "pdfio/pdf1_0/name.h"

/*! \brief Write the name to the ostream*/
std::ostream &operator<<(std::ostream &ostream, 
   const pdfio::pdf1_0::Name &name);
