#include "document_pages_tree.h"

namespace pdfio
{
   
namespace pdf1_0
{
   
namespace
{

const Name kKeyParent = Name("Parent");
   
}

const Name DocumentPagesTree::kKeyType = Name("Type");
const Name DocumentPagesTree::kKeyKids = Name("Kids");
const Name DocumentPagesTree::kKeyCount = Name("Count");
const Name DocumentPagesTree::kKeyMediaBox = Name("MediaBox");
const Name DocumentPagesTree::kNamePages = Name("Pages");
const Name DocumentPagesTree::kNamePage = Name("Page");
   
DocumentPagesTree::DocumentPagesTree()
{
   insert<Name>(kKeyType);
}
   
bool DocumentPagesTree::isTree() const
{
   return get<Name>(kKeyType) == kNamePages;
}

bool DocumentPagesTree::hasKids() const
{
   return contains(kKeyKids);
}

const Array<IndirectReference> &DocumentPagesTree::kids() const
{
   return get<Array<IndirectReference>>(kKeyKids);
}

bool DocumentPagesTree::hasCount() const
{
   return contains(kKeyCount);
}

const Integer &DocumentPagesTree::count() const
{
   return get<Integer>(kKeyCount);
}

bool DocumentPagesTree::hasParent() const
{
   return contains(kKeyParent);
}

const IndirectReference &DocumentPagesTree::parent() const
{
   return get<IndirectReference>(kKeyParent);
}

bool DocumentPagesTree::hasMediaBox() const
{
   return contains(kKeyMediaBox);
}

const Array<Integer> &DocumentPagesTree::mediaBox() const
{
   return get<Array<Integer>>(kKeyMediaBox);
}

void DocumentPagesTree::prepare4Reading()
{
   insert<Array<IndirectReference>>(kKeyKids);
   insert<Integer>(kKeyCount);
   insert<IndirectReference>(kKeyParent);
   insert<Array<Integer>>(kKeyMediaBox);
}
   
}

}