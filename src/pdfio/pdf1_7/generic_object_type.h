#pragma once

#include "pdfio/pdf1_0/generic_object_type.h"
#include "file_structure.h"
#include "document_catalog.h"

namespace pdfio
{
  
namespace pdf1_7
{
  
enum class GenericObjectType
{
  kXrefStream = static_cast<int>(pdf1_0::GenericObjectType::kReal) + 1,
  kArrayDictionary,
  kOutputIntents,
  kLiteralString,
  kDocumentCatalog,
};

} // namespace pdf1_0
/*! \brief Returns type id of XrefStream.*/
template <> int GenericObject::TypeId<pdf1_7::FileStructure::XrefStream>();
/*! \brief Returns type id of Array<Dictionary>.*/
template <> int GenericObject::TypeId<pdf1_7::Array<pdf1_7::Dictionary>>();
/*! \brief Returns type id of OutputIntent.*/
template <> int GenericObject::TypeId<pdf1_7::Array<pdf1_7::DocumentCatalog::OutputIntent>>();
/*! \brief Returns type id of LiteralString.*/
template <> int GenericObject::TypeId<pdf1_7::LiteralString>();
/*! \brief Returns type id of DocumentCatalog.*/
template <> int GenericObject::TypeId<pdf1_7::DocumentCatalog>();

} // namespace pdfio