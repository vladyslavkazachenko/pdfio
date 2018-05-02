#pragma once

#include "pdfio/pdf1_0/document_catalog.h"
#include "array.h"
#include "name.h"
#include "indirect_reference.h"
#include "literalstring.h"

namespace pdfio
{
   
namespace pdf1_7
{
   
class DocumentCatalog: public pdf1_0::DocumentCatalog
{
public:
   class OutputIntent: public Dictionary
   {
   public:
      OutputIntent()
      {
         insert<IndirectReference>(Name("DestOutputProfile"));
         insert<Name>(Name("S"));
         insert<LiteralString>(Name("Info"));
         insert<LiteralString>(Name("RegistryName"));
         insert<LiteralString>(Name("OutputCondition"));
         insert<Name>(Name("Type"));
         insert<LiteralString>(Name("OutputConditionIdentifier"));
      }
   };
   
   DocumentCatalog()
   {
      insert<Array<OutputIntent>>(Name("OutputIntents"));
      insert<IndirectReference>(Name("ViewerPreferences"));
      insert<Name>(Name("PageLayout"));
   }
};
   
}
   
}
