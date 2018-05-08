#pragma once

#include <ostream>

#include "pdfio/pdf1_0/indirect_reference.h"

/*! \brief Write the name to the ostream*/
std::ostream &operator<<(std::ostream &ostream, 
   const pdfio::pdf1_0::IndirectReference &indirRef);
