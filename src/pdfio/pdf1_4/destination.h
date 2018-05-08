#pragma once

#include "indirect_reference.h"
#include "integer.h"
#include "name.h"
#include "string.h"

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
   
   struct NamedDestination
   {
      enum Type
      {
         kInvalid,
         kName,
         kString,
      };
      
      struct InvalidValue
      {
         
      };
      
      struct Value
      {
         InvalidValue invalid_;
         Name name_;
         String string_;
      };
      
      Type type_ = kInvalid;
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
      NamedDestination named_;
   };
   
   Type type_ = {Type::kInvalid};
   Value value_ = {{}};
};

}

}
