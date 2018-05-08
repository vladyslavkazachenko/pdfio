#include "destination.h"

#include <cassert>

namespace pdfio
{
   
namespace pdf1_0
{
 
Destination::Type Destination::type() const
{
   if(value_.type() == Variant::KNull)
   {
      return Type::kNull;
   }
   switch(value_.type())
   {
   case static_cast<int>(Type::kXYZ):
      return Type::kXYZ;
   case static_cast<int>(Type::kFit):
      return Type::kFit;
   case static_cast<int>(Type::kFitH):
      return Type::kFitH;
   case static_cast<int>(Type::kFitV):
      return Type::kFitV;
   case static_cast<int>(Type::kFitR):
      return Type::kFitR;
   default:
      return Type::kNull;
   }
}

Destination::XYZ &Destination::xyz()
{
   assert(type() == Type::kXYZ);
   return value_.get<Destination::XYZ>();
}

Destination::Fit &Destination::fit()
{
   assert(type() == Type::kFit);
   return value_.get<Destination::Fit>();
}

Destination::FitH &Destination::fitH()
{
   assert(type() == Type::kFitH);
   return value_.get<Destination::FitH>();
}

Destination::FitV &Destination::fitV()
{
   assert(type() == Type::kFitV);
   return value_.get<Destination::FitV>();
}

Destination::FitR &Destination::fitR()
{
   assert(type() == Type::kFitR);
   return value_.get<Destination::FitR>();
}

}

}
