#pragma once

#include "indirect_reference.h"
#include "integer.h"

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
   
   struct FitB: ExplicitDestination
   {
      
   };
   
   struct FitBH: ExplicitDestination
   {
      Integer top_;
   };
   
   struct FitBV: ExplicitDestination
   {
      Integer left_;
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
      XYZ xyz_;
      Fit fit_;
      FitH fitH_;
      FitV fitV_;
      FitR fitR_;
      FitB fitB_;
      FitBH fitBH_;
      FitBV fitBV_;
   };
   
   Type type_ = {Type::kInvalid};
   Value value_ = {{}};
};

}

}
