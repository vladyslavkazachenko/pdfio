#pragma once

#include "literalstring.h"
#include "hexstring.h"

namespace pdfio
{

namespace pdf1_0
{

struct String
{
   enum Field
   {
      kNone,
      kLiteralString,
      kHexString,
   };
   
   LiteralString literalString_;
   HexString hexString_;
   Field field_ = kNone;
};
   
}
   
}
