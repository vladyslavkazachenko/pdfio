#include "document_catalog.h"

namespace pdfio
{

namespace pdf1_0
{

const Name DocumentCatalog::kKeyType = Name("Type");
const Name DocumentCatalog::kValueType = Name("Catalog");
const Name DocumentCatalog::kKeyPages = Name("Pages");
const Name DocumentCatalog::kKeyOutlines = Name("Outlines");
const Name DocumentCatalog::kKeyPageMode = Name("PageMode");

DocumentCatalog::DocumentCatalog()
{
   insert<IndirectReference>(kKeyPages);
}

const IndirectReference &DocumentCatalog::pages() const
{
   return get<IndirectReference>(kKeyPages);
}

IndirectReference &DocumentCatalog::pages()
{
   return get<IndirectReference>(kKeyPages);
}

bool DocumentCatalog::hasOutlines() const
{
   return contains(kKeyOutlines);
}

const IndirectReference &DocumentCatalog::outlines() const
{
   return get<IndirectReference>(kKeyOutlines);
}

IndirectReference &DocumentCatalog::outlines()
{
   if(!hasOutlines())
   {
      insert<IndirectReference>(kKeyOutlines);
   }
   return get<IndirectReference>(kKeyOutlines);
}

bool DocumentCatalog::hasPageMode() const
{
   return contains(kKeyPageMode);
}

const Name &DocumentCatalog::pageMode() const
{
   return get<Name>(kKeyPageMode);
}

Name &DocumentCatalog::pageMode()
{
   if(!hasPageMode())
   {
      insert<Name>(kKeyPageMode);
   }
   return get<Name>(kKeyPageMode);
}

void DocumentCatalog::prepare4Read()
{
   insert<Name>(kKeyType);
   insert<IndirectReference>(kKeyPages);
   insert<IndirectReference>(kKeyOutlines);
   insert<Name>(kKeyPageMode);
}

}

}
