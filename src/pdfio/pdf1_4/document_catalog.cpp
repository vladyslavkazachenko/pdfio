#include "document_catalog.h"

#include "name.h"

namespace pdfio
{
   
namespace pdf1_4
{
   
namespace
{
   
const Name kKeyOpenAction = Name("OpenAction");
   
}
 
bool DocumentCatalog::hasOpenAction() const
{
   return contains(kKeyOpenAction);
}

const IndirectReference &DocumentCatalog::openAction() const
{
   return get<IndirectReference>(kKeyOpenAction);
}

void DocumentCatalog::prepare4Reading()
{
   insert<IndirectReference>(kKeyOpenAction);
}
   
}

}
