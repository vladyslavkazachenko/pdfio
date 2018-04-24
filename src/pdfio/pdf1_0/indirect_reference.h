#pragma once

#include "integer.h"

namespace pdfio
{

namespace pdf1_0
{
   
/*! \brief PDF indirect reference object.*/
class IndirectReference
{
public:
   /*! \brief Default constructor.*/
   IndirectReference() = default;
   /*! \brief Initializes indirect reference by objectNumber and 
    * generationNumber.
    */
   inline IndirectReference(int objectNumber, int generationNumber)
   : objectNumber_(objectNumber)
   , generationNumber_(generationNumber)
   {
      
   }
   /*! \brief Returns object number as rvalue.*/
   inline const Integer &objectNumber() const
   {
      return objectNumber_;
   }
   /*! \brief Returns object number as lvalue.*/
   inline Integer &objectNumber()
   {
      return objectNumber_;
   }
   /*! \brief Returns generation number as rvalue.*/
   inline const Integer &generationNumber() const
   {
      return generationNumber_;
   }
   /*! \brief Returns generation number as lvalue.*/
   inline Integer &generationNumber()
   {
      return generationNumber_;
   }
   /*! \brief Checks whether the indirect reference equals to other.*/
   inline bool operator==(const IndirectReference &other) const
   {
      return objectNumber_ == other.objectNumber_ && 
         generationNumber_ == other.generationNumber_;
   }
   
private:
   Integer objectNumber_ = Integer();
   Integer generationNumber_ = Integer();
};

}

}
