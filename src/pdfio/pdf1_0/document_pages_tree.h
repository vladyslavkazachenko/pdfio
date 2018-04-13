#pragma once

#include "dictionary.h"
#include "indirect_reference.h"
#include "array.h"
#include "integer.h"

namespace pdfio
{
   
namespace pdf1_0
{
   
class DocumentPagesTree : public Dictionary
{
public:
   DocumentPagesTree();
   
   bool isTree() const;
   bool hasKids() const;
   const Array<IndirectReference> &kids() const;
   bool hasCount() const;
   const Integer &count() const;
   bool hasParent() const;
   const IndirectReference &parent() const;
   bool hasMediaBox() const;
   const Array<Integer> &mediaBox() const;
   void prepare4Reading();
   
   static const Name kKeyType;
   static const Name kKeyKids;
   static const Name kKeyCount;
   static const Name kKeyMediaBox;
   static const Name kNamePages;
   static const Name kNamePage;
};   

}
   
}