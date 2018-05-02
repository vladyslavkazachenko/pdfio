#pragma once

#include "indirect_reference.h"

namespace pdfio
{
   
namespace pdf1_4
{

class Destination
{
public:
   enum class Type
   {
      kInvalid,
      kFit,
   };
   
   struct Fit
   {
      IndirectReference page_;
   };
   
   inline Type &type()
   {
      return type_;
   }
   inline Fit &fit()
   {
      return value_.fit_;
   }
   
private:
   struct Invalid{};
   
   union Value
   {
      Invalid invalid_;
      Fit fit_;
   };
   
   Type type_ = {Type::kInvalid};
   Value value_ = {{}};
};

}

}
