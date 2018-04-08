#pragma once

#include "pdfio/pdf1_0/generic_object_type.h"
#include "pdfio/pdf1_7/file_structure.h"

namespace pdfio
{
  
namespace pdf1_7
{
  
enum class GenericObjectType
{
  kXrefStream = static_cast<int>(pdf1_0::GenericObjectType::kReal) + 1,
};

} // namespace pdf1_0
/*! \brief Returns type id of XrefStream.*/
template <> int GenericObject::TypeId<pdf1_7::FileStructure::XrefStream>();

} // namespace pdfio