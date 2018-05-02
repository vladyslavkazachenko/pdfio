#pragma once

#include "pdfio/pdf1_0/document_catalog.h"
#include "indirect_reference.h"

namespace pdfio
{
   
namespace pdf1_4
{
   
class DocumentCatalog: public pdf1_0::DocumentCatalog
{
public:
   bool hasOpenAction() const;
   const IndirectReference &openAction() const;
   
   void prepare4Reading();
};
   
}
   
}
