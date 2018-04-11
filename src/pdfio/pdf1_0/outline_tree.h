#pragma once

#include "dictionary.h"
#include "integer.h"
#include "indirect_reference.h"

namespace pdfio
{
   
namespace pdf1_0
{
   
class OutlineTree: public Dictionary
{
public:
   bool hasCount() const;
   const Integer &count() const;
   Integer &count();
   
   bool hasFirst() const;
   const IndirectReference &first() const;
   IndirectReference &first();
   
   bool hasLast() const;
   const IndirectReference &last() const;
   IndirectReference &last();
   
   void prepare4Reading();
};
   
}
   
}