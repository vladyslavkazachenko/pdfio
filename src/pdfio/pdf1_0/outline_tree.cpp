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
const Name kKeyParent = Name("Parent");
const Name kKeyTitle = Name("Title");
const Name kKeyNext = Name("Next");
const Name kKeyPrev = Name("Prev");
   
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


OutlineTree::Entry::Entry()
{
   insert<IndirectReference>(kKeyParent);
   insert<String>(kKeyTitle);
}

const IndirectReference &OutlineTree::Entry::parent() const
{
   return get<IndirectReference>(kKeyParent);
}

IndirectReference &OutlineTree::Entry::parent()
{
   return get<IndirectReference>(kKeyParent);
}

const String &OutlineTree::Entry::title() const
{
   return get<String>(kKeyTitle);
}

String &OutlineTree::Entry::title()
{
   return get<String>(kKeyTitle);
}

bool OutlineTree::Entry::hasNext() const
{
   return contains(kKeyNext);
}

const IndirectReference &OutlineTree::Entry::next() const
{
   return get<IndirectReference>(kKeyNext);
}

IndirectReference &OutlineTree::Entry::next()
{
   if(!hasNext())
   {
      insert<IndirectReference>(kKeyNext);
   }
   return get<IndirectReference>(kKeyNext);
}

bool OutlineTree::Entry::hasPrev() const
{
	return contains(kKeyPrev);
}

const IndirectReference &OutlineTree::Entry::prev() const
{
	return get<IndirectReference>(kKeyPrev);
}

IndirectReference &OutlineTree::Entry::prev()
{
	if(!hasPrev())
	{
		insert<IndirectReference>(kKeyPrev);
	}
	return get<IndirectReference>(kKeyPrev);
}

void OutlineTree::Entry::prepare4Reading()
{
   OutlineTree::prepare4Reading();
   insert<IndirectReference>(kKeyNext);
	insert<IndirectReference>(kKeyPrev);
}
   
}

}