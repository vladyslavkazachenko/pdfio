#pragma once

#include "dictionary.h"

namespace pdfio
{
   
namespace pdf1_0
{
   
/*! \brief Basic class for page tree nodes.*/
class DocumentPageTreeNode: public Dictionary
{
protected:
   /*! \brief Inserts {/Type type}.*/
   inline DocumentPageTreeNode(const Name &type)
   {
      insert(Name("Type"), type);
   }
};

}

}