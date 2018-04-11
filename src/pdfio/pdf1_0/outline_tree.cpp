#include "outline_tree.h"

namespace pdfio
{
   
namespace pdf1_0
{
   
namespace
{
   
const Name kKeyCount = Name("Count");
const Name kKeyFirst = Name("First");
const Name kKeyLast = Name("Last");
   
}
   
bool OutlineTree::hasCount() const
{
   return contains(kKeyCount);
}

const Integer &OutlineTree::count() const
{
   return get<Integer>(kKeyCount);
}

Integer &OutlineTree::count()
{
   if(!hasCount())
   {
      insert<Integer>(kKeyCount);
   }
   return get<Integer>(kKeyCount);
}

bool OutlineTree::hasFirst() const
{
   return contains(kKeyFirst);
}

const IndirectReference &OutlineTree::first() const
{
   return get<IndirectReference>(kKeyFirst);
}

IndirectReference &OutlineTree::first()
{
   if(!hasFirst())
   {
      insert<IndirectReference>(kKeyFirst);
   }
   return get<IndirectReference>(kKeyFirst);
}

bool OutlineTree::hasLast() const
{
   return contains(kKeyLast);
}

const IndirectReference &OutlineTree::last() const
{
   return get<IndirectReference>(kKeyLast);
}

IndirectReference &OutlineTree::last()
{
   if(!hasLast())
   {
      insert<IndirectReference>(kKeyLast);
   }
   return get<IndirectReference>(kKeyLast);
}
   
void OutlineTree::prepare4Reading()
{
   insert<Integer>(kKeyCount);
   insert<IndirectReference>(kKeyFirst);
   insert<IndirectReference>(kKeyLast);
}
   
}

}