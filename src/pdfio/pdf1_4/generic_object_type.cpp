#include "generic_object_type.h"

using namespace pdfio;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

template <> int GenericObject::TypeId<pdf1_4::Destination>()
{
   return static_cast<int>(pdf1_4::GenericObjectType::kDestination);
}

template <> int GenericObject::TypeId<pdf1_4::Action>()
{
   return static_cast<int>(pdf1_4::GenericObjectType::kAction);
}

#endif //DOXYGEN_SHOULD_SKIP_THIS
