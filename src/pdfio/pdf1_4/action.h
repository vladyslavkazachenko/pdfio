#pragma once

#include "dictionary.h"
#include "name.h"
#include "destination.h"

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
   
   struct GoTo
   {
      Destination destination_;
   };
   
   Action();
   
   Name &s();
   bool hasD() const;
   Destination &d();
   
   void prepare4Reading();
   
   Type type() const;
   GoTo &go2();
   
private:
   struct Invalid{};
   
   union Value
   {
      Invalid invalid_;
      GoTo go2_;
   };
   
   Value value_ = {{}};
};
   
}

}
