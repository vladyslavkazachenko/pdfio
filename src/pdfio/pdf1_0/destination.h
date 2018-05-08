#pragma once

#include "pdfio/variant.h"
#include "integer.h"
#include "indirect_reference.h"

namespace pdfio
{
   
namespace pdf1_0
{
   
class Destination
{
public:
   enum class Type
   {
      kNull = Variant::KNull,
      kXYZ,
      kFit,
      kFitH,
      kFitV,
      kFitR,
   };
   
   struct ExplicitDestination
   {
      IndirectReference page_;
   };
   
   struct XYZ: ExplicitDestination
   {
      Integer left_;
      Integer top_;
      Integer zoom_;
   };
   
   struct Fit: ExplicitDestination
   {
      
   };
   
   struct FitH: ExplicitDestination
   {
      Integer top_;
   };
   
   struct FitV: ExplicitDestination
   {
      Integer left_;
   };
   
   struct FitR: ExplicitDestination
   {
      Integer left_;
      Integer bottom_;
      Integer right_;
      Integer top_;
   };
   
   Type type() const;
   XYZ &xyz();
   Fit &fit();
   FitH &fitH();
   FitV &fitV();
   FitR &fitR();
   
private:
   Variant value_;
};
   
}
   
}
