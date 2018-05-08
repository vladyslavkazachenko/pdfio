#pragma once

#include "write_name.h"
#include "write_indirect_reference.h"
#include "write_dictionary.h"
#include "pdfio/write_generic_object.h"

using namespace pdfio;
using namespace pdfio::pdf1_0;

REGISTER_WRITE_HANDLER_FOR_TYPE(Name);
REGISTER_WRITE_HANDLER_FOR_TYPE(IndirectReference);
REGISTER_WRITE_HANDLER_FOR_TYPE(Dictionary);
