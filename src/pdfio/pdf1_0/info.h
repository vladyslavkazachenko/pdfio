#pragma once

#include "dictionary.h"
#include "string.h"

namespace pdfio
{

namespace pdf1_0
{

class Info: public Dictionary
{
public:
   const String &creator() const;
   const String &creationDate() const;
   const String &author() const;
   const String &producer() const;
   
   void prepare4Reading();
};
   
}

}
