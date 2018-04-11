#pragma once

#include "dictionary.h"
#include "integer.h"
#include "indirect_reference.h"
#include "literalstring.h"

namespace pdfio
{
   
namespace pdf1_0
{
   
class OutlineTree: public Dictionary
{
public:
   class Entry;
   
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

class OutlineTree::Entry: public OutlineTree
{
public:
   Entry();
      
   const IndirectReference &parent() const;
   IndirectReference &parent();
      
   const LiteralString &title() const;
   LiteralString &title();
      
   bool hasNext() const;
   const IndirectReference &next() const;
   IndirectReference &next();
      
   void prepare4Reading();
};
   
}
   
}