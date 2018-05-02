#pragma once

#include "dictionary.h"

namespace pdfio
{
   
namespace pdf1_4
{
   
class Action: public Dictionary
{
public:
   enum class Type
   {
      kInvalid,
      kGoTo,
   };
   
   Type type() const;
   
   void prepare4Reading();
};
   
}

}
