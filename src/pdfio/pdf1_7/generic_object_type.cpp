#include "generic_object_type.h"

using namespace pdfio;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <> int GenericObject::TypeId<pdf1_7::FileStructure::XrefStream>()
{
  return static_cast<int>(pdf1_7::GenericObjectType::kXrefStream);
}


#endif //DOXYGEN_SHOULD_SKIP_THIS