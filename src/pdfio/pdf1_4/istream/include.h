#pragma once

#include "pdfio/pdf1_0/istream/include.h"
#include "read_destination.h"
#include "read_action.h"

using namespace pdfio;
using namespace pdfio::pdf1_4;

REGISTER_READ_HANDLER_FOR_TYPE(Destination);
REGISTER_READ_HANDLER_FOR_TYPE(Action);
