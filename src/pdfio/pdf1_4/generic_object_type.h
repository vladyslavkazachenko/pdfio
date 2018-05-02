#pragma once

#include "pdfio/pdf1_0/generic_object_type.h"
#include "destination.h"
#include "action.h"

namespace pdfio
{
  
namespace pdf1_4
{
  
enum class GenericObjectType
{
  kDestination = static_cast<int>(pdf1_0::GenericObjectType::kReal) + 1,
  kAction,
};

} // namespace pdf1_4

/*! \brief Returns type id of Destination.*/
template <> int GenericObject::TypeId<pdf1_4::Destination>();
/*! \brief Returns type id of Action.*/
template <> int GenericObject::TypeId<pdf1_4::Action>();

} // namespace pdfio
