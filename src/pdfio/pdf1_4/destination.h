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
      kXYZ,
      kFit,
      kFitH,
      kFitV,
      kFitR,
      kFitB,
      kFitBH,
      kFitBV,
      kNamed,
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
   inline XYZ &xyz()
   {
      return value_.xyz_;
   }
   inline Fit &fit()
   {
      return value_.fit_;
   }
   inline FitH &fitH()
   {
      return value_.fitH_;
   }
   inline FitV &fitV()
   {
      return value_.fitV_;
   }
   inline FitR &fitR()
   {
      return value_.fitR_;
   }
   inline FitB &fitB()
   {
      return value_.fitB_;
   }
   inline FitBH &fitBH()
   {
      return value_.fitBH_;
   }
   inline FitBV &fitBV()
   {
      return value_.fitBV_;
   }
   inline NamedDestination &named()
   {
      return value_.named_;
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
