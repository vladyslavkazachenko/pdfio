#include "destination.h"

#include <cassert>

namespace pdfio
{
   
template <> int Variant::GetTypeId<pdf1_0::Destination::XYZ>()
{
   return static_cast<int>(pdf1_0::Destination::Type::kXYZ);
}

template <> int Variant::GetTypeId<pdf1_0::Destination::Fit>()
{
   return static_cast<int>(pdf1_0::Destination::Type::kFit);
}

template <> int Variant::GetTypeId<pdf1_0::Destination::FitH>()
{
   return static_cast<int>(pdf1_0::Destination::Type::kFitH);
}

template <> int Variant::GetTypeId<pdf1_0::Destination::FitV>()
{
   return static_cast<int>(pdf1_0::Destination::Type::kFitV);
}

template <> int Variant::GetTypeId<pdf1_0::Destination::FitR>()
{
   return static_cast<int>(pdf1_0::Destination::Type::kFitR);
}
   
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
   return value_.get<Destination::XYZ>();
}

Destination::Fit &Destination::fit()
{
   return value_.get<Destination::Fit>();
}

Destination::FitH &Destination::fitH()
{
   return value_.get<Destination::FitH>();
}

Destination::FitV &Destination::fitV()
{
   return value_.get<Destination::FitV>();
}

Destination::FitR &Destination::fitR()
{
   return value_.get<Destination::FitR>();
}

}

}
